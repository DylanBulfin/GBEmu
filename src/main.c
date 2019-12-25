#include <stdlib.h>
#include <SDL2/SDL.h>
#include "cpu/internal.h"
#include "cpu/arrays.h"
#include "timing/clock.h"
#include "interrupts/interrupts.h"
#include "graphics/graphics.h"
#include "cpu/run.h"
#include "cartridge/cartridge.h"

int8_t quit = 0;
int step = 0;

void cleanup(register_file_t *state) {
  write_ram_to_file();
    
  free(state->memory);
  free(cartridge);
  free(cartridge_ram);

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

long long int instruction_count = 0;    

int run(char *game) {
  condition_codes_t cc = {0,0,0,0,0};
  register_file_t rf = {0,0,0,0,0,0,0,0,0,NULL,cc,0};

  register_file_t *state = &rf;
    
  run_startup(game,state);

  int abort = 0;

  while(!abort && !quit) {
    if(step) {
      STATE;
      getchar();
    }
	
    run_instruction(state);
    instruction_count++;
  }

  cleanup(state);
    
  return 0;
}

int main(int argc, char *argv[]) {
  atexit(SDL_Quit);

  run(argv[1]);
    
  return 0;
}
