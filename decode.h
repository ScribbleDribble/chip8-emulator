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
#define X(instruction) ((instruction & 0x0F00) >> 8)


 /**
  * finds the instruction type and then
  * finds the appropriate decode-execute function
  */
void decode(Chip8* Chip8);

uint16_t get_instruction(Chip8* chip8);

/**
 * 
 * 
 * 00E0 Clear display, 00EE return from function, 
 */
int decode_instruction_type_0(Chip8* chip8, const uint16_t instruction);

// junp to address NNN
void decode_instruction_type_1(Chip8* chip8, const uint16_t instruction);

// call function at NNN
void decode_instruction_type_2(Chip8* chip8, const uint16_t instruction);

void decode_instruction_type_3(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_4(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_5(Chip8* chip8, const uint16_t instruction);

// Set register X to NN
void decode_instruction_type_6(Chip8* chip8, const uint16_t instruction);
// Increment register X by NN
void decode_instruction_type_7(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_8(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_9(Chip8* chip8, const uint16_t instruction);

// Store address NNN inside I register 
void decode_instruction_type_A(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_B(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_C(Chip8* chip8, const uint16_t instruction);

// DXYN
// Draw sprites on display starting at (register[X], register[Y]) with a height of N pixels
// Starting from the base address pointed by i register, the next N-1 memory addresses 
// ...will hold a bit-coded row of values that should be xor'ed with the screen 
void decode_instruction_type_D(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_E(Chip8* chip8, const uint16_t instruction);
void decode_instruction_type_F(Chip8* chip8, const uint16_t instruction);

#endif
