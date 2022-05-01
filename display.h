#ifndef DIPLAY_H
#define DISPLAY_H

#define DISPLAY_SIZE 2048

#define WIDTH 64
#define HEIGHT 32
#define MAX(a,b) (((a)>(b))?(a):(b))
#include <stdbool.h>


extern _Bool display[WIDTH][HEIGHT];


void clear_display(_Bool display[WIDTH][HEIGHT] );
// by default, each sprite will be 9 pixels wide
void draw(int x, int y, int height, _Bool display[WIDTH][HEIGHT]);

#endif
