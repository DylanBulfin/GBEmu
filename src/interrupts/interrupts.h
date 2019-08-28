#pragma once

#include "../cpu/internal.h"

#define V_BLANK        ((uint8_t)0x01)
#define LCDC_STATUS    ((uint8_t)0x02)
#define TIMER_OVERFLOW ((uint8_t)0x04)
#define SERIAL_IO_DONE ((uint8_t)0x08)
#define JOYPAD         ((uint8_t)0x10)

int check_interrupts(register_file_t*);
void request_interrupt(uint8_t,register_file_t*);
