#include "decode.h"
#include "display.h"

#define CLEAR_DISPLAY 0xE0
#define RETURN_FROM_SUBROUTINE 0xEE
#define A 0xA
#define D 0xD

void decode(Chip8* chip8) {
    const unsigned int instruction = chip8->memory[chip8->pc];
    const unsigned int instruction_type = get_instruction_type(instruction);
    int lower_instruction = get_lower_instruction(instruction);
    printf("instruction: %x | instruction type: %i | pc: %i\n", instruction, instruction_type, chip8->pc);
    

    switch(instruction_type) {
        case 0:
            decode_instruction_type_0(lower_instruction, &chip8->display);        
            break;
        case 1:
            decode_instruction_type_1(lower_instruction, &chip8->pc);
            // to keep pc the same as we want to execute the current instruction next
            chip8->pc--;
            break;
        case 6:
            decode_instruction_type_6(lower_instruction, &chip8->registers);
            break;
        case 7:
            decode_instruction_type_7(lower_instruction, &chip8->registers);
            break;
        case A:
            decode_instruction_type_A(lower_instruction, &chip8->i_register);
            break;
        case D:
            decode_instruction_type_D(lower_instruction, &chip8);
            break;
        default:
            break;
    }
    
    chip8->pc++;
    
}

int get_instruction_type(int instruction) {
    return (0xF000 & instruction) >> 12;
}


int get_lower_instruction(int instruction) {
     return 0x0FFF & instruction;
}

/**
 * Denoted as 'X' within opcodes 
 */
int get_second_ms_nibble(int lower_instruction) {
    return (0x0F00 & lower_instruction) >> 8;
}

/**
 * Denoted as 'Y' within opcodes 
 */
int get_third_ms_nibble(int lower_instruction) {
    return (0x00F0 & lower_instruction) >> 4;
}

/**
 * Denoted as 'NN within opcodes
 */
int get_lower_byte(int lower_instruction) {
    return 0x00FF & lower_instruction;
}


/**
 * Denoted as 'N'
 */
int get_fourth_ms_nibble(int lower_instruction) {
    return 0x000F & lower_instruction;
    
}

int decode_instruction_type_0(int lower_instruction, _Bool display[HEIGHT][WIDTH]) {
    switch(lower_instruction) {
        case CLEAR_DISPLAY:
            clear_display(display);
            return 1;

        case RETURN_FROM_SUBROUTINE:
            return 2;
        
        default:
            break;
    }

}

void decode_instruction_type_1(int lower_instruction, int* pc) {
    *pc = lower_instruction;
}

void decode_instruction_type_6(int lower_instruction, unsigned char registers[N_REGISTERS]) {
    int register_vx = get_second_ms_nibble(lower_instruction);
    registers[register_vx] = get_lower_byte(lower_instruction);
}

void decode_instruction_type_7(int lower_instruction, unsigned char registers[N_REGISTERS]) {
    // TODO set carry flag if the addition will cause an overflow
    int register_vx = get_second_ms_nibble(lower_instruction);
    registers[register_vx] += get_lower_byte(lower_instruction);
}

void decode_instruction_type_A(int lower_instruction, unsigned int* i_register) {
    *i_register = lower_instruction;
}

void decode_instruction_type_D(int lower_instruction, Chip8* chip8) {

    int register_vx = get_second_ms_nibble(lower_instruction);
    int register_vy = get_third_ms_nibble(lower_instruction);
    
    int sprite_height = get_fourth_ms_nibble(lower_instruction);

    uint8_t row_detail[sprite_height];

    for (int i = 0; i < sprite_height; ++i)
    {
        row_detail[i] = chip8->memory[chip8->i_register + i];
    }

    chip8->vf = 0;

    uint8_t x = (uint8_t) chip8->registers[register_vx] % (WIDTH-1);
    uint8_t y = (uint8_t) chip8->registers[register_vy] % (HEIGHT-1);

    draw(x, y, sprite_height, &chip8->display, row_detail, &chip8->vf);
}
