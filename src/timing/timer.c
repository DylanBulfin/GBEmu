#include <stdio.h>
#include "timer.h"
#include "clock.h"
#include "../interrupts/interrupts.h"

uint32_t last_increment = -1;
int8_t timer_overflow_pending = 0;

uint32_t last_divider = -1;

uint32_t get_num_cycles(register_file_t *state) {
    switch(TIMER_SPEED) {
    case S1_CODE:
	return S1_CYCLES;
	break;
    case S2_CODE:
	return S2_CYCLES;
	break;
    case S3_CODE:
	return S3_CYCLES;
	break;
    case S4_CODE:
	return S4_CYCLES;
	break;
    }
    return -1;
}
	    
void update_timer(uint32_t new_clock, register_file_t *state) {
    uint32_t cycles = get_num_cycles(state);

    if(TIMER_ENABLED) {
	//	printf("last inc: %d, new_clock: %d, cycles: %d\n,", last_increment, new_clock, cycles);
	while(new_clock >= ((last_increment + cycles) % CLOCK_MAX_VALUE) && ((new_clock < (CLOCK_MAX_VALUE / 2)) || (new_clock - (CLOCK_MAX_VALUE / 2) < ((last_increment + cycles) % CLOCK_MAX_VALUE)))) {
	    last_increment += cycles;
	    MEM(TIMA)++;
	    //printf(" TIMA:0x%02x\n", MEM(TIMA));
	    if(MEM(TIMA) == 0) {
		if(new_clock >= last_increment + TIMER_INTERRUPT_DELAY) {
		    MEM(TIMA) = MEM(TMA);
		    request_interrupt(TIMER_OVERFLOW, state);
		    timer_overflow_pending = 0;
		} else {
		    timer_overflow_pending = 1;
		}
	    }
	}
    }
}

void update_divider(uint32_t new_clock, register_file_t *state) {
    if(new_clock >= ((last_divider + DIVIDER_LENGTH) % CLOCK_MAX_VALUE) && ((new_clock < DIVIDER_LENGTH) || (new_clock - DIVIDER_LENGTH < ((last_divider + DIVIDER_LENGTH) % CLOCK_MAX_VALUE)))) {
        MEM(DIV)++;
	last_divider += DIVIDER_LENGTH;
    }
}
