#ifndef _DIPLAY_H
#define _DISPLAY_H

#include <stdbool.h>
#include "specifications.h"


#define DISPLAY_SIZE 2048
#define MAX(a,b) (((a)>(b))?(a):(b))


void clear_display(_Bool display[WIDTH][HEIGHT]);
// by default, each sprite will be 9 pixels wide
void draw(int x, int y, int height, _Bool display[WIDTH][HEIGHT]);

#endif
