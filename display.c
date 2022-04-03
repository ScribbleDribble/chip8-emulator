#include "display.h"



void clear_display(_Bool* display) {
    for (int i = 0; i < DISPLAY_SIZE; ++i)
        display[i] = 0;
}
