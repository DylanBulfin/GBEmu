#include "arrays.h"
#include "internal.h"

const void (*func_array[256])(register_file_t*) =
    {MI_NO_OP, LD_16_RP_I, LD_8_R_A, AR_16_I_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, RO_LC_A,
     LD_16_R_SP, AR_16_A_HL_RP, LD_8_A_R, AR_16_D_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, RO_RC_A,

     MI_ST_O, LD_16_RP_I, LD_8_R_A, AR_16_I_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, RO_L_A,
     CF_J_R_U, AR_16_A_HL_RP, LD_8_A_R, AR_16_D_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, RO_R_A,

     CF_J_R_C, LD_16_RP_I, LD_8_R_A_I, AR_16_I_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, AR_8_DA_A,
     CF_J_R_C, AR_16_A_HL_RP, LD_8_A_R_I, AR_16_D_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, AR_8_C_A,

     CF_J_R_C, LD_16_RP_I, LD_8_R_A_D, AR_16_I_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, AR_8_S_CF,
     CF_J_R_C, AR_16_A_HL_RP, LD_8_A_R_D, AR_16_D_RP, AR_8_I_R, AR_8_D_R, LD_8_R_I, AR_8_C_CF,
     

     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R,
     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R,

     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R,
     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R,

     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R,
     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R,

     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, MI_HA_O, LD_8_R_R,
     LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R, LD_8_R_R,


     AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R,
     AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R, AR_8_ADD_R,

     AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, 
     AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, AR_8_SUB_R, 

     AR_8_AND_R, AR_8_AND_R, AR_8_AND_R, AR_8_AND_R, AR_8_AND_R, AR_8_AND_R, AR_8_AND_R, AR_8_AND_R, 
     AR_8_XOR_R, AR_8_XOR_R, AR_8_XOR_R, AR_8_XOR_R, AR_8_XOR_R, AR_8_XOR_R, AR_8_XOR_R, AR_8_XOR_R, 

     AR_8_OR_R, AR_8_OR_R, AR_8_OR_R, AR_8_OR_R, AR_8_OR_R, AR_8_OR_R, AR_8_OR_R, AR_8_OR_R, 
     AR_8_CP_R, AR_8_CP_R, AR_8_CP_R, AR_8_CP_R, AR_8_CP_R, AR_8_CP_R, AR_8_CP_R, AR_8_CP_R, 


     CF_R_C, LD_16_PO_RP, CF_J_I_C, CF_J_I_U, CF_C_M_C, LD_16_PU_RP, AR_8_ADD_I, CF_RES_R,
     CF_R_C, CF_R_U, CF_J_I_C, CB_EXT, CF_C_M_C, CF_C_M_U, AR_8_ADD_I, CF_RES_R,

     CF_R_C, LD_16_PO_RP, CF_J_I_C, UNUSED, CF_C_M_C, LD_16_PU_RP, AR_8_SUB_I, CF_RES_R,
     CF_R_C, CF_R_EI, CF_J_I_C, UNUSED, CF_C_M_C, UNUSED, AR_8_SUB_I, CF_RES_R,

     LD_8_R_A, LD_16_PO_RP, LD_8_R_A, UNUSED, UNUSED, LD_16_PU_RP, AR_8_AND_I, CF_RES_R,
     AR_16_A_SP_I, CF_J_HL_R, LD_8_R_A, UNUSED, UNUSED, UNUSED, AR_8_XOR_I, CF_RES_R,

     LD_8_A_R, LD_16_PO_RP, LD_8_A_R, MI_DI_I, UNUSED, LD_16_PU_RP, AR_8_OR_I, CF_RES_R,
     LD_16_H_SP, LD_16_SP_H, LD_8_A_R, MI_EN_I, UNUSED, UNUSED, AR_8_CP_I, CF_RES_R};

