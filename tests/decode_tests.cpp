#include <gtest/gtest.h>

extern "C" {
#include <stdint.h>
#include <stdbool.h>
#include "../helpers.h"
#include "../decode.h"
#include <string.h>

}

TEST(test_get_NNN_from_instruction, examples) {
    int instruction = 0xf1da;
    int expected_truncated_instruction = 0x1da;
    ASSERT_EQ(expected_truncated_instruction, NNN(instruction));
}

TEST(test_get_NN_from_instruction, examples) {
    int instruction = 0x02AB;
    int expected_result = 0xAB;

    ASSERT_EQ(expected_result, NN(instruction));
}

TEST(test_decode_0, examples) {
    int instruction = 0x00E0;
    int expected_result = 1;

    Chip8 chip8;
    
    ASSERT_EQ(decode_instruction_type_0(&chip8, instruction), expected_result);
    
    instruction = 0x00EE;
    chip8.stack[2] = 0xAB;
    chip8.stack[1] = 0xDA;
    chip8.sp = 2;
    
    decode_instruction_type_0(&chip8, instruction);
    
    ASSERT_EQ(chip8.stack[2], 0);
    ASSERT_EQ(chip8.pc, 0xAB);
    ASSERT_EQ(chip8.sp, 1);
    
}

TEST(test_decode_1, examples) {
    int instruction = 0x1300;
    Chip8 chip8;
    
    decode_instruction_type_1(&chip8, instruction);

    ASSERT_EQ(chip8.pc, 0x300-2);
}

TEST(test_decode_2, examples) {
    Chip8 chip8;
    chip8.sp = 0;
    const uint16_t instruction = 0x1EEE;
    const uint16_t instruction2 = 0x1ABC;
    
    decode_instruction_type_2(&chip8, instruction);
    ASSERT_EQ(chip8.sp, 1);

    // decode() will increment the pc by two 
    chip8.pc += 2;

    decode_instruction_type_2(&chip8, instruction2);
    ASSERT_EQ(chip8.sp, 2);
    ASSERT_EQ(chip8.stack[chip8.sp], 0xEEE);
    ASSERT_EQ(chip8.pc, 0xABC-2);
}

TEST (test_decode_5, examples) {
    Chip8 chip8;


    chip8.pc = BASE_INSTRUCTION_ADDRESS;
    chip8.registers[1] = 5;
    chip8.registers[2] = 5;
    const uint16_t instruction = 0x5120;

    decode_instruction_type_5(&chip8, instruction);

    ASSERT_EQ(BASE_INSTRUCTION_ADDRESS+2, chip8.pc);

}

TEST(test_decode_6, examples) {
    Chip8 chip8;
    const uint16_t instruction = 0x6A06;
    
    decode_instruction_type_6(&chip8, instruction);
    ASSERT_EQ(chip8.registers[0xA], 6);
}

TEST(test_decode_7, examples) {
    Chip8 chip8;
    chip8.registers[0] = 5;

    const uint16_t instruction = 0x6005;
    
    decode_instruction_type_7(&chip8, instruction);
    ASSERT_EQ(chip8.registers[0], 0xA);
}

TEST(test_decode_A, examples) {
    Chip8 chip8;
    chip8.i_register = 0;
    int instruction = 0xA100;
    
    decode_instruction_type_A(&chip8, instruction);
    
    ASSERT_EQ(chip8.i_register, 0x100);
}

