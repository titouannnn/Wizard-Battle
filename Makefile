CC=gcc
FLAGS=-Wall -g

PROJECT_DIR=${PWD}
SDL_LIB_DIR=${PROJECT_DIR}/lib
SDL_INC_DIR=${PROJECT_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lm
INCS=-I${SDL_INC_DIR}
PROG=jeu

all: jeu
jeu: main.o fonctions.o carte.o menu.o entite.o projectile.o barre.o vague.o
	${CC} main.o vague.o projectile.o entite.o menu.o fonctions.o carte.o barre.o -o bin/${PROG} ${LIBS} ${INCS} ${FLAGS}
	./bin/jeu
	make clean

main.o: main.c src/fonctions.h src/menu.h src/entite.h src/projectile.h src/carte.h src/barre.h src/vague.h
	${CC} -c main.c

fonctions.o: src/fonctions.c src/barre.h
	${CC} -c src/fonctions.c

carte.o: src/carte.c 
	${CC} -c src/carte.c

menu.o: src/menu.c src/fonctions.h 
	${CC} -c src/menu.c

barre.o: src/barre.c src/barre.h
	${CC} -c src/barre.c

projectile.o: src/projectile.c src/projectile.h src/carte.h src/fonctions.h
	${CC} -c src/projectile.c

entite.o: src/entite.c src/entite.h src/carte.h src/projectile.h src/fonctions.h
	${CC} -c src/entite.c

vague.o: src/vague.c src/vague.h src/fonctions.h
	${CC} -c src/vague.c




clean:
	rm -f *.o bin/${PROG}
