CC=gcc
FLAGS=-Wall -g

SRC_DIR=lib
SDL_DIR=${PWD}/${SRC_DIR}
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=main

all: sdl_text
sdl_text: main.c
	${CC} -o ${PROG} main.c ${LIBS} ${INCS} ${FLAGS}
	./main
	
clean:
	rm -f ${PROG}
	rm -f *.o
