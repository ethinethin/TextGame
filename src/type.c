#include <ctype.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "disp.h"
#include "main.h"
#include "room.h"
#include "type.h"

short int
handle_typing(SDL_Event event, char *buffer, short int cur_letter)
{
	if (event.key.keysym.sym - 32 >= 0 && event.key.keysym.sym - 32 < 95) {
		if (cur_letter > 67) return cur_letter;
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
	char allwords[100];
	char *words[8];
	int i;
	int len;
	int room = -1;
	
	len = strlen(buffer);
	if (len == 0) return NOMOVE;
	
	/* Copy the line to a new variable that we can tokenize */
	strncpy(allwords, buffer, len);
	/* Split the line into words */
	*words = strtok(allwords, " \n");
	if (*words == NULL) return NOMOVE;
	for (i = 1; i < 8; i++) {
		*(words + i) = strtok(NULL, " \n");
	}
	
	/* Parse input */
	if (strncmp(*words, "QUIT", 4) == 0 || strncmp(*words, "EXIT", 4) == 0) {
	    	return QUIT;
	} else if (strncmp(*words, "HELP", 4) == 0) {
		return HELP;
	} else if (strncmp(*words, "LOOK", 4) == 0 && *(words + 1) == NULL) {
		return LOOKROOM;
	} else if (strncmp(*words, "NORTH", len) == 0) {
		room = get_exit(cur_screen->room, NORTH);
	} else if (strncmp(*words, "EAST", len) == 0) {
		room = get_exit(cur_screen->room, EAST);
	} else if (strncmp(*words, "SOUTH", len) == 0) {
		room = get_exit(cur_screen->room, SOUTH);
	} else if (strncmp(*words, "WEST", len) == 0) {
		room = get_exit(cur_screen->room, WEST);
	} else if (strncmp(*words, "RES1", 4) == 0) {
		if (change_resolution(cur_screen, 1024, 576) == SDL_TRUE) return RESOLUTION;
	} else if (strncmp(*words, "RES2", 4) == 0) {
		if (change_resolution(cur_screen, 1280, 720) == SDL_TRUE) return RESOLUTION;
	} else if (strncmp(*words, "RES3", 4) == 0) {
		if (change_resolution(cur_screen, 1600, 900) == SDL_TRUE) return RESOLUTION;
	} else if (strncmp(*words, "RES4", 4) == 0) {
		if (change_resolution(cur_screen, 800, 600) == SDL_TRUE) return RESOLUTION;
	} else if (strncmp(*words, "RES5", 4) == 0) {
		if (change_resolution(cur_screen, 640, 480) == SDL_TRUE) return RESOLUTION;
	} else if (strncmp(*words, "DISP1", 5) == 0) {
		if (toggle_fullscreen(cur_screen, 0) == SDL_TRUE) return RESOLUTION;
	} else if (strncmp(*words, "DISP2", 5) == 0) {
		if (toggle_fullscreen(cur_screen, 1) == SDL_TRUE) return RESOLUTION;
	} else if (strncmp(*words, "DISP3", 5) == 0) {
		if (toggle_fullscreen(cur_screen, 2) == SDL_TRUE) return RESOLUTION;
	}
	
	/* Change room if necessary */
	if (room != -1) {
		cur_screen->room = room;
		return MOVE;
	} else {
		return NOMOVE;
	}
}
