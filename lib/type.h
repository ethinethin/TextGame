#ifndef TYPE_H
#define TYPE_H

#define NOMOVE 0
#define MOVE 1
#define QUIT 2
#define RESOLUTION 3
#define HELP 4
#define LOOKROOM 5

extern short int	handle_typing(SDL_Event event, char *buffer, short int cur_letter);
extern int		handle_input(struct screen *cur_screen, char *buffer);

#endif
