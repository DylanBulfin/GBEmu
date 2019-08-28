#pragma once

#include "internal.h"

//Operation function prototypes
void unimplemented_instruction(register_file_t*);
void unused_instruction(register_file_t*);

void load_8_bit_register_immediate(register_file_t*);
void load_8_bit_register_register(register_file_t*);
void load_8_bit_accumulator_reference(register_file_t*);
void load_8_bit_reference_accumulator(register_file_t*);
void load_8_bit_accumulator_reference_inc(register_file_t*);
void load_8_bit_reference_accumulator_inc(register_file_t*);
void load_8_bit_accumulator_reference_dec(register_file_t*);
void load_8_bit_reference_accumulator_dec(register_file_t*);

void load_16_bit_register_pair_immediate(register_file_t*);
void load_16_bit_stack_pointer_hl(register_file_t*);
void load_16_bit_hl_stack_pointer(register_file_t*);
void load_16_bit_reference_stack_pointer(register_file_t*);
void load_16_bit_push_register_pair(register_file_t*);
void load_16_bit_pop_register_pair(register_file_t*);

void arithmetic_8_bit_add_register(register_file_t*);
void arithmetic_8_bit_add_immediate(register_file_t*);
void arithmetic_8_bit_sub_register(register_file_t*);
void arithmetic_8_bit_sub_immediate(register_file_t*);
void arithmetic_8_bit_and_register(register_file_t*);
void arithmetic_8_bit_and_immediate(register_file_t*);
void arithmetic_8_bit_xor_register(register_file_t*);
void arithmetic_8_bit_xor_immediate(register_file_t*);
void arithmetic_8_bit_or_register(register_file_t*);
void arithmetic_8_bit_or_immediate(register_file_t*);
void arithmetic_8_bit_cp_register(register_file_t*);
void arithmetic_8_bit_cp_immediate(register_file_t*);
void arithmetic_8_bit_increment_register(register_file_t*);
void arithmetic_8_bit_decrement_register(register_file_t*);
void arithmetic_8_bit_decimal_adjust_accumulator(register_file_t*);
void arithmetic_8_bit_complement_accumulator(register_file_t*);
void arithmetic_8_bit_set_carry_flag(register_file_t*);
void arithmetic_8_bit_complement_carry_flag(register_file_t*);

void arithmetic_16_bit_add_hl_register_pair(register_file_t*);
void arithmetic_16_bit_add_sp_immediate(register_file_t*);
void arithmetic_16_bit_increment_register_pair(register_file_t*);
void arithmetic_16_bit_decrement_register_pair(register_file_t*);

void control_flow_jump_immediate_unconditional(register_file_t*);
void control_flow_jump_immediate_conditional(register_file_t*);
void control_flow_jump_relative_unconditional(register_file_t*);
void control_flow_jump_relative_conditional(register_file_t*);
void control_flow_jump_hl_reference(register_file_t*);
void control_flow_call_method_unconditional(register_file_t*);
void control_flow_call_method_conditional(register_file_t*);
void control_flow_return_unconditional(register_file_t*);
void control_flow_return_conditional(register_file_t*);
void control_flow_return_enable_interrupts(register_file_t*);
void control_flow_restart_routine(register_file_t*);

void misc_no_operation(register_file_t*);
void misc_enable_interrupts(register_file_t*);
void misc_disable_interrupts(register_file_t*);
void misc_halt_operation(register_file_t*);
void misc_stop_operation(register_file_t*);

void rotate_left_carry_accumulator(register_file_t*);
void rotate_left_accumulator(register_file_t*);
void rotate_right_carry_accumulator(register_file_t*);
void rotate_right_accumulator(register_file_t*);
void rotate_left_carry_register(register_file_t*);
void rotate_left_register(register_file_t*);
void rotate_right_carry_register(register_file_t*);
void rotate_right_register(register_file_t*);

void shift_left_register(register_file_t*);
void shift_right_register_keep_msb(register_file_t*);
void shift_right_register(register_file_t*);

void swap_nibbles_register(register_file_t*); //in rotations_extensions.c

void bit_ops_test_bit(register_file_t*);
void bit_ops_set_bit(register_file_t*);
void bit_ops_reset_bit(register_file_t*);

void cb_extensions(register_file_t*);


//Abbreviation macros
#define U_I            unimplemented_instruction
#define UNUSED         unused_instruction

#define LD_8_R_I       load_8_bit_register_immediate
#define LD_8_R_R       load_8_bit_register_register
#define LD_8_A_R       load_8_bit_accumulator_reference
#define LD_8_R_A       load_8_bit_reference_accumulator
#define LD_8_A_R_I     load_8_bit_accumulator_reference_inc
#define LD_8_R_A_I     load_8_bit_reference_accumulator_inc
#define LD_8_A_R_D     load_8_bit_accumulator_reference_dec
#define LD_8_R_A_D     load_8_bit_reference_accumulator_dec

