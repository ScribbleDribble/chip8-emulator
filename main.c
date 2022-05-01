#include <stdio.h>
#include "SDL.h"
#include "vm.h"
#include "display.h"
#include "decode.h"

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
            

    _Bool display[WIDTH][HEIGHT];
    unsigned char registers[16];
    unsigned int memory[MEMORY_SIZE];
    unsigned int i_register = 0;
    
    const int base_instruction_addr = 0x200;
    int pc = base_instruction_addr;    
    
    

    char* file_name = "tests/ibm_program.ch8";
    int filelen = 0;
    
    unsigned char* code = read_code(file_name, &filelen);
    
    int i = 0;
    int instruction_count = 0;
    while (i < filelen) {
        printf("%x\n", get_instruction(code[i], code[i+1]));
        memory[base_instruction_addr + instruction_count] = get_instruction(code[i], code[i+1]);
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
                                
                decode(memory[pc], display, &pc, registers, i_register);
                
                if (pc >= base_instruction_addr + filelen)
                {
                    pc = base_instruction_addr;
                }
                
                
                printf("display");
                for (int i=0; i < WIDTH; i++)
                    for (int j=0; j < HEIGHT; j++)
                    {
                        if (display[i][j] == 1)
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

    
    
    
    return 0; 

}
