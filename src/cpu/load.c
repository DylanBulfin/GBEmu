#include <stdlib.h>
#include "internal.h"
#include "operations.h"

//8 bit loads
void load_8_bit_register_immediate(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
    
  uint8_t *dest_reg = DEST_REG(*code);
  if(dest_reg == &M) {
    WRITE_MEM(VAL_HL,ARG1);
  } else {
    *dest_reg = ARG1;
  }
}

void load_8_bit_register_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
    
  uint8_t *dest_reg = DEST_REG(*code);
  uint8_t *src_reg = SRC_REG(*code);

  if(dest_reg == &M) {
    WRITE_MEM(VAL_HL,*src_reg);
  } else {
    *dest_reg = *src_reg;
  }
}

void load_8_bit_accumulator_reference(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);

  uint16_t addr = 0;

  switch(*code) {
  case 0x0a:
    addr = VAL_BC;
    break;
  case 0x1a:
    addr = VAL_DE;
    break;
  case 0xfa:
    addr = VAL_NN(ARG2,ARG1);
    break;
  case 0xf2:
    addr = 0xff00u + C;
    break;
  case 0xf0:
    addr = 0xff00u + ARG1;
    break;
  default:
    unimplemented_instruction(state);
    break;
  }

  A = *READ_MEM(addr);
}

void load_8_bit_reference_accumulator(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);

  uint16_t addr = 0;

  switch(*code) {
  case 0x02:
    addr = VAL_BC;
    break;
  case 0x12:
    addr = VAL_DE;
    break;
  case 0xea:
    addr = VAL_NN(ARG2,ARG1);
    break;
  case 0xe2:
    addr = 0xff00u + C;
    break;
  case 0xe0:
    addr = 0xff00u + ARG1;
    break;
  default:
    unimplemented_instruction(state);
    break;
  }

  WRITE_MEM(addr,A);
}

void load_8_bit_accumulator_reference_inc(register_file_t *state) {
  A = M;
  uint16_t res = VAL_HL + 1;
  H = HI_BYTE(res);
  L = LO_BYTE(res);
}
    
void load_8_bit_reference_accumulator_inc(register_file_t *state) {
  if(PC == 0x1ffe) {
    //	STATE;
  }
  WRITE_MEM(VAL_HL, A);
  uint16_t res = VAL_HL + 1;
  H = HI_BYTE(res);
  L = LO_BYTE(res);
}

void load_8_bit_accumulator_reference_dec(register_file_t *state) {
  A = M;
  uint16_t res = VAL_HL - 1;
  H = HI_BYTE(res);
  L = LO_BYTE(res);
}

void load_8_bit_reference_accumulator_dec(register_file_t *state) {
  WRITE_MEM(VAL_HL, A);
  uint16_t res = VAL_HL - 1;
  H = HI_BYTE(res);
  L = LO_BYTE(res);
}


//16 bit loads
void load_16_bit_register_pair_immediate(register_file_t* state) {
  uint8_t *code = READ_MEM(PC);

  switch(REG_PAIR_CODE(*code)) {
  case CODE_BC:
    B = ARG2;
    C = ARG1;
    break;
  case CODE_DE:
    D = ARG2;
    E = ARG1;
    break;
  case CODE_HL:
    H = ARG2;
    L = ARG1;
    break;
  case CODE_SP:
    SP = VAL_NN(ARG2,ARG1);
    break;
  }
}

void load_16_bit_stack_pointer_hl(register_file_t *state) {
  SP = VAL_HL;
}

void load_16_bit_hl_stack_pointer(register_file_t *state){
  uint8_t *code = READ_MEM(PC);
  uint16_t res = SP + SE(ARG1);

  ZF = 0;
  NF = 0;
  CF = (((LO_BYTE(SP)) + ((uint16_t) ARG1)) > 0xff);
  HF = ((LO_NIBBLE(SP) + LO_NIBBLE(ARG1)) > 0xf);

  H = HI_BYTE(res);
  L = LO_BYTE(res);
}

void load_16_bit_reference_stack_pointer(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint16_t addr = VAL_NN(ARG2,ARG1);
  WRITE_MEM(addr,LO_BYTE(SP));
  WRITE_MEM(addr+1,HI_BYTE(SP));
}

void load_16_bit_push_register_pair(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t lo_byte = 0;
  uint8_t hi_byte = 0;
  switch(REG_PAIR_CODE(*code)) {
  case CODE_BC:
    lo_byte = C;
    hi_byte = B;
    break;
  case CODE_DE:
    lo_byte = E;
    hi_byte = D;
    break;
  case CODE_HL:
    lo_byte = L;
    hi_byte = H;
    break;
  case CODE_AF:
    lo_byte = VAL_FLAGS;
    hi_byte = A;
    break;
  }

  WRITE_MEM((SP-2),lo_byte);
  WRITE_MEM((SP-1),hi_byte);

  SP -= 2;
}

void load_16_bit_pop_register_pair(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t lo_byte = *READ_MEM((SP));
  uint8_t hi_byte = *READ_MEM((SP+1));

  switch(REG_PAIR_CODE(*code)) {
  case CODE_BC:
    B = hi_byte;
    C = lo_byte;
    break;
  case CODE_DE:
    D = hi_byte;
    E = lo_byte;
    break;
  case CODE_HL:
    H = hi_byte;
    L = lo_byte;
    break;
  case CODE_AF:
    A = hi_byte;
    SET_FLAGS(lo_byte);
    break;
  }

  SP += 2;
}
