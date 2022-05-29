#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdlib.h>
#include <stdint.h>

#include "specifications.h"

char* print_n_bits_int(int x, int n);
void print_memory(Chip8* chip8, const int program_length);

#endif