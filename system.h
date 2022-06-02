#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096
#define N_REGISTERS 16
#define BASE_INSTRUCTION_ADDRESS 0x200
#define MAX_STACK_DEPTH 12
#define WIDTH 64
#define HEIGHT 32

typedef struct Chip8 {

    uint8_t memory[MEMORY_SIZE];
    uint16_t stack[MAX_STACK_DEPTH];
    uint8_t sp;
    uint8_t registers[N_REGISTERS];
    unsigned int i_register;
    unsigned int pc;
    _Bool display[HEIGHT][WIDTH];
    _Bool vf;

}Chip8;

Chip8 init_system(const char* program_path);

#endif 