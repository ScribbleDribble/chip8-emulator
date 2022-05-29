#include <stdio.h>
#include "SDL.h"
#include "display.h"
#include "decode.h"
#include "helpers.h"
#include "specifications.h"
#include <stdlib.h>


Chip8 init_system() {
    Chip8 chip8;
    chip8.i_register = 0;
    chip8.pc = BASE_INSTRUCTION_ADDRESS;
    chip8.vf = 0;
    return chip8;
}



unsigned char* read_code(char* file_name, int* filelen) {
    
    FILE* f = fopen(file_name, "r");

    if (f == NULL) {
        fprintf(stderr, "Could not open file. Exiting program.");
        exit(0);
    }
    fseek(f, 0, SEEK_END);
    *filelen = ftell(f);
    rewind(f);
    
    unsigned char* code = (unsigned char *)malloc(*filelen*sizeof(unsigned char));
    fread(code, *filelen, 1, f);



    // int i = 0;
    // char c = fgetc(f);
    // while (c != EOF) {
    //     // printf("%x\n", (unsigned char) c);
    //     printf("%i\n", i++);
    //     code[(*filelen)++] = c;
    //     c = fgetc(f);
    //     code = (unsigned char *) realloc(code, (*filelen)+1);
    // }


    fclose(f);
    
    return code;
}

uint16_t get_instruction2(unsigned char low_byte, unsigned char high_byte) {
    return (high_byte << 8) | low_byte;
}


int main(int argc, char* argv[]) {
    
    Chip8 chip8 = init_system();  

    char* file_name = "tests/ibm_program.ch8";
    int codelen = 0;
    
    unsigned char* code = read_code(file_name, &codelen);
    
    int i = 0;
    int instruction_count = 0;
    while (i < codelen) {
        printf("%x\n", code[i]);
        chip8.memory[BASE_INSTRUCTION_ADDRESS + instruction_count] = code[i++];
        instruction_count++;
    }

    print_memory(&chip8, codelen);
    // exit(0);
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;
                
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                                
                decode(&chip8);
                
                if (chip8.pc >= codelen+BASE_INSTRUCTION_ADDRESS){
                    // printf("%i\n", codelen);
                    chip8.pc = BASE_INSTRUCTION_ADDRESS;
                    
                }

                for (int j=0; j < HEIGHT; j++)
                    for (int i=0; i < WIDTH; i++)
                    {
                        if (chip8.display[j][i] == 1)
                            SDL_RenderDrawPoint(renderer, j, i);
                    }
                        
                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }

    free(code);

    SDL_Quit();
    return 0;

}
