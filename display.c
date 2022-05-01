#include "display.h"
#include <stdio.h>

void clear_display(_Bool display[WIDTH][HEIGHT]) {
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < HEIGHT; ++j)
            display[i][j] = 0;
}

void draw(int x, int y, int height, _Bool display[WIDTH][HEIGHT]) {
    const int sprite_width = 8;
    for (int i = 0; i < MAX(height, sprite_width); ++i) {
        
        if (i < sprite_width)
            display[x + i][y] ^= 1; 
        
        if (i < height)
        {
            display[x][y + i] ^= 1;
        }
        
    }
}
