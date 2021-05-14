TARGET=textgame
CC?=clang
CFLAGS=-lSDL2 -I./lib -Wall -Wextra -Wpedantic

CFILES=./src/main.c ./src/disp.c ./src/font.c ./src/room.c ./src/type.c

default:
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILES)
clean:
	rm -f $(TARGET)
debug:
	$(CC) $(CFLAGS) -o $(TARGET) -g $(CFILES)
run: default
	./$(TARGET)
all: default
