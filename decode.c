#include "decode.h"
#include "display.h"
#include "registers.h"

#define CLEAR_DISPLAY 0b000011100000
#define RETURN_FROM_SUBROUTINE 0b000011101110
#define A 0b000000001010
#define D 0b000000001101

 /**
  * this function will 
  * find the instruction type 
  * then using a switch statement, will find the appropriate decode-execute function
  * TODO decode-execute functions to only use lower_instructions (lower 12 bits 
  */
int decode(int instruction) {
    int instruction_type = get_instruction_type(instruction);
    int lower_instruction = get_lower_instruction(instruction);
    switch(instruction_type) {
        case 0:
            decode_instruction_type_0(lower_instruction);        
            break;
        case 1:
            break;
        case 6:
            break;
        case 7:
            break;
        case A:
            break;
            
        case D:
            break;
        default:
            return 1;
            
    }
}

int get_instruction_type(int instruction) {
    int mask = 0b1111000000000000;
    int shift_to_get_ms_nibble = 12;
    return (mask & instruction) >> shift_to_get_ms_nibble;
}

/**
 * Returns the lower 12-bits of the instruction.
 * The instruction is truncated because we no longer need the most          * significant 4 bits after knowing the instruction type
 * also can be used as NNN
 */ 
int get_lower_instruction(instruction) {
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
 * Denoted as 'NN within opcodes
 */
int get_lower_byte(int lower_instruction) {
    int mask = 0b000011111111;
    return mask & lower_instruction;
}


int decode_instruction_type_0(int lower_instruction) {
    
     switch(lower_instruction) {
        case CLEAR_DISPLAY:
            clear_display();
            return 1; // call clear screen subroutine 
        
        case RETURN_FROM_SUBROUTINE:
            return 2;
        
        default:
            return 0;
    }

}

void decode_instruction_type_1(int lower_instruction, int* pc) {
    *pc = lower_instruction;
}


void decode_instruction_type_6(int lower_instruction, char* registers) {
    int register_vx = get_second_ms_nibble(lower_instruction);
    registers[register_vx] = get_lower_byte(lower_instruction);
}

void decode_instruction_type_7(int lower_instruction, char* registers) {
    // TODO set carry flag if the addition will cause an overflow
    int register_vx = get_second_ms_nibble(lower_instruction);
    registers[register_vx] += get_lower_byte(lower_instruction);
}

void decode_instruction_A(int lower_instruction, int* i) {
    *i = lower_instruction;
}

// void decode_instruction_D(int lower_instruction, int
