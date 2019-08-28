#pragma once

#include "../cpu/internal.h"

extern const uint32_t CLOCK_MAX_VALUE;
extern uint32_t seconds;
extern uint32_t frames;

void increment_clock(uint8_t, register_file_t*);
void check_scanline(uint32_t, register_file_t*);

void start_timer();

#define INC_CLOCK(num,state) increment_clock(num,state)
#define TRANS(num1,num2,state) check_transition(num1,num2,state)