const void (*cb_array[32])(register_file_t*) =
    {RO_LC_R, RO_RC_R, RO_L_R, RO_R_R, SH_L_R, SH_R_R_K, SW_N_R, SH_R_R,
     BO_T_B, BO_T_B, BO_T_B, BO_T_B, BO_T_B, BO_T_B, BO_T_B, BO_T_B, 
     BO_R_B, BO_R_B, BO_R_B, BO_R_B, BO_R_B, BO_R_B, BO_R_B, BO_R_B, 
     BO_S_B, BO_S_B, BO_S_B, BO_S_B, BO_S_B, BO_S_B, BO_S_B, BO_S_B};

const int num_args[256] =
    {0, 2, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 1, 0,
     0, 2, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 1, 0,
     -1, 2, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 1, 0,
     -1, 2, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 0, 1, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     -1, 0, -1, -1, -1, 0, 1, -1, -1, -1, -1, 1, -1, -1, 1, -1,
     -1, 0, -1, 0, -1, 0, 1, -1, -1, -1, -1, 0, -1, 0, 1, -1,
     1, 0, 0, 0, 0, 0, 1, -1, 1, -1, 2, 0, 0, 0, 1, -1,
     1, 0, 0, 0, 0, 0, 1, -1, 1, 0, 2, 0, 0, 0, 1, -1};

const char* reg_ops[256] =
    {"NOP", "LD BC,0x%02x%02x", "LD (BC),A", "INC BC", "INC B", "DEC B", "LD B,0x%02x", "RLCA",
     "LD (0x%02x%02x),SP", "ADD HL,BC", "LD A,(BC)", "DEC BC", "INC C", "DEC C", "LD C,0x%02x", "RRCA",

     "STOP 0", "LD DE,0x%02x%02x", "LD (DE),A", "INC DE", "INC D", "DEC D", "LD D,0x%02x", "RLA",
     "JR 0x%02x", "ADD HL,DE", "LD A,(DE)", "DEC DE", "INC E", "DEC E", "LD E,0x%02x", "RRA",

     "JR NZ,0x%02x", "LD HL,0x%02x%02x", "LD (HL+),A", "INC HL", "INC H", "DEC H", "LD H,0x%02x", "DAA",
     "JR Z,0x%02x", "ADD HL,HL", "LD A,(HL+)", "DEC HL", "INC L", "DEC L", "LD L,0x%02x", "CPL",

     "JR NC,0x%02x", "LD SP,0x%02x%02x", "LD (HL-),A", "INC SP", "INC (HL)", "DEC (HL)", "LD (HL),0x%02x", "SCF",
     "JR C,0x%02x", "ADD HL,SP", "LD A,(HL-)", "DEC SP", "INC A", "DEC A", "LD A,0x%02x", "CCF",


     "LD B,B", "LD B,C", "LD B,D", "LD B,E", "LD B,H", "LD B,L", "LD B,(HL)", "LD B,A",
     "LD C,B", "LD C,C", "LD C,D", "LD C,E", "LD C,H", "LD C,L", "LD C,(HL)", "LD C,A",

     "LD D,B", "LD D,C", "LD D,D", "LD D,E", "LD D,H", "LD D,L", "LD D,(HL)", "LD D,A",
     "LD E,B", "LD E,C", "LD E,D", "LD E,E", "LD E,H", "LD E,L", "LD E,(HL)", "LD E,A",
     
     "LD H,B", "LD H,C", "LD H,D", "LD H,E", "LD H,H", "LD H,L", "LD H,(HL)", "LD H,A",
     "LD L,B", "LD L,C", "LD L,D", "LD L,E", "LD L,H", "LD L,L", "LD L,(HL)", "LD L,A",

     "LD (HL),B", "LD (HL),C", "LD (HL),D", "LD (HL),E", "LD (HL),H", "LD (HL),L", "HALT", "LD (HL),A",
     "LD A,B", "LD A,C", "LD A,D", "LD A,E", "LD A,H", "LD A,L", "LD A,(HL)", "LD A,A",


     "ADD A,B", "ADD A,C", "ADD A,D", "ADD A,E", "ADD A,H", "ADD A,L", "ADD A,(HL)", "ADD A,A",
     "ADC A,B", "ADC A,C", "ADC A,D", "ADC A,E", "ADC A,H", "ADC A,L", "ADC A,(HL)", "ADC A,A",

     "SUB B", "SUB C", "SUB D", "SUB E", "SUB H", "SUB L", "SUB (HL)", "SUB A",
     "SBC A,B", "SBC A,C", "SBC A,D", "SBC A,E", "SBC A,H", "SBC A,L", "SBC A,(HL)", "SBC A,A",

     "AND B", "AND C", "AND D", "AND E", "AND H", "AND L", "AND (HL)", "AND A",
     "XOR B", "XOR C", "XOR D", "XOR E", "XOR H", "XOR L", "XOR (HL)", "XOR A",

     "OR B", "OR C", "OR D", "OR E", "OR H", "OR L", "OR (HL)", "OR A",
     "CP B", "CP C", "CP D", "CP E", "CP H", "CP L", "CP (HL)", "CP A",


     "RET NZ", "POP BC", "JP NZ,0x%02x%02x", "JP 0x%02x%02x", "CALL NZ,0x%02x%02x", "PUSH BC", "ADD A,0x%02x", "RST 0x00",
     "RET Z", "RET", "JP Z,0x%02x%02x", "CB %02x", "CALL Z,0x%02x%02x", "CALL 0x%02x%02x", "ADC A,0x%02x", "RST 0x08",

     "RET NC", "POP DE", "JP NC,0x%02x%02x", 0, "CALL NC,0x%02x%02x", "PUSH DE", "SUB 0x%02x", "RST 0x10",
     "RET C", "RETI", "JP C,0x%02x%02x", 0, "CALL C,0x%02x%02x", 0, "SBC A,0x%02x", "RST 0x18",

     "LDH (0x%02x),A", "POP HL", "LD (C),A", 0, 0, "PUSH HL", "AND 0x%02x", "RST 0x20",
     "ADD SP,0x%02x", "JP (HL)", "LD (0x%02x%02x),A", 0, 0, 0, "XOR 0x%02x", "RST 0x28",

     "LDH A,(0x%02x)", "POP AF", "LD A,(C)", "DI", 0, "PUSH AF", "OR 0x%02x", "RST 0x30",
     "LD HL,SP + 0x%02x", "LD SP,HL", "LD A,(0x%02x%02x)", "EI", 0, 0, "CP 0x%02x", "RST 0x38"};

