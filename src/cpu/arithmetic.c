#include <stdio.h>
#include <stdlib.h>
#include "internal.h"
#include "operations.h"
#include "arrays.h"
#include "disassembler.h"

//8 Bit Arithmetic
void arithmetic_8_bit_add_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *src = SRC_REG(*code);
  int carry = CARRY & CF;
  uint16_t res = (((uint16_t) A) + ((uint16_t) *src) + ((uint16_t) carry));

  ZF = ((res & 0xff) == 0);
  NF = 0;
  CF = (res > 0xff);
  HF = ((((uint8_t) LO_NIBBLE(A)) + ((uint8_t) LO_NIBBLE(*src)) + ((uint8_t) carry)) > 0xf);

  A = res & 0xff;
}
    
void arithmetic_8_bit_add_immediate(register_file_t *state) {

  uint8_t *code = READ_MEM(PC);
  int carry = CARRY & CF;
  uint16_t res = (((uint16_t) A) + ((uint16_t) ARG1) + ((uint16_t) carry));

  ZF = ((res & 0xff) == 0);
  NF = 0;
  CF = (res > 0xff);
  HF = ((((uint8_t) LO_NIBBLE(A)) + ((uint8_t) LO_NIBBLE(ARG1)) + ((uint8_t) carry)) > 0xf);

  A = res & 0xff;
}

void arithmetic_8_bit_sub_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *src = SRC_REG(*code);
  int carry = CARRY & CF;
  uint8_t res = A - *src - carry;

  ZF = (res == 0);
  NF = 1;
  CF = ((((uint16_t)*src) + carry) > A);
  HF = ((LO_NIBBLE(*src) + carry) > LO_NIBBLE(A));

  A = res;
}

void arithmetic_8_bit_sub_immediate(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  int carry = CARRY & CF;
  uint8_t res = A - ARG1 - carry;

  ZF = (res == 0);
  NF = 1;
  CF = ((((uint16_t)ARG1) + carry) > A);
  HF = ((LO_NIBBLE(ARG1) + carry) > LO_NIBBLE(A));

  A = res;
}

void arithmetic_8_bit_and_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *src = SRC_REG(*code);
  uint8_t res = A & *src;

  ZF = (res == 0);
  NF = 0;
  HF = 1;
  CF = 0;

  A = res;
}

void arithmetic_8_bit_and_immediate(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t res = A & ARG1;

  ZF = (res == 0);
  NF = 0;
  HF = 1;
  CF = 0;

  A = res;
}

void arithmetic_8_bit_xor_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *src = SRC_REG(*code);
  uint8_t res = A ^ *src;

  ZF = (res == 0);
  NF = 0;
  HF = 0;
  CF = 0;

  A = res;
}

void arithmetic_8_bit_xor_immediate(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t res = A ^ ARG1;

  ZF = (res == 0);
  NF = 0;
  HF = 0;
  CF = 0;

  A = res;
}

void arithmetic_8_bit_or_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *src = SRC_REG(*code);
  uint8_t res = A | *src;

  ZF = (res == 0);
  NF = 0;
  HF = 0;
  CF = 0;

  A = res;
}

void arithmetic_8_bit_or_immediate(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t res = A | ARG1;

  ZF = (res == 0);
  NF = 0;
  HF = 0;
  CF = 0;

  A = res;
}

void arithmetic_8_bit_cp_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *src = SRC_REG(*code);
  uint8_t res = A - *src;

  ZF = (res == 0);
  NF = 1;
  CF = (*src > A);
  HF = (LO_NIBBLE(*src) > LO_NIBBLE(A));
}

void arithmetic_8_bit_cp_immediate(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t res = A - ARG1;

  ZF = (res == 0);
  NF = 1;
  CF = (ARG1 > A);
  HF = (LO_NIBBLE(ARG1) > LO_NIBBLE(A));
}

void arithmetic_8_bit_increment_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *dest = DEST_REG(*code);
  uint8_t res = *dest + 1;

  ZF = (res == 0);
  NF = 0;
  CF = CF;
  HF = ((((uint8_t) LO_NIBBLE(*dest)) + 1) > 0xf);

  if(dest == &M) {
    WRITE_MEM(VAL_HL,res);
  } else {
    *dest = res;
  }
}

