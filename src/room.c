#include <SDL2/SDL.h>
#include "main.h"

struct room {
	int id;
	char *name;
	char *desc;
	int exits[4];
} ROOMS[] = {
	{ 0, "First room", "This is the first room", {1, 7, -1, -1} },
	{ 1, "Second room", "This is the second room", {2, -1, 0, -1} },
	{ 2, "Third room", "This is the third room", {3, -1, 1, -1} },
	{ 3, "Fourth room", "This is the fourth room", {-1, 4, 2, 5} },
	{ 4, "Fifth room", "This is the fifth room", {-1, -1, -1, 3} },
	{ 5, "Sixth room", "This is the sixth room", {6, 3, -1, -1} },
	{ 6, "Seventh room", "This is the seventh room", {-1, -1, 5, -1} },
	{ 7, "Eighth room", "This is the eighth room", {-1, -1, -1, 0} }, 
	{ -1, "THIS IS NOT A ROOM", "THIS ROOM DOES NOT EXIST", {-1, -1, -1, -1} }
};

/* Function prototype */
static short int	which_room(int id);

char *
room_name(int id)
{
	id = which_room(id);
	if (id != -1) {
		return ROOMS[id].name;
	} else {
		return "????";
	}
}

char *
room_desc(int id)
{
	id = which_room(id);
	if (id != -1) {
		return ROOMS[id].desc;
	} else {
		return "????";
	}
}

static short int
which_room(int id)
{
	int i;
	for (i = 0; ROOMS[i].id != -1; i++) {
		if (ROOMS[i].id == id) {
			return i;
		}
	}
	return -1;
}

int
get_exit(int id, int dir)
{
	id = which_room(id);
	if (id != -1) {
		return ROOMS[id].exits[dir];
	} else {
		return -1;
	}
}
