#include "display.h"
#include <stdio.h>
#include "helpers.h"

void clear_display(_Bool display[HEIGHT][WIDTH]) {
    memset(display, 0, HEIGHT*WIDTH*sizeof(_Bool));
}

_Bool get_sprite_pixel(int col, uint8_t row_detail) {
    return (0b10000000 >> col) & row_detail;
}

void draw(Chip8* chip8, int x, int y, int sprite_height, uint8_t bit_rows[]) {
    _Bool sprite_pixel = 0;
    for (int j = y; j < y+sprite_height; ++j) {
        uint8_t row_detail = bit_rows[j-y];
        for (int i = x; i < x+8; ++i) {
            sprite_pixel = get_sprite_pixel(i-x, row_detail);
            chip8->display[j][i] ^= sprite_pixel;
            if (sprite_pixel == 1 && chip8->display[j][i] == 0)
                chip8->vf = 1; 
        }
        if (y >= HEIGHT)
            break;
    }
}  
        
