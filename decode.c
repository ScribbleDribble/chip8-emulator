#include "decode.h"
#include "display.h"



void decode(Chip8* chip8) {
    const unsigned int instruction = get_instruction(chip8);
    const unsigned int instruction_type = (instruction & 0xF000) >> 12;

    printf("instruction: %x | instruction type: %i | pc: %i\n", instruction, instruction_type, chip8->pc);

    void (*decode_ptr_arr[])(Chip8*, const uint16_t) = {
        decode_instruction_type_0, decode_instruction_type_1, decode_instruction_type_2, 
        decode_instruction_type_3, decode_instruction_type_4, decode_instruction_type_5,
        decode_instruction_type_6, decode_instruction_type_7, decode_instruction_type_8, 
        decode_instruction_type_9, decode_instruction_type_A, decode_instruction_type_B, 
        decode_instruction_type_C, decode_instruction_type_D, decode_instruction_type_E, 
        decode_instruction_type_F
    };

    (*decode_ptr_arr[instruction_type])(chip8, instruction);

    chip8->pc += 2;
    
}

uint16_t get_instruction(Chip8* chip8) {
    unsigned char low_byte = chip8->memory[chip8->pc+1];
    unsigned char high_byte = chip8->memory[chip8->pc]; 
    return (high_byte << 8) | low_byte;
}

int decode_instruction_type_0(Chip8* chip8, const uint16_t instruction) {
    int lower_12_bits = NNN(instruction);

    switch(lower_12_bits) {
        case 0xE0:
            clear_display(chip8->display);
            return 1;

        case 0xEE:
            chip8->pc = chip8->stack[chip8->sp];
            chip8->stack[chip8->sp] = 0;
            chip8->sp--;
            return 2;
        
        default:
            break;
    }

}


void decode_instruction_type_1(Chip8* chip8, const uint16_t instruction) {
    chip8->pc = NNN(instruction);
    // the pc will increment by the end of this (and every) cycle. decrement by two to avoid advancing to the next instruction
    chip8->pc -= 2;
}

void decode_instruction_type_2(Chip8* chip8, const uint16_t instruction) {
    if (chip8->sp + 1 > MAX_STACK_DEPTH) {
        fprintf(stderr, "Stack overflow: max stack depth of %i was exceeded\n", MAX_STACK_DEPTH);
        exit(0);
    }
    chip8->sp += 1;
    chip8->stack[chip8->sp] = chip8->pc;
    chip8->pc = NNN(instruction) - 2;
}

void decode_instruction_type_3(Chip8* chip8, const uint16_t instruction) {
    uint8_t lower_byte = NN(instruction);
    uint8_t index = X(instruction);
    uint8_t reg_value = chip8->registers[index];

    if (reg_value == lower_byte)
        chip8->pc += 2;
}
void decode_instruction_type_4(Chip8* chip8, const uint16_t instruction) {
    uint8_t lower_byte = NN(instruction);
    uint8_t index = X(instruction);
    uint8_t reg_value = chip8->registers[index];

    if (reg_value != lower_byte)
        chip8->pc += 2;
}
void decode_instruction_type_5(Chip8* chip8, const uint16_t instruction) {
    uint8_t index_x = X(instruction);
    uint8_t index_y = Y(instruction);
    uint8_t reg_value_vx = chip8->registers[index_x];
    uint8_t reg_value_vy = chip8->registers[index_y];

    if (reg_value_vx == reg_value_vy)
        chip8->pc += 2;
}

void decode_instruction_type_6(Chip8* chip8, const uint16_t instruction) {
    uint16_t index = X(instruction);
    chip8->registers[index] = NN(instruction);
}

void decode_instruction_type_7(Chip8* chip8, const uint16_t instruction) {
    // TODO set carry flag if the addition will cause an overflow
    int index = X(instruction);
    chip8->registers[index] += NN(instruction);
}

void decode_instruction_type_8(Chip8* chip8, const uint16_t instruction) {
    uint8_t lowest_nibble = N(instruction); 
    uint8_t index_x = X(instruction);
    uint8_t index_y = Y(instruction);
    switch(lowest_nibble) {
        case 0:
            chip8->registers[index_x] = chip8->registers[index_y];
            break;
        case 1:
            chip8->registers[index_x] |= chip8->registers[index_y];
            break;
        case 2:
            chip8->registers[index_x] &= chip8->registers[index_y];
            break;
        case 3:
            chip8->registers[index_x] ^= chip8->registers[index_y];
            break;
        case 4:
            chip8->registers[index_x] += chip8->registers[index_y];
            break;
        case 5:
            chip8->registers[index_x] -= chip8->registers[index_y];
            chip8->vf = chip8->registers[index_y] > chip8->registers[index_x] ? 1 : 0;
        case 6:
            chip8->vf = chip8->registers[index_x] & 1;
            chip8->registers[index_x] >>= 1;
            break;
        case 7:
            chip8->registers[index_x] = chip8->registers[index_y] - chip8->registers[index_x];
            chip8->vf = chip8->registers[index_x] > chip8->registers[index_y] ? 0 : 1;
        case 8:
            chip8->vf = chip8->registers[index_x] & 0b10000000; 
            chip8->registers[index_x] <<= 1;
    }       

    
}


void decode_instruction_type_9(Chip8* chip8, const uint16_t instruction) {
    int index_x = X(instruction);
    int index_y = Y(instruction);

    if (chip8->registers[index_x] != chip8->registers[index_y])
        chip8->pc += 2;
}

void decode_instruction_type_A(Chip8* chip8, uint16_t instruction) {
    chip8->i_register = NNN(instruction);
}


void decode_instruction_type_B(Chip8* chip8, const uint16_t instruction) {

}

void decode_instruction_type_C(Chip8* chip8, const uint16_t instruction) {

}

void decode_instruction_type_D(Chip8* chip8, const uint16_t instruction) {
    int index_x = X(instruction);
    int index_y = Y(instruction);
    
    int sprite_height = N(instruction);

    uint8_t bit_rows[sprite_height];

    for (int i = 0; i < sprite_height; ++i)
    {
        bit_rows[i] = chip8->memory[chip8->i_register + i];
    }

    chip8->vf = 0;
    uint8_t x = (uint8_t) chip8->registers[index_x] % (WIDTH-1);
    uint8_t y = (uint8_t) chip8->registers[index_y] % (HEIGHT-1);

    draw(chip8, x, y, sprite_height, bit_rows);
}

void decode_instruction_type_E(Chip8* chip8, const uint16_t instruction) {

}
void decode_instruction_type_F(Chip8* chip8, const uint16_t instruction) {

}
