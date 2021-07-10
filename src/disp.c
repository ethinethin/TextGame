#include <stdio.h>
#include <SDL2/SDL.h>
#include "disp.h"
#include "font.h"
#include "main.h"

void
display_init(struct screen *cur_screen, int fullscreen, SDL_bool vsync)
{
	SDL_DisplayMode dm;

	/* Create the main window and renderer */
	if (fullscreen == 0) {
		SDL_GetDesktopDisplayMode(0, &dm);
		cur_screen->w = dm.w;
		cur_screen->h = dm.h;
		cur_screen->window = SDL_CreateWindow(cur_screen->name, 100, 100, cur_screen->w, cur_screen->h, SDL_WINDOW_FULLSCREEN_DESKTOP);
	} else if (fullscreen == 1) {
		cur_screen->window = SDL_CreateWindow(cur_screen->name, 100, 100, cur_screen->w, cur_screen->h, SDL_WINDOW_FULLSCREEN);
	} else {
		cur_screen->window = SDL_CreateWindow(cur_screen->name, 100, 100, cur_screen->w, cur_screen->h, SDL_WINDOW_RESIZABLE);
	}
	if (vsync == SDL_TRUE) {
		cur_screen->renderer = SDL_CreateRenderer(cur_screen->window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_TARGETTEXTURE);
	} else {
		cur_screen->renderer = SDL_CreateRenderer(cur_screen->window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
	}
	/* Load the font */
	load_font(cur_screen);
	/* Create output texture */
	cur_screen->output = SDL_CreateTexture(cur_screen->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	/* Up and running */
	cur_screen->running = SDL_TRUE;
}

void
display_kill(struct screen *cur_screen)
{
	unload_font(cur_screen);
	SDL_DestroyTexture(cur_screen->output);
	SDL_DestroyRenderer(cur_screen->renderer);
	cur_screen->renderer = NULL;
	SDL_DestroyWindow(cur_screen->window);
	cur_screen->window = NULL;
}

void
clear_disp(struct screen *cur_screen)
{
	/* Set the rendering target to the output texture and clear it */
	SDL_SetRenderTarget(cur_screen->renderer, cur_screen->output);
	SDL_SetRenderDrawColor(cur_screen->renderer, 26, 26, 26, 255);
	SDL_RenderClear(cur_screen->renderer);
}

void
present_disp(struct screen *cur_screen)
{
	SDL_Rect src = { 0, 0, 1280, 720 };
	SDL_Rect dest = { 0, 0, cur_screen->w, cur_screen->h };
	
	/* Reset render target to the renderer */
	SDL_SetRenderTarget(cur_screen->renderer, NULL);
	/* Clear the renderer */
	SDL_RenderClear(cur_screen->renderer);
	/* Copy the output texture to the renderer */
	SDL_RenderCopy(cur_screen->renderer, cur_screen->output, &src, &dest);
	/* Present */
	SDL_RenderPresent(cur_screen->renderer);
}

SDL_bool
change_resolution(struct screen *cur_screen, int w, int h)
{
	if (cur_screen->w != w || cur_screen->h != h) {
		cur_screen->w = w;
		cur_screen->h = h;
		return SDL_TRUE;	
	} else {
		return SDL_FALSE;
	}
}

SDL_bool
toggle_fullscreen(struct screen *cur_screen, int fullscreen)
{
	if (cur_screen->fullscreen != fullscreen) {
		cur_screen->fullscreen = fullscreen;
		return SDL_TRUE;
	} else {
		return SDL_FALSE;
	}
}
