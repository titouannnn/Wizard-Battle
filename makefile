CC = gcc
CFLAGS = -Wall -Wextra -std=c99 $(shell sdl2-config --cflags)
LDFLAGS = -lSDL2 -lSDL2_image $(shell sdl2-config --libs)

SRCS = main.c
OBJS = $(SRCS:.c=.o)
EXEC = programme

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