#define LD_16_RP_I     load_16_bit_register_pair_immediate
#define LD_16_SP_H     load_16_bit_stack_pointer_hl
#define LD_16_H_SP     load_16_bit_hl_stack_pointer
#define LD_16_R_SP     load_16_bit_reference_stack_pointer
#define LD_16_PU_RP    load_16_bit_push_register_pair
#define LD_16_PO_RP    load_16_bit_pop_register_pair

#define AR_8_ADD_R     arithmetic_8_bit_add_register
#define AR_8_ADD_I     arithmetic_8_bit_add_immediate
#define AR_8_SUB_R     arithmetic_8_bit_sub_register
#define AR_8_SUB_I     arithmetic_8_bit_sub_immediate
#define AR_8_AND_R     arithmetic_8_bit_and_register
#define AR_8_AND_I     arithmetic_8_bit_and_immediate
#define AR_8_XOR_R     arithmetic_8_bit_xor_register
#define AR_8_XOR_I     arithmetic_8_bit_xor_immediate
#define AR_8_OR_R      arithmetic_8_bit_or_register
#define AR_8_OR_I      arithmetic_8_bit_or_immediate
#define AR_8_CP_R      arithmetic_8_bit_cp_register
#define AR_8_CP_I      arithmetic_8_bit_cp_immediate
#define AR_8_I_R       arithmetic_8_bit_increment_register
#define AR_8_D_R       arithmetic_8_bit_decrement_register
#define AR_8_DA_A      arithmetic_8_bit_decimal_adjust_accumulator
#define AR_8_C_A       arithmetic_8_bit_complement_accumulator
#define AR_8_S_CF      arithmetic_8_bit_set_carry_flag
#define AR_8_C_CF      arithmetic_8_bit_complement_carry_flag

#define AR_16_A_HL_RP  arithmetic_16_bit_add_hl_register_pair
#define AR_16_A_SP_I   arithmetic_16_bit_add_sp_immediate
#define AR_16_I_RP     arithmetic_16_bit_increment_register_pair
#define AR_16_D_RP     arithmetic_16_bit_decrement_register_pair

#define CF_J_I_U       control_flow_jump_immediate_unconditional
#define CF_J_I_C       control_flow_jump_immediate_conditional
#define CF_J_R_U       control_flow_jump_relative_unconditional
#define CF_J_R_C       control_flow_jump_relative_conditional
#define CF_J_HL_R      control_flow_jump_hl_reference
#define CF_C_M_U       control_flow_call_method_unconditional
#define CF_C_M_C       control_flow_call_method_conditional
#define CF_R_U         control_flow_return_unconditional
#define CF_R_C         control_flow_return_conditional
#define CF_R_EI        control_flow_return_enable_interrupts
#define CF_RES_R       control_flow_restart_routine

#define MI_NO_OP       misc_no_operation
#define MI_EN_I        misc_enable_interrupts
#define MI_DI_I        misc_disable_interrupts
#define MI_HA_O        misc_halt_operation
#define MI_ST_O        misc_stop_operation

#define RO_LC_A        rotate_left_carry_accumulator
#define RO_L_A         rotate_left_accumulator
#define RO_RC_A        rotate_right_carry_accumulator
#define RO_R_A         rotate_right_accumulator
#define RO_LC_R        rotate_left_carry_register
#define RO_L_R         rotate_left_register
#define RO_RC_R        rotate_right_carry_register
#define RO_R_R         rotate_right_register

#define SH_L_R         shift_left_register
#define SH_R_R_K       shift_right_register_keep_msb
#define SH_R_R         shift_right_register

#define SW_N_R         swap_nibbles_register 

#define BO_T_B         bit_ops_test_bit
#define BO_S_B         bit_ops_set_bit
#define BO_R_B         bit_ops_reset_bit

#define CB_EXT         cb_extensions

//Helper functions
uint16_t sign_extend(uint8_t);
int eval_condition(uint8_t, register_file_t*);

//Other helpful macros
#define SE(num) sign_extend(num)
#define COND(opcode) eval_condition(CONDITION(opcode), state)
#define ARG1 code[1]
#define ARG2 code[2]
#define HI_BYTE(num)   ((num>>8)&0xff)
#define LO_BYTE(num)   (num&0xff)
#define LO_NIBBLE(num) (num&0xf)
#define HI_NIBBLE(num) ((num>>4)&0xf)
#define CARRY ((*code>>3)&0x1)
#define TC(num) ((~num)+1)
#define TC_NIBBLE(num) (((~num)+1)&0xf)
#define CB_INDEX (code[1]>>3)
#define REFORM(hi_nib,lo_nib) ((hi_nib<<4)|lo_nib)
