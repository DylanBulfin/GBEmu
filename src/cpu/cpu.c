#include <SDL2/SDL.h>
#include <time.h>
#include "../timing/clock.h"
#include "../interrupts/interrupts.h"
#include "../input/input.h"
#include "internal.h"
#include "arrays.h"
#include "run.h"

int8_t is_halted = 0;
int8_t halt_mode = -1;
int8_t ei_pending = 0;
int8_t di_pending = 0;

struct timespec stop_wait = {0,1000000};

long long int instrs = 0;

void run_instruction(register_file_t *state) {
    //printf("STAT: 0x%02x, LYC: 0x%02x\n", MEM(STAT), MEM(LYC));
    
    if(check_interrupts(state)) {
	return;
    }

    if(ei_pending) {
	ei_pending = 0;
	IME = 1;
    }
    if(di_pending) {
	di_pending = 0;
	IME = 0;
    }

    instrs++;
    
    if(!is_halted) {
	uint8_t op = MEM(PC);
    
	if(op == 0xcb) {
	    uint8_t ext = MEM(PC + 1);
	    int hl = ((ext & 0x7) == 0x6);
	    uint8_t cycle_count = (hl ? (((ext >> 6) & 0x3) == 0x1 ? 12 : 16)  : 8);
	    INC_CLOCK(cycle_count,state);
	} else {
	    INC_CLOCK(cycles[op],state);
	}

	if(PC == 0x300) {
	    //printf("LDH Performed at instr 0x%I64d\n", instrs);
	}
	
	(*func_array[op])(state);
	PC += 1 + num_args[op];

	return;
    } else {
	INC_CLOCK(4,state);
    }
}
