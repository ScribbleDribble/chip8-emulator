#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdbool.h>
#include <stdint.h>
#include "specifications.h"


#define DISPLAY_SIZE 2048
#define SPRITE_WIDTH 8
#define MAX(a,b) (((a)>(b))?(a):(b))


void clear_display(_Bool display[HEIGHT][WIDTH]);
// by default, each sprite will be 9 pixels wide
void draw(int x, int y, int sprite_height, _Bool display[HEIGHT][WIDTH], uint8_t row_detail[],  _Bool* vf);

_Bool get_sprite_pixel(int col, uint8_t row_data);


#endif
