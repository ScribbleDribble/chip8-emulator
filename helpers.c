#include "helpers.h"

char* print_n_bits_int(int x, int n) {

    char* bit_string = (char*)malloc(sizeof(char)*(n+1));
    bit_string[n] = '\0';

    int i = n-1;
    while (x > 0) {
        if (x & 1 == 1)
            bit_string[i--] = '1';
        else
            bit_string[i--] = '0' ;
        x >>= 1;
    }

    while (i >= 0)
        bit_string[i--] = '0';
        
    printf("%s\n", bit_string);
    return bit_string;
}