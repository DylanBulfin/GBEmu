#include <stdlib.h>
#include <SDL2/SDL.h>
#include "cpu/internal.h"
#include "cpu/arrays.h"
#include "timing/clock.h"
#include "interrupts/interrupts.h"
#include "graphics/graphics.h"
#include "cpu/run.h"
#include "cartridge/cartridge.h"
#include "sound/sound.h"

int8_t quit = 0;
int step = 0;

void cleanup(register_file_t *state) {
    shutdown_audio();
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
    test_method();

    condition_codes_t cc = {0,0,0,0,0};
    register_file_t rf = {0,0,0,0,0,0,0,0,0,NULL,cc,0};

    register_file_t *state = &rf;
    
    run_startup(game,state);

    int abort = 0;


    //    FILE *f = fopen("states.txt", "a");
    
    while(!abort && !quit) {
	//uint8_t op = MEM(PC);
	if(step) {
	    STATE;
	    getchar();
	}
	//STATE;

	if(PC == 0x300) {
	    //printf("%I64d\n", instruction_count);
	}
	/*			
	if(PC == 0x21b) {
	    printf("0x21b arrived\n");
	    getchar();
	}
	*/
	//	write_state_to_file(f, state);
	
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