const char *ext_ops[256] =
    {"RLC B", "RLC C", "RLC D", "RLC E", "RLC H", "RLC L", "RLC (HL)", "RLC A",
     "RRC B", "RRC C", "RRC D", "RRC E", "RRC H", "RRC L", "RRC (HL)", "RRC A",

     "RL B", "RL C", "RL D", "RL E", "RL H", "RL L", "RL (HL)", "RL A",
     "RR B", "RR C", "RR D", "RR E", "RR H", "RR L", "RR (HL)", "RR A",
     
     "SLA B", "SLA C", "SLA D", "SLA E", "SLA H", "SLA L", "SLA (HL)", "SLA A",
     "SRA B", "SRA C", "SRA D", "SRA E", "SRA H", "SRA L", "SRA (HL)", "SRA A",
     
     "SWAP B", "SWAP C", "SWAP D", "SWAP E", "SWAP H", "SWAP L", "SWAP (HL)", "SWAP A",
     "SRL B", "SRL C", "SRL D", "SRL E", "SRL H", "SRL L", "SRL (HL)", "SRL A",
     
     "BIT 0,B", "BIT 0,C", "BIT 0,D", "BIT 0,E", "BIT 0,H", "BIT 0,L", "BIT 0,(HL)", "BIT 0,A",
     "BIT 1,B", "BIT 1,C", "BIT 1,D", "BIT 1,E", "BIT 1,H", "BIT 1,L", "BIT 1,(HL)", "BIT 1,A",
     
     "BIT 2,B", "BIT 2,C", "BIT 2,D", "BIT 2,E", "BIT 2,H", "BIT 2,L", "BIT 2,(HL)", "BIT 2,A",
     "BIT 3,B", "BIT 3,C", "BIT 3,D", "BIT 3,E", "BIT 3,H", "BIT 3,L", "BIT 3,(HL)", "BIT 3,A",
     
     "BIT 4,B", "BIT 4,C", "BIT 4,D", "BIT 4,E", "BIT 4,H", "BIT 4,L", "BIT 4,(HL)", "BIT 4,A",
     "BIT 5,B", "BIT 5,C", "BIT 5,D", "BIT 5,E", "BIT 5,H", "BIT 5,L", "BIT 5,(HL)", "BIT 5,A",
     
     "BIT 6,B", "BIT 6,C", "BIT 6,D", "BIT 6,E", "BIT 6,H", "BIT 6,L", "BIT 6,(HL)", "BIT 6,A",
     "BIT 7,B", "BIT 7,C", "BIT 7,D", "BIT 7,E", "BIT 7,H", "BIT 7,L", "BIT 7,(HL)", "BIT 7,A",
     
     "RES 0,B", "RES 0,C", "RES 0,D", "RES 0,E", "RES 0,H", "RES 0,L", "RES 0,(HL)", "RES 0,A",
     "RES 1,B", "RES 1,C", "RES 1,D", "RES 1,E", "RES 1,H", "RES 1,L", "RES 1,(HL)", "RES 1,A",
     
     "RES 2,B", "RES 2,C", "RES 2,D", "RES 2,E", "RES 2,H", "RES 2,L", "RES 2,(HL)", "RES 2,A",
     "RES 3,B", "RES 3,C", "RES 3,D", "RES 3,E", "RES 3,H", "RES 3,L", "RES 3,(HL)", "RES 3,A",
     
     "RES 4,B", "RES 4,C", "RES 4,D", "RES 4,E", "RES 4,H", "RES 4,L", "RES 4,(HL)", "RES 4,A",
     "RES 5,B", "RES 5,C", "RES 5,D", "RES 5,E", "RES 5,H", "RES 5,L", "RES 5,(HL)", "RES 5,A",
     
     "RES 6,B", "RES 6,C", "RES 6,D", "RES 6,E", "RES 6,H", "RES 6,L", "RES 6,(HL)", "RES 6,A",
     "RES 7,B", "RES 7,C", "RES 7,D", "RES 7,E", "RES 7,H", "RES 7,L", "RES 7,(HL)", "RES 7,A",
     
     "SET 0,B", "SET 0,C", "SET 0,D", "SET 0,E", "SET 0,H", "SET 0,L", "SET 0,(HL)", "SET 0,A",
     "SET 1,B", "SET 1,C", "SET 1,D", "SET 1,E", "SET 1,H", "SET 1,L", "SET 1,(HL)", "SET 1,A",
     
     "SET 2,B", "SET 2,C", "SET 2,D", "SET 2,E", "SET 2,H", "SET 2,L", "SET 2,(HL)", "SET 2,A",
     "SET 3,B", "SET 3,C", "SET 3,D", "SET 3,E", "SET 3,H", "SET 3,L", "SET 3,(HL)", "SET 3,A",
     
     "SET 4,B", "SET 4,C", "SET 4,D", "SET 4,E", "SET 4,H", "SET 4,L", "SET 4,(HL)", "SET 4,A",
     "SET 5,B", "SET 5,C", "SET 5,D", "SET 5,E", "SET 5,H", "SET 5,L", "SET 5,(HL)", "SET 5,A",
     
     "SET 6,B", "SET 6,C", "SET 6,D", "SET 6,E", "SET 6,H", "SET 6,L", "SET 6,(HL)", "SET 6,A",
     "SET 7,B", "SET 7,C", "SET 7,D", "SET 7,E", "SET 7,H", "SET 7,L", "SET 7,(HL)", "SET 7,A"};

