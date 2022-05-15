#include "display.h"
#include <stdio.h>
#include "helpers.h"

void clear_display(_Bool display[HEIGHT][WIDTH]) {
    for (int j = 0; j < HEIGHT; ++j)
        for (int i = 0; i < WIDTH; ++i)
            display[j][i] = 0;
}

_Bool get_sprite_pixel(int col, uint8_t row_data) {
    return (0b10000000 >> col) & row_data;
}

void draw(int x, int y, int sprite_height, _Bool display[HEIGHT][WIDTH], uint8_t row_detail[], _Bool* vf) {
    _Bool sprite_pixel = 0;
    for (int j = y; j < y+sprite_height; ++j) {
        uint8_t row_data = row_detail[j-y];
        for (int i = x; i < x+8; ++i) {
            sprite_pixel = get_sprite_pixel(i-x, row_data);
            
            display[j][i] ^= sprite_pixel;
            if (sprite_pixel == 1 && display[j][i] == 0)
                *vf = 1; 
        }
        if (y >= HEIGHT)
            break;
    }



}  
        
