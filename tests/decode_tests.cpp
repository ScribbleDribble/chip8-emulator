#include <gtest/gtest.h>

extern "C" {
#include "../decode.h"
}

TEST(test_instruction_type, examples) {
    int instruction = 0b0100100111000001;
    int expected_instruction_type = 4;
    ASSERT_EQ(get_instruction_type(instruction), expected_instruction_type);
}

TEST(test_decode_0, examples) {
    int lower_call_instruction = 0b110111001000;
    int expected_instruction = 0;
    /*
    ASSERT_EQ(decode_instruction_type_0(lower_call_instruction), expected_instruction);
    
    int lower_cls_instruction = 0b000011100000;
    expected_instruction = 1;
    ASSERT_EQ(decode_instruction_type_0(lower_cls_instruction), expected_instruction);
    
    int lower_return_instruction = 0b000011101110;
    expected_instruction = 2;
    ASSERT_EQ(decode_instruction_type_0(lower_return_instruction), expected_instruction);
    */
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
    registers[6] = 0x8;
    
    int lower_instruction = 0b011000000010;
    
    decode_instruction_type_7(lower_instruction, registers);
    ASSERT_EQ(registers[6], 0xA);
}

TEST(test_decode_A, examples) {
    unsigned int i_register = 0x0000;
    int lower_instruction = 0x30;
    
    decode_instruction_type_A(lower_instruction, &i_register);
    
    ASSERT_EQ(i_register, lower_instruction);
}


int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