const uint8_t bios[256] =
    {0x31, 0xfe, 0xff, 0xaf, 0x21, 0xff, 0x9f, 0x32, 0xcb, 0x7c, 0x20, 0xfb, 0x21, 0x26, 0xff, 0x0e,
     0x11, 0x3e, 0x80, 0x32, 0xe2, 0x0c, 0x3e, 0xf3, 0xe2, 0x32, 0x3e, 0x77, 0x77, 0x3e, 0xfc, 0xe0,
     0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1a, 0xcd, 0x95, 0x00, 0xcd, 0x96, 0x00, 0x13, 0x7b,
     0xfe, 0x34, 0x20, 0xf3, 0x11, 0xd8, 0x00, 0x06, 0x08, 0x1a, 0x13, 0x22, 0x23, 0x05, 0x20, 0xf9,
     0x3e, 0x19, 0xea, 0x10, 0x99, 0x21, 0x2f, 0x99, 0x0e, 0x0c, 0x3d, 0x28, 0x08, 0x32, 0x0d, 0x20,
     0xf9, 0x2e, 0x0f, 0x18, 0xf3, 0x67, 0x3e, 0x64, 0x57, 0xe0, 0x42, 0x3e, 0x91, 0xe0, 0x40, 0x04,
     0x1e, 0x02, 0x0e, 0x0c, 0xf0, 0x44, 0xfe, 0x90, 0x20, 0xfa, 0x0d, 0x20, 0xf7, 0x1d, 0x20, 0xf2,
     0x0e, 0x13, 0x24, 0x7c, 0x1e, 0x83, 0xfe, 0x62, 0x28, 0x06, 0x1e, 0xc1, 0xfe, 0x64, 0x20, 0x06,
     0x7b, 0xe2, 0x0c, 0x3e, 0x87, 0xe2, 0xf0, 0x42, 0x90, 0xe0, 0x42, 0x15, 0x20, 0xd2, 0x05, 0x20,
     0x4f, 0x16, 0x20, 0x18, 0xcb, 0x4f, 0x06, 0x04, 0xc5, 0xcb, 0x11, 0x17, 0xc1, 0xcb, 0x11, 0x17,
     0x05, 0x20, 0xf5, 0x22, 0x23, 0x22, 0x23, 0xc9, 0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b,
     0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
     0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc,
     0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e, 0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c,
     0x21, 0x04, 0x01, 0x11, 0xa8, 0x00, 0x1a, 0x13, 0xbe, 0x20, 0xfe, 0x23, 0x7d, 0xfe, 0x34, 0x20,
     0xf5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xfb, 0x86, 0x20, 0xfe, 0x3e, 0x01, 0xe0, 0x50};

