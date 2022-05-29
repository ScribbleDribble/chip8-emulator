#ifndef _DECODE_H
#define _DECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "display.h"


#define NNN(instruction) (instruction & 0x0FFF)
#define NN(instruction) (instruction & 0x00FF)
#define N(instruction) (instruction & 0x000F)

#define Y(instruction) ((instruction & 0x00F0) >> 4)


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
int get_truncated_instruction(int instruction);
uint16_t get_instruction(Chip8* chip8);
int get_lower_byte(int truncated_instruction);


/**
 * for the classification of each of these instructions, we will be using the LS 12 bits of the 
 * 16 bit instruction as we already know the instruction type
 * 
 * returns
 * 0 - SYS addr
 * 1 - CKS
 * 2 - RET
 */
int decode_instruction_type_0(int truncated_instruction, _Bool display[HEIGHT][WIDTH]);
void decode_instruction_type_1(int truncated_instruction, int* pc);
void decode_instruction_type_6(int truncated_instruction, unsigned char registers[N_REGISTERS]);
void decode_instruction_type_7(int truncated_instruction, unsigned char registers[N_REGISTERS]);
void decode_instruction_type_A(int truncated_instruction, unsigned int* i_register);
void decode_instruction_type_D(int truncated_instruction, Chip8* chip8);

 #endif
