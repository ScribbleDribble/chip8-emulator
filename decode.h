#ifndef _DECODE_H
#define _DECODE_H

/**
 * gets the first nibble of the 16-bit instruction, which tells us the type of instruction
 */
int get_instruction_type(int instruction);

/**
 * for the classification of each of these instructions, we will be using the LS 12 bits of the 
 * 16 bit instruction as we already know the instruction type
 * 
 * returns
 * 0 - SYS addr
 * 1 - CKS
 * 2 - RET
 */
 int decode_instruction_type_0(int lower_instruction);
 
#endif