const uint8_t cycles[256] =
    { 4, 12,  8,  8,  4,  4,  8,  4, 20,  8,  8,  8,  4,  4,  8,  4,
      4, 12,  8,  8,  4,  4,  8,  4, 12,  8,  8,  8,  4,  4,  8,  4,
      8, 12,  8,  8,  4,  4,  8,  4,  8,  8,  8,  8,  4,  4,  8,  4,
      8, 12,  8,  8, 12, 12, 12,  4,  8,  8,  8,  8,  4,  4,  8,  4,
      4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
      4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
      4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
      8,  8,  8,  8,  8,  8,  4,  8,  4,  4,  4,  4,  4,  4,  8,  4,
      4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
      4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
      4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
      4,  4,  4,  4,  4,  4,  8,  4,  4,  4,  4,  4,  4,  4,  8,  4,
      8, 12, 12, 16, 12, 16,  8, 16,  8, 16, 12,  4, 12, 24,  8, 16,
      8, 12, 12,  0, 12, 16,  8, 16,  8, 16, 12,  0, 12,  0,  8, 16,
     12, 12,  8,  0,  0, 16,  8, 16, 16,  4, 16,  0,  0,  0,  8, 16,
     12, 12,  8,  4,  0, 16,  8, 16, 12,  8, 16,  4,  0,  0,  8, 16};
