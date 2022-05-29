#include "display.h"
#include <stdio.h>
#include "helpers.h"

void clear_display(_Bool display[HEIGHT][WIDTH]) {
    memset(display, 0, HEIGHT*WIDTH*sizeof(_Bool));
}

_Bool get_sprite_pixel(int col, uint8_t row_detail) {
    return (0b10000000 >> col) & row_detail;
}

void draw(int x, int y, int sprite_height, _Bool display[HEIGHT][WIDTH], uint8_t row_list[], _Bool* vf) {
    _Bool sprite_pixel = 0;
    for (int j = y; j < y+sprite_height; ++j) {
        uint8_t row_detail = row_list[j-y];
        // print_n_bits_int(row_detail, 8);
        // printf("\n");
        for (int i = x; i < x+8; ++i) {
            sprite_pixel = get_sprite_pixel(i-x, row_detail);
            display[j][i] ^= sprite_pixel;
            if (sprite_pixel == 1 && display[j][i] == 0)
                *vf = 1; 
        }
        if (y >= HEIGHT)
            break;
    }



}  
        
