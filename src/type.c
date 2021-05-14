#include <ctype.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "main.h"
#include "room.h"
#include "type.h"

short int
handle_typing(SDL_Event event, char *buffer, short int cur_letter)
{
	if (event.key.keysym.sym - 32 >= 0 && event.key.keysym.sym - 32 < 95) {
		if (cur_letter > 68) return cur_letter;
		buffer[cur_letter] = toupper(event.key.keysym.sym);
		buffer[cur_letter + 1] = '|';
		buffer[cur_letter + 2] = '\0';
		cur_letter += 1;
	} else if (event.key.keysym.sym == '\b') {
		if (cur_letter > 0) {
			buffer[cur_letter - 1] = '|';
			buffer[cur_letter] = '\0';
			cur_letter -= 1;
		}
	} else if (event.key.keysym.sym == SDLK_RETURN) {
		return -1;
	}
	return cur_letter;
}

int
handle_input(struct screen *cur_screen, char *buffer)
{
	int len;
	int room;
	
	len = strlen(buffer);
	if (len == 0) return NOMOVE;
	
	/* Check if commands were entered */
	if (strncmp(buffer, "NORTH", len) == 0) {
		room = get_exit(cur_screen->room, NORTH);
	} else if (strncmp(buffer, "EAST", len) == 0) {
		room = get_exit(cur_screen->room, EAST);
	} else if (strncmp(buffer, "SOUTH", len) == 0) {
		room = get_exit(cur_screen->room, SOUTH);
	} else if (strncmp(buffer, "WEST", len) == 0) {
		room = get_exit(cur_screen->room, WEST);
	} else if (strncmp(buffer, "QUIT", 5) == 0 ||
		   strncmp(buffer, "EXIT", 5) == 0) {
		   	return QUIT;
	} else {
		room = -1;
	}
	
	/* Change room if necessary */
	if (room != -1) {
		cur_screen->room = room;
		return MOVE;
	} else {
		return NOMOVE;
	}
}
