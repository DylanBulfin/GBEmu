#pragma once

#include <stdint.h>
#include <stdio.h>

typedef struct condition_codes {
    uint8_t z:1;
    uint8_t n:1;
    uint8_t h:1;
    uint8_t c:1;

    uint8_t unused:4;
} condition_codes_t;

typedef struct register_file {
    uint8_t a;
    
    uint8_t b;
    uint8_t c;
    
    uint8_t d;
    uint8_t e;
    
    uint8_t h;
    uint8_t l;

    uint16_t sp;
    uint16_t pc;

    uint8_t *memory;

    struct condition_codes cc;

    uint8_t int_master_enable;
} register_file_t;

condition_codes_t cc;
register_file_t rf;

//Helper function prototypes
uint8_t *decode_reg(uint8_t, register_file_t*);
void print_state(register_file_t*);
void write_state_to_file(FILE *f, register_file_t *state);
void set_register_pair(uint16_t,uint8_t,register_file_t*);
void set_flags(uint8_t,register_file_t*);
void write_memory(uint16_t,uint8_t,register_file_t*);
uint8_t *read_memory(uint16_t,register_file_t*);

void print_mem_range(uint16_t,uint16_t,register_file_t*);


//HALT mode
extern int8_t is_halted;
extern int8_t halt_mode;
#define HALT_MODE_ENABLED 0
#define HALT_MODE_DISABLED 1
#define HALT(mode) is_halted=1;halt_mode=mode
#define UNHALT is_halted=0;halt_mode=-1


extern int8_t quit;
extern int8_t in_bios;
extern int8_t in_dma;


//Interrupt insruction helpers
extern int8_t ei_pending;
extern int8_t di_pending;


//Memory Access
#define MEM(loc) state->memory[loc]
#define READ_MEM(loc) read_memory(loc,state)
#define WRITE_MEM(loc,val) write_memory(loc,val,state)


//Register Pair macros
#define VAL_HL        (((uint16_t)state->h<<8)+state->l)
#define VAL_BC        (((uint16_t)state->b<<8)+state->c)
#define VAL_DE        (((uint16_t)state->d<<8)+state->e)
#define VAL_NN(n1,n2) (((uint16_t)n1<<8)+n2)


//Normal Register macros
#define A     state->a
#define B     state->b
#define C     state->c
#define D     state->d
#define E     state->e
#define H     state->h
#define L     state->l
#define M     MEM(VAL_HL)

#define SP    state->sp
#define PC    state->pc

#define CC    state->cc
#define ZF    state->cc.z
#define NF    state->cc.n
#define HF    state->cc.h
#define CF    state->cc.c

#define IME   state->int_master_enable


//Special Register macros
#define P1    0xff00
#define SB    0xff01
#define SC    0xff02
#define DIV   0xff04
#define TIMA  0xff05
#define TMA   0xff06
#define TAC   0xff07
#define IF    0xff0f

#define NR10  0xff10
#define NR11  0xff11
#define NR12  0xff12
#define NR13  0xff13
#define NR14  0xff14
#define NR21  0xff16
#define NR22  0xff17
#define NR23  0xff18
#define NR24  0xff19
#define NR30  0xff1a
#define NR31  0xff1b
#define NR32  0xff1c
#define NR33  0xff1d
#define NR34  0xff1e
#define NR41  0xff20
#define NR42  0xff21
#define NR43  0xff22
#define NR44  0xff23
#define NR50  0xff24
#define NR51  0xff25
#define NR52  0xff26

#define LCDC  0xff40
#define STAT  0xff41
#define SCY   0xff42
#define SCX   0xff43
#define LY    0xff44
#define LYC   0xff45
#define DMA   0xff46
#define BGP   0xff47
#define OBP0  0xff48
#define OBP1  0xff49
#define WY    0xff4a
#define WX    0xff4b
#define VBK   0xff4f

#define IE    0xffff


//Register Code macros
#define CODE_B  0x0
#define CODE_C  0x1
#define CODE_D  0x2
#define CODE_E  0x3
#define CODE_H  0x4
#define CODE_L  0x5
#define CODE_M  0x6
#define CODE_A  0x7


//Register Pair Code macros
#define CODE_BC 0x0
#define CODE_DE 0x1
#define CODE_HL 0x2

#define CODE_AF 0x3
#define CODE_SP 0x3


//Condition Test Code macros
#define CODE_NZF 0x0
#define CODE_ZF  0x1
#define CODE_NCF 0x2
#define CODE_CF  0x3


//Register Decoding macros
#define SRC_REG_CODE(opcode)  (opcode&0x7)
#define DEST_REG_CODE(opcode) ((opcode>>3)&0x7)
#define SRC_REG(opcode)       decode_reg(SRC_REG_CODE(opcode),state)
#define DEST_REG(opcode)      decode_reg(DEST_REG_CODE(opcode),state)
#define REG_PAIR_CODE(opcode) ((opcode>>4)&0x3)
#define CONDITION(opcode)     ((opcode>>3)&0x3)


//Other helpful macros
#define STATE print_state(state)
#define VAL_FLAGS ((ZF<<7)+(NF<<6)+(HF<<5)+(CF<<4))
#define SET_FLAGS(value) set_flags(value,state)
#define BIT(bit,value) ((value>>bit)&0x1)
#define Z_BIT 7
#define N_BIT 6
#define H_BIT 5
#define C_BIT 4
