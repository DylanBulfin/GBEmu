#include <SDL2/SDL.h>
#include <stdio.h>
#include "../cpu/internal.h"
#include "../input/input.h"
#include "../interrupts/interrupts.h"
#include "clock.h"
#include "timer.h"

const uint32_t CLOCK_MAX_VALUE = 4194304;

uint32_t clock = 0;

int times = 0;

uint32_t seconds = 0;

void start_timer() {
    last_increment = clock;
}

void check_transition(uint32_t old_clock, uint32_t new_clock, register_file_t *state) {
    if(timer_overflow_pending && (new_clock >= (last_increment + TIMER_INTERRUPT_DELAY))) {
	MEM(TIMA) = MEM(TMA);
	request_interrupt(TIMER_OVERFLOW, state);
	timer_overflow_pending = 0;
    }
	
    check_scanline(new_clock, state);
    update_timer(new_clock, state);
    update_divider(new_clock, state);
}

//Main clock increment method
void increment_clock(uint8_t val, register_file_t *state) {
    uint32_t new_clock = clock + val;

    TRANS(clock, new_clock, state);
    
    if(new_clock >= CLOCK_MAX_VALUE) {
	new_clock -= CLOCK_MAX_VALUE;
	seconds++;
	//        printf("%d second have passed\n", seconds);
    }
    clock = new_clock;
}
