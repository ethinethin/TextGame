#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "disp.h"
#include "font.h"
#include "main.h"
#include "room.h"
#include "type.h"

/* Function prototypes */
static void	start_SDL(void);
static void	stop_SDL(void);

int
main()
{
	char exits[32];
	char buffer[70];
	short int cur_letter;
	int len;
	int results;
	int y_val;
	SDL_Event event;

	/* Create initial display */
	struct screen cur_screen = {
		1280,		/* width */
		720,		/* height */
		"TextGame",	/* name */
		NULL,		/* window */
		NULL,		/* renderer */
		NULL,		/* output */
		SDL_FALSE,	/* vsync */
		2,		/* fullscreen */
		SDL_FALSE,	/* running */
		NULL,		/* font */
		0		/* room */
	};
	/* Stat SDL and initialize display */
	start_SDL();
	display_init(&cur_screen, cur_screen.fullscreen, cur_screen.vsync);
	
	/* Enter main loop and output some text to the screen */
	cur_letter = 0; buffer[0] = '|'; buffer[1] = '\0';
	while(cur_screen.running == SDL_TRUE) {
		clear_disp(&cur_screen);
		y_val = output(&cur_screen, 10, 10, room_name(cur_screen.room), 2.0);
		y_val = output(&cur_screen, 10, y_val, "\n", 1.0);
		y_val = output(&cur_screen, 10, y_val, room_desc(cur_screen.room), 1.0);
		y_val = output(&cur_screen, 10, y_val, "\n", 1.0);
		room_exits(cur_screen.room, exits);
		output(&cur_screen, 10, y_val, exits, 1.0);
		output(&cur_screen, 10, 692, "COMMAND> ", 1.0);
		output(&cur_screen, 10 + 144, 692, buffer, 1.0);
		present_disp(&cur_screen);
		SDL_Delay(10);
		if (SDL_PollEvent(&event) == 0) continue;
		if (event.type == SDL_QUIT) {		/* exit button pressed */
			cur_screen.running = SDL_FALSE;
		} else if (event.type == SDL_KEYDOWN) {
			cur_letter = handle_typing(event, buffer, cur_letter);
			if (cur_letter == -1) {
				/* Do something */
				len = strlen(buffer);
				if (len > 0) {
					buffer[len - 1] = '\0';
				}
				results = handle_input(&cur_screen, buffer);
				/* Reset buffer */
				cur_letter = 0; buffer[0] = '|'; buffer[1] = '\0';
				if (results == QUIT) {
					cur_screen.running = SDL_FALSE;
				} else if (results == RESOLUTION) {
					display_kill(&cur_screen);
					display_init(&cur_screen, cur_screen.fullscreen, cur_screen.vsync);
				}
			}
		} else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			change_resolution(&cur_screen, event.window.data1, event.window.data2);
		}
	}
	
	/* Destroy display and exit */
	display_kill(&cur_screen);
	stop_SDL();
	return 0;
}

static void
start_SDL(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL error: %s\n", SDL_GetError());
		exit(1);
	}
}

static void
stop_SDL(void)
{
	SDL_Quit();
}
