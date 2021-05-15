#ifndef DISP_H
#define DISP_H

#include "main.h"

extern void		display_init(struct screen *cur_screen, SDL_bool vsync);
extern void		display_kill(struct screen *cur_screen);
extern void		clear_disp(struct screen *cur_screen);
extern void		present_disp(struct screen *cur_screen);
extern SDL_bool		change_resolution(struct screen *cur_screen, int w, int h);

#endif
