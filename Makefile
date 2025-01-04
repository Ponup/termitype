CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O2 -D_POSIX_C_SOURCE=199309L
TARGET = termitype
SOURCES = main.c printer.c terminal.c game_intro.c game_end.c game.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

