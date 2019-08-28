#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdlib.h>
#include "settings.h"

#define LINE_SEP "\n"
#define OPTION_SEP "="

//Defaults
uint8_t real_time = 1;

uint16_t window_width = 800;
uint16_t window_height = 720;

char *game_directory = "roms/";
char *save_directory = "saves/";
int8_t load_save_file = 1;

SDL_Keycode a_key = SDLK_x;
SDL_Keycode b_key = SDLK_z;
SDL_Keycode start_key = SDLK_RETURN;
SDL_Keycode select_key = SDLK_SPACE;
SDL_Keycode up_key = SDLK_UP;
SDL_Keycode down_key = SDLK_DOWN;
SDL_Keycode left_key = SDLK_LEFT;
SDL_Keycode right_key = SDLK_RIGHT;

SDL_GameControllerButton jp_a = 0;
SDL_GameControllerButton jp_b = 0;
SDL_GameControllerButton jp_start = 0;
SDL_GameControllerButton jp_select = 0;
SDL_GameControllerButton jp_up = 0;
SDL_GameControllerButton jp_down = 0;
SDL_GameControllerButton jp_left = 0;
SDL_GameControllerButton jp_right = 0;

int8_t color_mode = 0;

/*
#ifdef __linux__

void parse_line(char *new_value) {
    char *option = strsep(&new_value, OPTION_SEP);
    
#elif _WIN32*/

void parse_line(char *line) {
    const char *delim = OPTION_SEP;
    char *new_value;
    char *option = strtok_r(line, delim, &new_value);
    
    //#endif

    if(!strcmp(option, "FAST_FORWARD")) {
	if(!strcmp(new_value, "true")) {
	    real_time = 0;
	    printf("Updated fast forward to true\n");
	} else if(!strcmp(new_value, "false")) {
	    real_time = 1;
	    printf("Updated fast forward to false\n");
	} else {
	    printf("Invalid fast forward setting, using default value of false instead!\n");
	}
    }
    
    else if(!strcmp(option, "WINDOW_HEIGHT")) {
	int new_window_height = atoi(new_value);
	if(!new_window_height) {
	    printf("Invalid window height option, using default value of %d instead!\n", window_height);
	} else {
	    window_height = new_window_height;
	    printf("Updated window height to %d pixels\n", window_height);
	}
    }

    else if(!strcmp(option, "WINDOW_WIDTH")) {
	int new_window_width = atoi(new_value);
	if(!new_window_width) {
	    printf("Invalid window width option, using default value of %d instead!\n", window_width);
	} else {
	    window_width = new_window_width;
	    printf("Updated window width to %d pixels\n", window_width);
	}
    }

    else if(!strcmp(option, "GAME_DIRECTORY")) {
	game_directory = new_value;
	printf("Updated game directory to %s\n", game_directory);
    }

    else if(!strcmp(option, "SAVE_DIRECTORY")) {
	save_directory = new_value;
	printf("Updated save directory to %s\n", save_directory);
    }

    else if(!strcmp(option, "LOAD_SAVE")) {
	if(!strcmp(new_value, "true")) {
	    load_save_file = 1;
	    printf("Updated save file loading to true\n");
	} else if(!strcmp(new_value, "false")) {
	    load_save_file = 0;
	    printf("Updated save file loading to false\n");
	} else {
	    printf("Invalid save file loading option, using default value of true instead!\n");
	}
    }

    else if(!strcmp(option, "A_KEY")) {
	SDL_Keycode new_a_key = SDL_GetKeyFromName(new_value);

	if(new_a_key == SDLK_UNKNOWN) {
	    printf("Invalid a key option, using default value of X instead!\n");
	} else {
	    a_key = new_a_key;
	    printf("Updated a key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "B_KEY")) {
	SDL_Keycode new_b_key = SDL_GetKeyFromName(new_value);

	if(new_b_key == SDLK_UNKNOWN) {
	    printf("Invalid b key option, using default value of Z instead!\n");
	} else {
	    b_key = new_b_key;
	    printf("Updated b key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "START_KEY")) {
	SDL_Keycode new_start_key = SDL_GetKeyFromName(new_value);

	if(new_start_key == SDLK_UNKNOWN) {
	    printf("Invalid start key option, using default value of Return instead!\n");
	} else {
	    start_key = new_start_key;
	    printf("Updated start key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "SELECT_KEY")) {
	SDL_Keycode new_select_key = SDL_GetKeyFromName(new_value);

	if(new_select_key == SDLK_UNKNOWN) {
	    printf("Invalid select key option, using default value of Space instead!\n");
	} else {
	    select_key = new_select_key;
	    printf("Updated select key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "UP_KEY")) {
	SDL_Keycode new_up_key = SDL_GetKeyFromName(new_value);

	if(new_up_key == SDLK_UNKNOWN) {
	    printf("Invalid up key option, using default value of Up instead!\n");
	} else {
	    up_key = new_up_key;
	    printf("Updated up key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "DOWN_KEY")) {
	SDL_Keycode new_down_key = SDL_GetKeyFromName(new_value);

	if(new_down_key == SDLK_UNKNOWN) {
	    printf("Invalid down key option, using default value of Down instead!\n");
	} else {
	    down_key = new_down_key;
	    printf("Updated down key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "LEFT_KEY")) {
	SDL_Keycode new_left_key = SDL_GetKeyFromName(new_value);

	if(new_left_key == SDLK_UNKNOWN) {
	    printf("Invalid left key option, using default value of Left instead!\n");
	} else {
	    left_key = new_left_key;
	    printf("Updated left key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "RIGHT_KEY")) {
	SDL_Keycode new_right_key = SDL_GetKeyFromName(new_value);

	if(new_right_key == SDLK_UNKNOWN) {
	    printf("Invalid right key option, using default value of Right instead!\n");
	} else {
	    right_key = new_right_key;
	    printf("Updated right key to %s\n", new_value);
	}
    }

    else if(!strcmp(option, "COLOR_MODE")) {
	if(!strcmp(new_value, "green")) {
	    color_mode = 0;
	    printf("Updated color mode to green\n");
	} else if(!strcmp(new_value, "grey") || !strcmp(new_value, "gray")) {
	    color_mode = 1;
	    printf("Updated color mode to grey\n");
	} else {
	    printf("Invalid color mode option, using default value of green instead!\n");
	}
    }
}

void load_settings() {
    printf("\n\nReading settings file...\n\n");
    FILE *f = fopen("settings.txt", "r");

    fseek(f, 0, SEEK_END);
    long f_size = ftell(f);

    fseek(f, 0, SEEK_SET);

    char *settings_file = malloc(f_size + 1);

    fread(settings_file, f_size, 1, f);
    /*
#ifdef __linux__
    
    char *line = strsep(&settings_file, LINE_SEP);

    while(line != NULL) {
	if(line[0] != '#') {
	    parse_line(line);
	}

	line = strsep(&settings_file, LINE_SEP);
    }
    
#elif _WIN32
    */
    const char *delim = LINE_SEP;
    char *next_line;
    char *line = strtok_r(settings_file, delim, &next_line);

    while(line != NULL) {
	if(line[0] != '#') {
	    parse_line(line);
	}
	
	line = strtok_r(NULL, delim, &next_line);
    }
    
    //#endif
    
}
