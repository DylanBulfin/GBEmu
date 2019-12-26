#include <stdio.h>
#include <SDL2/SDL.h>
#include "internal.h"
#include "operations.h"
#include "../graphics/graphics.h"
#include "../input/input.h"

void misc_no_operation(register_file_t *state) {
  return;
}

void misc_enable_interrupts(register_file_t *state) {
  ei_pending = 1;
}

void misc_disable_interrupts(register_file_t *state) {
  di_pending = 1;
}

void misc_halt_operation(register_file_t *state) {
  //printf("HALT occurred at 0x%04x, IE = 0x%02x, IF = 0x%02x, IME = 0x%02x\n", PC, MEM(IE), MEM(IF), IME);
  if(!IME) {
    if(MEM(IE) & MEM(IF) & 0x1f) {
      //TODO maybe implement skipping
      return;
    }
    HALT(HALT_MODE_DISABLED);
    return;
  }
  HALT(HALT_MODE_ENABLED);
}

void misc_stop_operation(register_file_t *state) {
  //   printf("STOP SIGNAL RECEIVED\n");
  clear_screen();
  wait_for_valid_button_press(state);
}
