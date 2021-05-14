#ifndef ROOM_H
#define ROOM_H

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

extern char	*room_name(int id);
extern char	*room_desc(int id);
extern int	 get_exit(int id, int dir);

#endif
