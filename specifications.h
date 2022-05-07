#ifndef _SPECIFICATIONS_H
#define _SPECIFICATIONS_H

#include <stdbool.h>

#define MEMORY_SIZE 4096
#define N_REGISTERS 16
#define BASE_INSTRUCTION_ADDRESS 0x200
#define WIDTH 64
#define HEIGHT 32

typedef struct Chip8 {

    unsigned int memory[MEMORY_SIZE];
    unsigned char registers[N_REGISTERS];
    unsigned int i_register;
    unsigned int pc;
    _Bool display[WIDTH][HEIGHT];
}Chip8;


#endif 