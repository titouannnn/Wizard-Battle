CC=gcc
FLAGS=-Wall -g

PROJECT_DIR=${PWD}
SDL_LIB_DIR=${PROJECT_DIR}/lib
SDL_INC_DIR=${PROJECT_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=jeu

all: jeu
jeu: main.o fonctions.o
	${CC} main.o fonctions.o -o bin/${PROG} ${LIBS} ${INCS} ${FLAGS}
	./bin/jeu
	make clean

main.o: main.c src/fonctions.h
	${CC} -c main.c

fonctions.o: src/fonctions.c
	${CC} -c src/fonctions.c

clean:
	rm -f *.o

msproper: clean
	rm -i ${PROG}
