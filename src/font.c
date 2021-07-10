#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "disp.h"
#include "font.h"
#include "main.h"

#define font_w 16
#define font_h 18

/* Function prototype */
static void	draw_char(struct screen *cur_screen, int x, int y, int letter, float scale);
static void	format_text(char *text, char formatted[1024], int n);

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

int
output(struct screen *cur_screen, int x, int y, char *sentence, float scale)
{
	char formatted[1024];
	int i;
	int cur_x, cur_y;
	int len;

	/* Format the text*/
	format_text(sentence, formatted, 78/scale);
	
	/* Output the text */ 
	for (i = 0, len = strlen(formatted), cur_x = x, cur_y = y; i < len; i++) {
		if (formatted[i] != '\n') {
			if (formatted[i] - 32 >= 0 && formatted[i] - 32 < 95) {
				draw_char(cur_screen, cur_x, cur_y, toupper(formatted[i]) - 32, scale);
			} else {
				draw_char(cur_screen, cur_x, cur_y, '?' - 32, scale);
			}
			cur_x += font_w * scale;
		}
		if (formatted[i] == '\n') {
			cur_x = x;
			cur_y += font_h * scale;
		}
	}
	cur_y += font_h * scale;
	return cur_y;
}

static void
draw_char(struct screen *cur_screen, int x, int y, int letter, float scale)
{
	SDL_Rect rect = {x, y, font_w * scale, font_h * scale};
	SDL_RenderCopyEx(cur_screen->renderer, cur_screen->font[letter], NULL, &rect, 0, NULL, 0);
}

static void
format_text(char *text, char formatted[1024], int n)
{
	int form_i;
	int len;
	int text_i;
	int x_pos;
	
	len = strlen(text);
	/* If the string fits in a single line, just copy it */
	
	/* Reformat text to fit window */
	for (text_i = 0, form_i = 0, x_pos = 0; text_i < len; text_i++, form_i++, x_pos++) {
		/* Check if at end of line */
		if (x_pos > n) {
			/* If you're on a space, replace a new line */
			if (text[text_i] == ' ') {
				formatted[form_i] = '\n';
			} else {
				/* Go backwords looking for a space */
				while (text[text_i] != ' ') {
					text_i--; form_i--;
				}
				formatted[form_i] = '\n';
			}
			x_pos = 0;
		} else {
			formatted[form_i] = text[text_i];
		}
	}
	formatted[form_i] = '\0';
}
