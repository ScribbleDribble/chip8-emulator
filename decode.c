#include "decode.h"
#include "display.h"

#define CLEAR_DISPLAY 0xE0
#define RETURN_FROM_SUBROUTINE 0xEE


void decode(Chip8* chip8) {
    const unsigned int instruction = get_instruction(chip8);

    const unsigned int instruction_type = get_instruction_type(instruction);
    int truncated_instruction = NNN(instruction);
    printf("instruction: %x | instruction type: %i | pc: %i\n", instruction, instruction_type, chip8->pc);

    switch(instruction_type) {
        case 0:
            decode_instruction_type_0(truncated_instruction, chip8->display);        
            break;
        case 1:
            decode_instruction_type_1(truncated_instruction, &chip8->pc);
            // to keep pc the same as we want to execute the current instruction next
            chip8->pc -= 2;
            break;
        case 6:
            decode_instruction_type_6(truncated_instruction, chip8->registers);
            break;
        case 7:
            decode_instruction_type_7(truncated_instruction, chip8->registers);
            break;
        case 0xA:
            decode_instruction_type_A(truncated_instruction, &chip8->i_register);
            break;
        case 0xD:
            decode_instruction_type_D(truncated_instruction, chip8);
            break;
        default:
            printf("Instruction not supported");
            break;
    }
    
    chip8->pc += 2;
    
}

int get_instruction_type(int instruction) {
    return (0xF000 & instruction) >> 12;
}

uint16_t get_instruction(Chip8* chip8) {
    unsigned char low_byte = chip8->memory[chip8->pc+1];
    unsigned char high_byte = chip8->memory[chip8->pc]; 
    return (high_byte << 8) | low_byte;
}

/**
 * Denoted as 'X' within opcodes 
 */
int get_second_ms_nibble(int instruction) {
    return (0x0F00 & instruction) >> 8;
}

/**
 * Denoted as 'Y' within opcodes 
 */
int get_third_ms_nibble(int instruction) {
    return (0x00F0 & instruction) >> 4;
}

/**
 * Denoted as 'NN within opcodes
 */
int get_lower_byte(int instruction) {
    return 0x00FF & instruction;
}


/**
 * Denoted as 'N'
 */
int get_fourth_ms_nibble(int instruction) {
    return 0x000F & instruction;
    
}

int decode_instruction_type_0(int truncated_instruction, _Bool display[HEIGHT][WIDTH]) {
    switch(truncated_instruction) {
        case 0XE0:
            clear_display(display);
            return 1;

        case 0XEE:
            return 2;
        
        default:
            break;
    }

}

void decode_instruction_type_1(int truncated_instruction, int* pc) {
    *pc = truncated_instruction;

}

void decode_instruction_type_6(int truncated_instruction, unsigned char registers[N_REGISTERS]) {
    int register_vx = get_second_ms_nibble(truncated_instruction);
    registers[register_vx] = get_lower_byte(truncated_instruction);
}

void decode_instruction_type_7(int truncated_instruction, unsigned char registers[N_REGISTERS]) {
    // TODO set carry flag if the addition will cause an overflow
    int register_vx = get_second_ms_nibble(truncated_instruction);
    registers[register_vx] += get_lower_byte(truncated_instruction);
}

void decode_instruction_type_A(int truncated_instruction, unsigned int* i_register) {
    *i_register = truncated_instruction;
}

void decode_instruction_type_D(int truncated_instruction, Chip8* chip8) {
    int register_vx = get_second_ms_nibble(truncated_instruction);
    int register_vy = get_third_ms_nibble(truncated_instruction);
    
    int sprite_height = get_fourth_ms_nibble(truncated_instruction);

    uint8_t row_list[sprite_height];

    // printf("i_reg addr: %i\nvalue pointed by i_reg: %i\n", chip8->i_register, chip8->memory[chip8->i_register]);
    for (int i = 0; i < sprite_height; ++i)
    {
        row_list[i] = chip8->memory[chip8->i_register + i];
    }

    chip8->vf = 0;
    uint8_t x = (uint8_t) chip8->registers[register_vx] % (WIDTH-1);
    uint8_t y = (uint8_t) chip8->registers[register_vy] % (HEIGHT-1);

    // printf("x: %i, y: %i, sprite height: %i\n", x, y, sprite_height);
    draw(x, y, sprite_height, chip8->display, row_list, &chip8->vf);
}
