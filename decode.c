#include "decode.h"
#include "display.h"

#define CLEAR_DISPLAY 0b000011100000
#define RETURN_FROM_SUBROUTINE 0b000011101110
#define A 0xA
#define D 0xD

void decode(Chip8* chip8) {
    const unsigned int instruction = chip8->memory[chip8->pc];
    const unsigned int instruction_type = get_instruction_type(instruction);
    int lower_instruction = get_lower_instruction(instruction);
    printf("instruction: %x | instruction type: %i\n", instruction, instruction_type);

    switch(instruction_type) {
        case 0:
            decode_instruction_type_0(lower_instruction, &chip8->display);        
            break;
        case 1:
            decode_instruction_type_1(lower_instruction, &chip8->pc);
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
            decode_instruction_type_D(lower_instruction, &chip8->registers, &chip8->display);
            break;
        default:
            break;
    }
    
    chip8->pc++;
    
}

int get_instruction_type(int instruction) {
    int mask = 0b1111000000000000;
    int shift_to_get_ms_nibble = 12;
    return (mask & instruction) >> shift_to_get_ms_nibble;
}


int get_lower_instruction(int instruction) {
     int mask = 0b0000111111111111;
     return mask & instruction;
}

/**
 * Denoted as 'X' within opcodes 
 */
int get_second_ms_nibble(int lower_instruction) {
    int mask = 0b111100000000;
    int shift_to_get_second_ms_nibble = 8;
    return (mask & lower_instruction) >> shift_to_get_second_ms_nibble;
}

/**
 * Denoted as 'Y' within opcodes 
 */
int get_third_ms_nibble(int lower_instruction) {
    int mask = 0b000011110000;
    int shift_to_get_third_ms_nibble = 4;
    return (mask & lower_instruction) >> shift_to_get_third_ms_nibble;
}

/**
 * Denoted as 'NN within opcodes
 */
int get_lower_byte(int lower_instruction) {
    int mask = 0b000011111111;
    return mask & lower_instruction;
}


/**
 * Denoted as 'N'
 */
int get_fourth_ms_nibble(int lower_instruction) {
    int mask = 0b000000001111;
    return mask & lower_instruction;
    
}

void decode_instruction_type_0(int lower_instruction, _Bool display[WIDTH][HEIGHT] ) {
     switch(lower_instruction) {
        case CLEAR_DISPLAY:
            clear_display(display);
            break;

        case RETURN_FROM_SUBROUTINE:
            break;
        
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

void decode_instruction_type_D(int lower_instruction, unsigned char registers[N_REGISTERS], _Bool display[WIDTH][HEIGHT]) {
	
    int register_vx = get_second_ms_nibble(lower_instruction);
    int register_vy = get_third_ms_nibble(lower_instruction);
    
    int sprite_height = get_fourth_ms_nibble(lower_instruction);
    char x = registers[register_vx];
    char y = registers[register_vy];
    
    draw(x, y, sprite_height, display);
}
