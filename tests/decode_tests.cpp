#include <gtest/gtest.h>

extern "C" {
#include <stdint.h>
#include <stdbool.h>
#include "../helpers.h"
#include "../decode.h"
}

TEST(test_instruction_type, examples) {
    int instruction = 0b0100100111000001;
    int expected_instruction_type = 4;
    ASSERT_EQ(get_instruction_type(instruction), expected_instruction_type);
}

TEST(test_get_lower_instruction, examples) {
    int instruction = 0xf1da;
    int expected_lower_instruction = 0x1da;
    ASSERT_EQ(expected_lower_instruction, get_lower_instruction(instruction));
}

TEST(test_get_lower_byte, examples) {
    int lower_instruction = 0x2AB;
    int result = get_lower_byte(lower_instruction);
    int expected_result = 0xAB;

    ASSERT_EQ(expected_result, result);
}

TEST(test_decode_0, examples) {
    int lower_call_instruction = 0xE0;
    int expected_instruction = 1;

    _Bool fake_display[HEIGHT][WIDTH];
    
    ASSERT_EQ(decode_instruction_type_0(lower_call_instruction, fake_display), expected_instruction);
    
    int lower_cls_instruction = 0xEE;
    expected_instruction = 2;
    ASSERT_EQ(decode_instruction_type_0(lower_cls_instruction, fake_display), expected_instruction);
    
    // int lower_return_instruction = 0b000011101110;
    // expected_instruction = 2;
    // ASSERT_EQ(decode_instruction_type_0(lower_return_instruction, fake_display), expected_instruction);
    
}

TEST(test_decode_1, examples) {
    int pc = 0x0000;
    int lower_instruction = 0x30;
    
    decode_instruction_type_1(lower_instruction, &pc);
    
    ASSERT_EQ(pc, lower_instruction);
}

TEST(test_decode_6, examples) {
    unsigned char registers[16];
    int lower_instruction = 0b011000001010;
    
    decode_instruction_type_6(lower_instruction, registers);
    ASSERT_EQ(registers[6], 0xA);
}

TEST(test_decode_7, examples) {
    unsigned char registers[16];
    registers[6] = 8;
    
    int lower_instruction = 0b011000000010;
    
    decode_instruction_type_7(lower_instruction, registers);
    ASSERT_EQ(registers[6], 10);
}

TEST(test_decode_A, examples) {
    unsigned int i_register = 0x0000;
    int lower_instruction = 0x30;
    
    decode_instruction_type_A(lower_instruction, &i_register);
    
    ASSERT_EQ(i_register, lower_instruction);
}

TEST(test_decode_D, examples) {

    Chip8 chip8;
    chip8.i_register = 5;
    clear_display(chip8.display);
    
    unsigned int lower_instruction = 0x01f;
    // lower instruction is composed of XYN 
    int X = 0;
    int Y = 1;
    int N = 0xF;
    
    chip8.registers[X] = 2;
    chip8.registers[Y] = 3;

    // we want to have first half each sprite row to be set as ON
    int i;
    for (i = chip8.i_register; i < chip8.i_register+N; i++) {
        chip8.memory[i] = 0xF0;
    }

    _Bool expected_display[HEIGHT][WIDTH];
    clear_display(expected_display);
    
    int j;
    int x = chip8.registers[X];
    int y = chip8.registers[Y];

    for (j = y; j < y+N; ++j)
        for (i = x; i < x+8; ++i)
            (i-x < 4) ? expected_display[j][i] = 1 : expected_display[j][i] = 0;   

    decode_instruction_type_D(lower_instruction, &chip8);

    for (j = 0; j < HEIGHT; ++j)
        for (i = 0; i < WIDTH; ++i)
        {
            if (expected_display[j][i] != chip8.display[j][i]) printf("Failure at i:%i, j: %i\n", i, j);
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
