#include <stdlib.h>
#include <stdio.h>
#include "../timing/clock.h"
#include "internal.h"
#include "operations.h"
#include "disassembler.h"

void unimplemented_instruction(register_file_t *state) {
    printf("\nInstruction not implemented:");
    STATE;
    exit(1);
}

void unused_instruction(register_file_t *state) {
    printf("\nThis instruction should never occur, opcode = 0x%02x\n", MEM(PC));
    STATE;
    exit(1);
}

uint8_t *decode_reg(uint8_t reg_code, register_file_t *state) {
    uint8_t *ret = 0;
    switch(reg_code) {
    case CODE_B:
	ret = &B;
	break;
    case CODE_C:
	ret = &C;
	break;
    case CODE_D:
	ret = &D;
	break;
    case CODE_E:
	ret = &E;
	break;
    case CODE_H:
	ret = &H;
	break;
    case CODE_L:
	ret = &L;
	break;
    case CODE_M:
	ret = &M;
	break;
    case CODE_A:
	ret = &A;
	break;
    }
    return ret;
}

void print_state(register_file_t *state) {
    printf("\nA: 0x%02x, B: 0x%02x, C: 0x%02x, D: 0x%02x, E: 0x%02x, H: 0x%02x, L: 0x%02x, M: 0x%02x\n"
	   "PC: 0x%04x, SP: 0x%04x, ZF: %d, NF: %d, HF: %d, CF: %d\n"
	   "Current Instruction: %s, Opcode = 0x%02x\n\n",
	   A, B, C, D, E, H, L, M, PC, SP, ZF, NF, HF, CF, disassemble(state), (MEM(PC) == 0xcb) ? MEM(PC+1) : MEM(PC));
}

void write_state_to_file(FILE *f, register_file_t *state) {
    fprintf(f, "PC: 0x%04x, P1: 0x%02x, Current instruction: %s\n", PC, MEM(P1), disassemble(state));
}

uint16_t sign_extend(uint8_t num) {
    if(num > 0x7f) {
	return 0xff00 | num;
    } else {
	return (uint16_t) num;
    }
}

int eval_condition(uint8_t cond_code, register_file_t *state) {
    switch(cond_code) {
    case CODE_NZF:
	return (!ZF);
	break;
    case CODE_ZF:
	return (ZF);
	break;
    case CODE_NCF:
	return (!CF);
	break;
    case CODE_CF:
	return (CF);
	break;
    }
    printf("eval_condition failed, %x invalid arg\n\n", cond_code);
    exit(1);
}

void set_register_pair(uint16_t value, uint8_t reg_pair_code, register_file_t *state) {
    switch(reg_pair_code) {
    case CODE_BC:
	B = HI_BYTE(value);
	C = LO_BYTE(value);
	break;
    case CODE_DE:
	D = HI_BYTE(value);
	E = LO_BYTE(value);
	break;
    case CODE_HL:
	H = HI_BYTE(value);
	L = LO_BYTE(value);
	break;
    default:
	printf("\nERROR in set_register_pair\n");
	break;
    }
}

void set_flags(uint8_t value, register_file_t *state) {
    ZF = BIT(Z_BIT,value);
    NF = BIT(N_BIT,value);
    HF = BIT(H_BIT,value);
    CF = BIT(C_BIT,value);
}
