#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "system.h"

#define DISPLAY_SIZE 2048
#define SPRITE_WIDTH 8
#define FONT_START 050
#define FONT_END 09F

#define MAX(a,b) (((a)>(b))?(a):(b))

// TODO maybe move this code to system file

void clear_display(_Bool display[HEIGHT][WIDTH]);
void draw(Chip8* chip8, int x, int y, int sprite_height, uint8_t bit_rows[]);

_Bool get_sprite_pixel(int col, uint8_t row_data);


#endif
