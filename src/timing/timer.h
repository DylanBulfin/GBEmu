#include "../cpu/internal.h"

extern uint32_t last_increment;
extern int8_t timer_overflow_pending;

void update_timer(uint32_t,register_file_t*);
void update_divider(uint32_t, register_file_t*);

#define TIMER_ENABLED ((MEM(TAC)>>2)&0x1)
#define TIMER_SPEED   (MEM(TAC)&0x3)

#define TIMER_INTERRUPT_DELAY 4

#define DIVIDER_LENGTH 256

#define S1_CODE   0x0
#define S2_CODE   0x1
#define S3_CODE   0x2
#define S4_CODE   0x3

#define S1_CYCLES 1024
#define S2_CYCLES 16
#define S3_CYCLES 64
#define S4_CYCLES 256
