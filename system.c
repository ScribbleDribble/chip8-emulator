#include "system.h"

unsigned char* read_code(const char* file_name, int* filelen) {
    FILE* f = fopen(file_name, "r");

    if (f == NULL) {
        fprintf(stderr, "Could not open file. Exiting program.\n");
        exit(0);
    }

    fseek(f, 0, SEEK_END);
    *filelen = ftell(f);
    rewind(f);
    unsigned char* code = (unsigned char *)malloc(*filelen*sizeof(unsigned char));
    fread(code, *filelen, 1, f);
    
    fclose(f);

    return code;
}

Chip8 init_system(const char* program_path) {
    Chip8 chip8;
    chip8.i_register = 0;
    chip8.pc = BASE_INSTRUCTION_ADDRESS;
    chip8.vf = 0;

    int codelen = 0;
    unsigned char* code = read_code(program_path, &codelen);

    int i = 0;
    int instruction_count = 0;
    while (i < codelen) {
        printf("%x\n", code[i]);
        chip8.memory[BASE_INSTRUCTION_ADDRESS + instruction_count] = code[i++];

        instruction_count++;
    }

    free(code);
    return chip8;
}