#include <string.h>
#include <SDL2/SDL.h>
#include "disp.h"
#include "font.h"
#include "main.h"

#define font_w 16
#define font_h 18

/* Function prototype */
static void	draw_char(struct screen *cur_screen, int x, int y, int letter, float scale);

void
load_font(struct screen *cur_screen)
{
	int i, j;
	SDL_Surface *image;
	SDL_Surface *tmp;
	SDL_Rect rect = {0, 0, font_w, font_h};

	/* Allocate memory for 95 font characters */
	cur_screen->font = malloc(sizeof(*cur_screen->font)*95);
	/* Load sprite sheet */
	image = SDL_LoadBMP("art/font.bmp");
	/* Load all sprites */
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (i * 10 + j == 95) break;
			rect.x = j * font_w;
			rect.y = i * font_h;
			tmp = SDL_CreateRGBSurface(0, font_w, font_h, 24, 0, 0, 0, 0);
			SDL_SetColorKey(tmp, 1, 0xFF00FF);
			SDL_BlitSurface(image, &rect, tmp, NULL);
			cur_screen->font[i * 10 + j] = SDL_CreateTextureFromSurface(cur_screen->renderer, tmp);
			SDL_FreeSurface(tmp);
		}
	}
	SDL_FreeSurface(image);
}

void
unload_font(struct screen *cur_screen)
{
	int i;

	/* Free all font characters */
	for (i = 0; i < 95; i++) {
		SDL_DestroyTexture(cur_screen->font[i]);
	}
	free(cur_screen->font);
}

void
output(struct screen *cur_screen, int x, int y, char *sentence, float scale)
{
	int i;
	int cur_x, cur_y;
	int len;

	for (i = 0, len = strlen(sentence), cur_x = x, cur_y = y; i < len; i++) {
		if (sentence[i] != '\n') {
			if (sentence[i] - 32 >= 0 && sentence[i] - 32 < 95) {
				draw_char(cur_screen, cur_x, cur_y, sentence[i] - 32, scale);
			} else {
				draw_char(cur_screen, cur_x, cur_y, '?' - 32, scale);
			}
			cur_x += font_w * scale * cur_screen->scale;
		}
		if (cur_x >= cur_screen->w - font_w || sentence[i] == '\n') {
			cur_x = x;
			cur_y += font_h * scale * cur_screen->scale;
		}
	}
}

static void
draw_char(struct screen *cur_screen, int x, int y, int letter, float scale)
{
	SDL_Rect rect = {x, y, font_w * scale * cur_screen->scale, font_h * scale * cur_screen->scale};
	SDL_RenderCopyEx(cur_screen->renderer, cur_screen->font[letter], NULL, &rect, 0, NULL, 0);
}
