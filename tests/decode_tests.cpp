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
    ASSERT_EQ(decode_instruction_type_0(lower_call_instruction), expected_instruction);
    
    int lower_cls_instruction = 0b000011100000;
    expected_instruction = 1;
    ASSERT_EQ(decode_instruction_type_0(lower_cls_instruction), expected_instruction);
    
    int lower_return_instruction = 0b000011101110;
    expected_instruction = 2;
    ASSERT_EQ(decode_instruction_type_0(lower_return_instruction), expected_instruction);
    
}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
