#include "decode.h"

#define CLEAR_DISPLAY 0b000011100000
#define RETURN_FROM_SUBROUTINE 0b000011101110

int get_instruction_type(int instruction) {
    int mask = 0b1111000000000000;
    int shift_to_get_ms_nibble = 12;
    return (mask & instruction) >> shift_to_get_ms_nibble;
}

 int decode_instruction_type_0(int lower_instruction) {
    
     switch(lower_instruction) {
        case CLEAR_DISPLAY:
            return 1; // call clear screen subroutine 
        
        case RETURN_FROM_SUBROUTINE:
            return 2;
        
        default:
            return 0;
    }

}
