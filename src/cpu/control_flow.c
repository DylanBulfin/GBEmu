#include <stdio.h>
#include "internal.h"
#include "operations.h"
#include "../timing/clock.h"
#include "../cartridge/cartridge.h"

//Jumps to immediate address
void control_flow_jump_immediate_unconditional(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);
    PC = VAL_NN(ARG2,ARG1);
}

void control_flow_jump_immediate_conditional(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);

    if(COND(*code)) {
	PC = VAL_NN(ARG2,ARG1);
	INC_CLOCK(4,state);
    } else {
	PC += 3;
    }
}


//Jumps to relative offset
void control_flow_jump_relative_unconditional(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);

    PC += 2;
    PC += SE(ARG1);
}

void control_flow_jump_relative_conditional(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);

    PC += 2;

    if(COND(*code)) {
	PC += SE(ARG1);
	INC_CLOCK(4,state);
    }
}


//Jump to HL reference
void control_flow_jump_hl_reference(register_file_t *state) {
    PC = VAL_HL;
}


//Method calls
void control_flow_call_method_unconditional(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);

    PC += 3;
    
    WRITE_MEM(SP-1,HI_BYTE(PC));
    WRITE_MEM(SP-2,LO_BYTE(PC));

    SP -= 2;

    PC = VAL_NN(ARG2,ARG1);
}

void control_flow_call_method_conditional(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);

    PC += 3;

    if(COND(*code)) {
	WRITE_MEM(SP-1,HI_BYTE(PC));
	WRITE_MEM(SP-2,LO_BYTE(PC));

	SP -= 2;

	PC = VAL_NN(ARG2,ARG1);

	INC_CLOCK(12,state);
    }
}


//Returns
void control_flow_return_unconditional(register_file_t *state) {
    PC = VAL_NN((*READ_MEM(SP+1)),(*READ_MEM(SP)));

    SP += 2;
}

void control_flow_return_conditional(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);

    if(COND(*code)) {
	PC = VAL_NN((*READ_MEM(SP+1)),(*READ_MEM(SP)));
	SP += 2;
	
	INC_CLOCK(12,state);
    } else {
	PC += 1;
    }
}

void control_flow_return_enable_interrupts(register_file_t *state) {
    PC = VAL_NN((*READ_MEM(SP+1)),(*READ_MEM(SP)));

    SP += 2;

    IME = 1;
}


//Restart
void control_flow_restart_routine(register_file_t *state) {
    uint8_t *code = READ_MEM(PC);
    uint8_t addr = (*code & 0x38);

    PC += 1;

    WRITE_MEM(SP-1,HI_BYTE(PC));
    WRITE_MEM(SP-2,LO_BYTE(PC));

    SP -= 2;

    PC = 0 | addr;
}
