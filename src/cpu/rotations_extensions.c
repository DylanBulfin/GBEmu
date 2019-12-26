#include "internal.h"
#include "operations.h"
#include "arrays.h"

//Main extension processing
void cb_extensions(register_file_t *state) {
  uint8_t *code = &MEM(PC);
  (*cb_array[CB_INDEX])(state);
}

//Rotations
void rotate_left_carry_accumulator(register_file_t *state) {
  ZF = 0;
  NF = 0;
  HF = 0;
  CF = ((A >> 7) & 0x1);

  A = ((A << 1) | CF);
}

void rotate_right_carry_accumulator(register_file_t *state) {
  ZF = 0;
  NF = 0;
  HF = 0;
  CF = (A & 0x1);

  A = ((A >> 1) | (CF << 7));
}

void rotate_left_accumulator(register_file_t *state) {
  uint8_t new_carry = ((A >> 7) & 0x1);

  A = ((A << 1) | CF);

  ZF = 0;
  NF = 0;
  HF = 0;
  CF = new_carry;
}

void rotate_right_accumulator(register_file_t *state) {
  uint8_t new_carry = (A & 0x1);

  A = ((A >> 1) | (CF << 7));

  ZF = 0;
  NF = 0;
  HF = 0;
  CF = new_carry;
}

void rotate_left_carry_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  NF = 0;
  HF = 0;
  CF = ((*src >> 7) & 0x1);

  if(src == &M) {
    WRITE_MEM(VAL_HL,((*src << 1) | CF));
  } else {
    *src = ((*src << 1) | CF);
  }

  ZF = (*src == 0);
}

void rotate_right_carry_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  NF = 0;
  HF = 0;
  CF = (*src & 0x1);

  if(src == &M) {
    WRITE_MEM(VAL_HL,((*src >> 1) | (CF << 7)));
  } else {
    *src = ((*src >> 1) | (CF << 7));
  }

  ZF = (*src == 0);
}

void rotate_left_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  uint8_t new_carry = ((*src >> 7) & 0x1);

  if(src == &M) {
    WRITE_MEM(VAL_HL,((*src << 1) | CF));
  } else {
    *src = ((*src << 1) | CF);
  }

  ZF = (*src == 0);
  HF = 0;
  NF = 0;
  CF = new_carry;
}

void rotate_right_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  uint8_t new_carry = (*src & 0x1);

  if(src == &M) {
    WRITE_MEM(VAL_HL,((*src >> 1) | (CF << 7)));
  } else {
    *src = ((*src >> 1) | (CF << 7));
  }

  ZF = (*src == 0);
  HF = 0;
  NF = 0;
  CF = new_carry;
}

//Shift operations
void shift_left_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  HF = 0;
  NF = 0;
  CF = ((*src >> 7) & 0x1);

  if(src == &M) {
    WRITE_MEM(VAL_HL,((*src << 1) & (0xfe)));
  } else {
    *src = ((*src << 1) & (0xfe));
  }

  ZF = (*src == 0);
}

void shift_right_register_keep_msb(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  HF = 0;
  NF = 0;
  CF = (*src & 0x1);

  uint8_t msb = (*src & (1 << 7));

  if(src == &M) {
    WRITE_MEM(VAL_HL,((*src >> 1) | msb));
  } else {
    *src = ((*src >> 1) | msb);
  }

  ZF = (*src == 0);
}

void shift_right_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  HF = 0;
  NF = 0;
  CF = (*src & 0x1);

  if(src == &M) {
    WRITE_MEM(VAL_HL,((*src >> 1) & (0x7f)));
  } else {
    *src = ((*src >> 1) & (0x7f));
  }

  ZF = (*src == 0);
}

//Swap operation
void swap_nibbles_register(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);

  if(src == &M) {
    WRITE_MEM(VAL_HL,REFORM(LO_NIBBLE(*src),HI_NIBBLE(*src)));
  } else {
    *src = REFORM(LO_NIBBLE(*src),HI_NIBBLE(*src));
  }

  ZF = (*src == 0);
  HF = 0;
  NF = 0;
  CF = 0;
}

//Bit operations
void bit_ops_test_bit(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);
  uint8_t bit_index = DEST_REG_CODE(*code);

  uint8_t bit = ((*src >> bit_index) & 0x1);

  ZF = (bit == 0);
  NF = 0;
  HF = 1;
  CF = CF;
}

void bit_ops_set_bit(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);
  uint8_t bit_index = DEST_REG_CODE(*code);

  if(src == &M) {
    WRITE_MEM(VAL_HL,*src | (1 << bit_index));
  } else {
    *src = *src | (1 << bit_index);
  }
}

void bit_ops_reset_bit(register_file_t *state) {
  uint8_t *code = READ_MEM(PC+1);
  uint8_t *src = SRC_REG(*code);
  uint8_t bit_index = DEST_REG_CODE(*code);

  if(src == &M) {
    WRITE_MEM(VAL_HL,*src & (~(1 << bit_index)));
  } else {
    *src = *src & (~(1 << bit_index));
  }
}
