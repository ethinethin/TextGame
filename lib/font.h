#ifndef FONT_H
#define FONT_H

#include "main.h"

extern void	load_font(struct screen *cur_screen);
extern void	unload_font(struct screen *cur_screen);
extern void	output(struct screen *cur_screen, int x, int y, char *sentence, float scale);

#endif
