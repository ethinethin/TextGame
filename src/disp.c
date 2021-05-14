#include <stdio.h>
#include <SDL2/SDL.h>
#include "disp.h"
#include "font.h"
#include "main.h"

void
display_init(struct screen *cur_screen, SDL_bool vsync)
{
	/* Create the main window and renderer */
	cur_screen->window = SDL_CreateWindow(cur_screen->name, 100, 100, cur_screen->w, cur_screen->h, 0);
	if (vsync == SDL_TRUE) {
		cur_screen->renderer = SDL_CreateRenderer(cur_screen->window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
	} else {
		cur_screen->renderer = SDL_CreateRenderer(cur_screen->window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
	}
	/* Load the font */
	load_font(cur_screen);					      
	/* Up and running */
	cur_screen->running = SDL_TRUE;
}

void
display_kill(struct screen *cur_screen)
{
	unload_font(cur_screen);
	SDL_DestroyRenderer(cur_screen->renderer);
	cur_screen->renderer = NULL;
	SDL_DestroyWindow(cur_screen->window);
	cur_screen->window = NULL;
}

void
clear_disp(struct screen *cur_screen)
{
	SDL_SetRenderDrawColor(cur_screen->renderer, 26, 26, 26, 255);
	SDL_RenderClear(cur_screen->renderer);
}

void
present_disp(struct screen *cur_screen)
{
	SDL_RenderPresent(cur_screen->renderer);
}
