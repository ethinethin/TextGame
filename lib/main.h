#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>

struct screen {
	int w;
	int h;
	const char *name;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *output;
	SDL_bool vsync;
	int fullscreen;
	SDL_bool running;
	SDL_Texture **font;
	int room;
};

#endif
