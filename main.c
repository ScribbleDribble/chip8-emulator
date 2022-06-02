#include <stdio.h>
#include "display.h"
#include "decode.h"
#include "helpers.h"
#include "system.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    
    char* program_path = argc == 2 ? argv[1] : "tests/test_opcode.ch8";

    window_loop(program_path);

    return 0;

}
