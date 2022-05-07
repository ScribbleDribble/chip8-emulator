#include <stdio.h>
#include "SDL.h"
#include "display.h"
#include "decode.h"
#include "specifications.h"


Chip8 init_system() {
    Chip8 chip8;
    chip8.i_register = 0;
    chip8.pc = BASE_INSTRUCTION_ADDRESS;
    return chip8;
}

int get_instruction(unsigned char high_byte, unsigned char low_byte) {
    return (high_byte << 8) | low_byte;
}

// returns size of the file in bytes
unsigned char* read_code(char* file_name, int* filelen) {
    
    FILE* f = fopen(file_name, "rb");
    fseek(f, 0, SEEK_END);
    *filelen = ftell(f);
    rewind(f);
    
    unsigned char* code = (unsigned char *)malloc(*filelen*sizeof(unsigned char));
    fread(code, *filelen, 1, f);
    fclose(f);
    
    return code;
}

int main(int argc, char* argv[]) {
    
    Chip8 chip8 = init_system();  

    char* file_name = "tests/ibm_program.ch8";
    int codelen = 0;
    
    unsigned char* code = read_code(file_name, &codelen);
    
    int i = 0;
    int instruction_count = 0;
    while (i < codelen) {
        printf("%x\n", get_instruction(code[i], code[i+1]));
        chip8.memory[BASE_INSTRUCTION_ADDRESS + instruction_count] = get_instruction(code[i], code[i+1]);
        instruction_count++;
        i += 2;
    }
    
    
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
                
                if (chip8.pc >= BASE_INSTRUCTION_ADDRESS + codelen)
                    chip8.pc = BASE_INSTRUCTION_ADDRESS;
                
                for (int i=0; i < WIDTH; i++)
                    for (int j=0; j < HEIGHT; j++)
                    {
                        if (chip8.display[i][j] == 1)
                            SDL_RenderDrawPoint(renderer, i, j);
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

    SDL_Quit();
    return 0;

}