void arithmetic_8_bit_decrement_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint8_t *dest = DEST_REG(*code);
  uint8_t res = *dest - 1;

  ZF = (res == 0);
  NF = 1;
  CF = CF;
  HF = (1 > LO_NIBBLE(*dest));

  if(dest == &M) {
    WRITE_MEM(VAL_HL,res);
  } else {
    if(dest == &B && PC == 0x1fe9) {
      //STATE;
      //printf("DECREMENTING B\n");
    }
    *dest = res;
  }
}

void arithmetic_8_bit_decimal_adjust_accumulator(register_file_t *state) {
  uint16_t correction = 0;

  if(NF) {
    if(HF) {
      correction += 0xfa;
    }
    if(CF) {
      correction += 0xa0;
    }
  } else {
    if((A & 0xf) > 0x9 || HF) {
      correction += 0x06;
    }
    if(((A + correction) & 0x1f0) > 0x90 || CF) {
      correction += 0x60;
      CF = 1;
    } else {
      CF = 0;
    }
  }

  A = (((uint16_t)A + correction) & 0xff);

  HF = 0;
    
  ZF = (A == 0);
}

void arithmetic_8_bit_complement_accumulator(register_file_t *state) {
  ZF = ZF;
  NF = 1;
  HF = 1;
  CF = CF;

  A = ~A;
}

void arithmetic_8_bit_set_carry_flag(register_file_t *state) {
  ZF = ZF;
  NF = 0;
  HF = 0;
  CF = 1;
}

void arithmetic_8_bit_complement_carry_flag(register_file_t *state) {
  ZF = ZF;
  NF = 0;
  HF = 0;
  CF = ((CF == 0) ? 1 : 0);
}


//16 Bit Arithmetic
void arithmetic_16_bit_add_hl_register_pair(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint16_t res = VAL_HL;
  uint16_t value;
  switch(REG_PAIR_CODE(*code)) {
  case CODE_BC:
    value = VAL_BC;
    break;
  case CODE_DE:
    value = VAL_DE;
    break;
  case CODE_HL:
    value = VAL_HL;
    break;
  case CODE_SP:
    value = SP;
    break;
  }

  res += value;

  ZF = ZF;
  NF = 0;
  CF = ((((uint32_t) VAL_HL) + ((uint32_t) value)) > 0xffff); 
  HF = (((VAL_HL & 0xfff) + (value & 0xfff)) > 0xfff);

  H = HI_BYTE(res);
  L = LO_BYTE(res);
}

void arithmetic_16_bit_add_sp_immediate(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);

  ZF = 0;
  NF = 0;
  CF = ((((uint16_t) LO_BYTE(SP)) + ((uint16_t) ARG1)) > 0xff);
  HF = ((((uint8_t) LO_NIBBLE(SP)) + ((uint8_t) LO_NIBBLE(ARG1))) > 0xf);

  SP += SE(ARG1);
}

void arithmetic_16_bit_increment_register_pair(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint16_t res;
  switch(REG_PAIR_CODE(*code)) {
  case CODE_SP:
    SP++;
    break;
  case CODE_BC:
    res = VAL_BC + 1;
    B = HI_BYTE(res);
    C = LO_BYTE(res);
    break;
  case CODE_DE:
    res = VAL_DE + 1;
    D = HI_BYTE(res);
    E = LO_BYTE(res);
    break;
  case CODE_HL:
    res = VAL_HL + 1;
    H = HI_BYTE(res);
    L = LO_BYTE(res);
    break;
  }
}

void arithmetic_16_bit_decrement_register_pair(register_file_t *state) {
  uint8_t *code = READ_MEM(PC);
  uint16_t res;
  switch(REG_PAIR_CODE(*code)) {
  case CODE_SP:
    SP--;
    break;
  case CODE_BC:
    res = VAL_BC - 1;
    B = HI_BYTE(res);
    C = LO_BYTE(res);
    break;
  case CODE_DE:
    res = VAL_DE - 1;
    D = HI_BYTE(res);
    E = LO_BYTE(res);
    break;
  case CODE_HL:
    res = VAL_HL - 1;
    H = HI_BYTE(res);
    L = LO_BYTE(res);
    break;
  }
}

