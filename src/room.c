#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"

struct room {
	int id;
	char *name;
	char *desc;
	int exits[4];
} ROOMS[] = {
	{ 0, "Village Entrance", "You stand at the entrance to a quiet village. To the north, you see a row of houses. To the east is a large field next to a forest.", {1, 7, -1, -1} },
	{ 1, "Edge of the Village", "You are near a row of small houses on the edge of a quiet village. More houses are to the north, while the village entrance is to the south.", {2, -1, 0, -1} },
	{ 2, "Quiet Neighborhood", "You are in a quiet, residential neighborhood. You see people lurking behind pulled curtains out of the corner of your eye - you're being watched. There is a row of trash bins near the street. The village stretches both north and south.", {3, -1, 1, -1} },
	{ 3, "Shopping District", "You are outside of a row of shops. You can hear the banging of a hammer on an anvil from an blacksmith's shop to the east. Next to the shop is a pile of old metal junk. To the west is an inn called The Sleepy Woodsman.", {-1, 6, 2, 4} },
	{ 4, "The Sleepy Woodsman", "The cozy inn has a welcome desk near the door. A staircase leads north to the rooms upstairs. The exit is to the east.", {5, 3, -1, -1} },
	{ 5, "Upstairs at the Inn", "You are in a hallway on the second floor of the inn. There are four rooms here. All the doors are currently closed. There are tables standing next to the doors with assorted object and letters. A staircase leads downstairs to the south.", {-1, -1, 4, -1} },
	{ 6, "The Blacksmith's Shop", "You enter the blacksmith's shop. There are intricate works of shaped metal all around the room - high quality weapons, armor, and tools. It looks expensive!", {-1, -1, -1, 3} },
	{ 7, "The Field Near the Village", "You are in a field. There is an entrance to a village to the west. To the east is a path through a tall grass field that leads to a forest.", {-1, 8, -1, 0} }, 
	{ 8, "Tall Grass Field", "You walking on a path surrounded by dense, tall grass. There might be snakes lurking in the grass. A village can be seen in the distance to the west. A forest can be seen in the distance to the east.", {-1, 9, -1, 7} }, 
	{ 9, "Field Near the Cave and Forest", "You are standing in a field. A path to the south leads into a dark cave. A path to the east leads to the outskirts of a forest.", {-1, 15, 10, 8} }, 
	{ 10, "Cave Entrance", "You are standing inside a dark cave. Bright light can be seen through the entrance to the north. The cave stretches into darkness south.", {9, -1, 11, -1} }, 
	{ 11, "Cave", "You are deep in a cave. It is dark here, but you can see light coming from the north. The cave stretches into darkness south.", {10, -1, 12, -1} }, 
	{ 12, "Cave-In", "You are deep in a cave. A cave-in blocks a tunnel to the south. You can hear running water coming somewhere from the west.", {11, -1, -1, -1} }, 
	{ 13, "Underground River", "You are in a dark room in the cave. You feel wind and water spraying your face as you stand beside an underground river. You see pale, blue lights coming from the south, accessible if you follow the river. A small passage opens to the east.", {-1, 12, 14, -1} }, 
	{ 14, "Treasure Chamber", "You are in a room lined with strange, pale blue torches. There are piles of treasure, including hundreds of shiny gold coins, lining the room. The only way to leave is by following the river north.", {13, -1, -1, -1} }, 
	{ 15, "Forest Outskirts", "You are at the edge of the forest. There is a grassy field to the west. The forest gets thicker to the north and to the east, but there is a path in both directions.", {16, 21, -1, 9} }, 
	{ 16, "Forest", "You are on a forest path. The path stretches both north and south, and there are fewer trees to the south. There is a dense thicket to the east that may be traversable.", {17, 23, 15, -1} }, 
	{ 17, "Near the Clearing", "You are on a path at the edges of the forest. There is a clearing to the north which appears to be full of stone columns. To the south, the forest is slightly more dense.", {18, -1, 16, -1} }, 
	{ 18, "Clearing in Forest", "You are in a clearing in the forest. There are many stone podiums and columns in the area. The stone structures are lined with carved symbols, but you do not know what they mean. There is a path south that leads back into the woods.", {-1, -1, 17, -1} }, 
	{ 19, "North Clearing", "You are in the middle of a clearing in the forest. There are several stone podiums in area. Each of the podiums have intricate carvings lining them. This must be a truly ancient area. There is a tunnel that leads south, and a path that leads back into the woods to the north.", {20, -1, 18, -1} }, 
	{ 20, "Deep Forest", "You are walking on a forest path. The path runs south into a clearing. There are thick, impassable thickets north and south, and a steep rocky wall to the east.", {-1, -1, 19, -1} }, 
	{ 21, "Forest Path", "You are walking through the forest. Dense underbrush is all around, but you are on a clear footpath that runs east and west.", {-1, 22, -1, 15} }, 
	{ 22, "Curve in the Forest Path", "You are walking along the forest path. To the north, the forest appears to be more dense. To the west, the forest is less dense.", {23, -1, -1, 21} }, 
	{ 23, "The Familiar Copse", "You are walking along a path in the forest. The path runs north and south. The path is split in the middle by a grassy patch with four trees growing closely together.", {24, -1, 22, -1} }, 
	{ 24, "Dark Forest", "You are in a dark portion of the forest where the trees are blocking out light from the sky. There is dense underbrush that makes it very hard to see through the trees, but there is a footpath that runs south and east.", {-1, -1, 23, -1} }, 
	{ 25, "Dark Forest", "You are on a path through the forest that runs west and north. The trees all around you are thick and hard to see through, and the air feels very still. You can't see anything east or south, only darkness.", {26, -1, -1, 24} }, 
	{ 26, "Thicket Dead End", "You are walking in the forest. The forest path from the south seems to end here, with dense overgrowth in all other directions.", {27, 23, 25, 17} }, 
	{ 27, "Light Forest", "You are walking in a light section of the forest. The trees have thinned out here. To the south, you see a dense thicket of trees. A path leads to the north, where you see a mountain rising above the trees.", {28, -1, 26, -1} }, 
	{ 28, "Light Forest Near the Tower", "You are walking along a forest path, which runs south and west from here. There is a mountain with small, carved alcoves that blocks the way to the north. The path leads west to a large tower to the west which leads up to a bluff at the top the mountain.", {-1, -1, 27, 29} }, 
	{ 29, "Base of the Tower", "You are standing at the base of a large tower that leads to the top of the mountain bluff, which you can enter to the west. There are small, carved alcoves in the mountains to the north. A path leads into the forest to the east.", {-1, 28, -1, -1} }, 
	{ 30, "Bluff Overlooking the Forest", "You are at the top of a bluff at the northmost point of the forest. Looking around, you can see the entire forest, and to the west, you can see the small town. There is a rocky hill to the west, a twisting stone path to the north, and the entrance to a tower to the east.", {31, -1, -1, 20} }, 
	{ 31, "Twisting Path", "You are walking on a twisting, cobblestone path that runs north and south. To the north, you see a giant stone gate. To the south is a tower and bluff that overlooks the forest.", {32, -1, 30, -1} }, 
	{ 32, "The Stone Gate", "You are at the northmost part of a twisting cobblestone path. There is a giant stone gate that leads to the north. The gate looks old, like it was built many centuries ago.", {-1, -1, 31, -1} }, 
	{ 33, "Hidden Temple", "You enter an ancient temple. Tall stone walls rise up around you on all sides, no ceiling. There is a two-story tall gold throne sitting beside the north wall.", {-1, -1, 32, -1} }, 
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

void
room_exits(int id, char exits[32])
{
	char directions[4][6] = {"North", "East", "South", "West"};
	int i;

	/* Output "Exits" to exits */
	sprintf(exits, "Exits: ");
	/* Output exits to the string */
	id = which_room(id);
	if (id != -1) {
		for (i = 0; i < 4; i++) {
			if (ROOMS[id].exits[i] != -1) {
				sprintf(exits, "%s %s", exits, directions[i]);
			}
		}
	} else {
		sprintf(exits, "none");
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
