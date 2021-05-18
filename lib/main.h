#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>

struct screen {
	int w;
	int h;
	const char *name;
	float scale_x;
	float scale_y;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_bool vsync;
	SDL_bool fullscreen;
	SDL_bool running;
	SDL_Texture **font;
	int room;
};

#endif