TEST(test_decode_D, examples) {

    Chip8 chip8;
    chip8.i_register = 5;
    clear_display(chip8.display);
    
    uint16_t instruction = 0xD01F;
    // lower instruction is composed of XYN 
    int X = 0;
    int Y = 1;
    int N = 0xF;
    
    chip8.registers[X] = 2;
    chip8.registers[Y] = 3;

    // we want to have first half of each sprite row to be set as ON
    int i;
    for (i = chip8.i_register; i < chip8.i_register+N; i++) {
        chip8.memory[i] = 0xF0;
    }

    _Bool expected_display[HEIGHT][WIDTH];
    clear_display(expected_display);

    int j;
    int x = chip8.registers[X];
    int y = chip8.registers[Y];
    int sprite_row_length = 8;
    for (j = y; j < y+N; ++j)
        for (i = x; i < x+8; ++i)
            (i-x < (sprite_row_length/2)) ? expected_display[j][i] = 1 : expected_display[j][i] = 0;   

    decode_instruction_type_D(&chip8, instruction);

    for (j = 0; j < HEIGHT; ++j)
        for (i = 0; i < WIDTH; ++i)
        {
            if (expected_display[j][i] != chip8.display[j][i]) printf("Failure at i:%i, j: %i\n", i, j);
            ASSERT_EQ(expected_display[j][i], chip8.display[j][i]);
        }
}

TEST(integration_test, example) {
    // opcodes 0xE0 0xA22A 0x600C 0x6108 0xD01F
    int code_len = 10;
    unsigned char code[code_len] = {0x0, 0xe0, 0xa2, 0x2a, 0x60, 0xc, 0x61, 0x8, 0xd0, 0x1f};

    uint8_t ram[MEMORY_SIZE];
    int i;
    for (i = 0; i < code_len; i++) {
        ram[BASE_INSTRUCTION_ADDRESS + i] = code[i];
    }

    // to be pointed by bit code to draw on screen. will be pointed by i register
    int sprite_height = 0xf;
    for (i = 0; i < sprite_height; i++) {
        ram[0x22A + i] = 0b11111111;
    }
    
    Chip8 chip8;
    chip8.i_register = 0;
    chip8.pc = BASE_INSTRUCTION_ADDRESS;
    chip8.vf = 0;
    
    memcpy(chip8.memory, ram, MEMORY_SIZE);

    int cycles = 0;
    while (cycles < 5){
        decode(&chip8);
        cycles++;
    }

    _Bool expected_display[HEIGHT][WIDTH];

    int j;
    int bit_code_length = 8;
    for (j = 0; j < HEIGHT; ++j){
        for(i = 0; i < WIDTH; ++i) {
            if (j >= 8 && j < 8 + sprite_height && i >= 12 && i < 12+bit_code_length){
                expected_display[j][i] = 1;
            }
            else
                expected_display[j][i] = 0;
        }

    }
    // We expect
    // 1. The screen to be cleared
    // 2. The i register to point at address 22A = 554
    // 3. register 0 = c
    // 4. register 1 = 8
    // 5. to draw at (12, 8) at height of 15 
    
    // We should see this drawn:
    //      col
    //       11                 
    // row     
    //  7    0 0 0 0 0 0 0 0 0 ...    
    //  8    0 1 1 1 1 1 1 1 1        
    //       0 1 1 1 1 1 1 1 1        
    //       0 1 1 1 1 1 1 1 1        
    // ...
    //       0 1 1 1 1 1 1 1 1       
    //

    ASSERT_EQ(0x22A, chip8.i_register);
    ASSERT_EQ(0xc, chip8.registers[0]);
    ASSERT_EQ(8, chip8.registers[1]);
    
    printf("\n%i\n", expected_display[j][i]);
    for (j = 0; j < HEIGHT; ++j)
        for(i = 0; i < WIDTH; ++i)
            {
                if (expected_display[j][i] != chip8.display[j][i]) printf("Mismatch at i:%i, j: %i\n", i, j);
                ASSERT_EQ(expected_display[j][i], chip8.display[j][i]);
            }
    
}

TEST(test_print_n_bits, examples) {

    uint8_t num = 4;
    char* byte_string = print_n_bits_int(num, 10);
    
    ASSERT_STREQ("0000000100", byte_string);
    
}


TEST(test_get_sprite_pixel, examples) {
    uint8_t row_data = 0b11000000;
    int col = 1;
    _Bool sprite_pixel1 = get_sprite_pixel(col, row_data);
    _Bool sprite_pixel2 = get_sprite_pixel(col+1, row_data);

    ASSERT_TRUE(sprite_pixel1);
    ASSERT_FALSE(sprite_pixel2);
    ASSERT_FALSE(get_sprite_pixel(col+2, row_data));
}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
