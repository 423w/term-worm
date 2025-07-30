CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBS=-lncurses
TARGET=term-worm
SOURCES=main.c game.c platform.c player.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean 