#include "decode.h"
#include "display.h"

#define MEMORY_SIZE 4096



void sys_loop() {
    // The main loop for the CHIP-8 
    
    char memory[MEMORY_SIZE];
    _Bool display[DISPLAY_SIZE];
    int pc;
    
    
    clear_display(display);
    while (1) {
        
        switch(get_instruction_type(memory[pc])) {
            
            case 0:
                
            
            case 1:
                printf("run this");
                break;
                
            default:
                printf("throw exception...but there are no exceptions in C");
                
            
        }
    
    
    } 

}
