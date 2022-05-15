#ifndef _DECODE_H
#define _DECODE_H

#include "display.h"
#include <stdio.h>
#include <stdbool.h>

 /**
  * finds the instruction type and then
  * finds the appropriate decode-execute function
  */
void decode(Chip8* Chip8);

/**
 * gets the first nibble of the 16-bit instruction, which tells us the type of instruction
 */
int get_instruction_type(int instruction);

/**
 * Returns the lower 12-bits of the instruction.
 * The instruction is truncated because we no longer need the most          * significant 4 bits after knowing the instruction type
 * also can be used as NNN
 */ 
int get_lower_instruction(int instruction);

int get_lower_byte(int lower_instruction);


/**
 * for the classification of each of these instructions, we will be using the LS 12 bits of the 
 * 16 bit instruction as we already know the instruction type
 * 
 * returns
 * 0 - SYS addr
 * 1 - CKS
 * 2 - RET
 */
int decode_instruction_type_0(int lower_instruction, _Bool display[HEIGHT][WIDTH]);
void decode_instruction_type_1(int lower_instruction, int* pc);
void decode_instruction_type_6(int lower_instruction, unsigned char registers[N_REGISTERS]);
void decode_instruction_type_7(int lower_instruction, unsigned char registers[N_REGISTERS]);
void decode_instruction_type_A(int lower_instruction, unsigned int* i_register);
void decode_instruction_type_D(int lower_instruction, Chip8* chip8);

 #endif
