#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entite.h"

void initialiserJoueur(entite_t * joueur){
    joueur->attaque = 10;
    joueur->defense = 5;
    joueur->pv = 100;
    joueur->pvMax = 100;
    joueur->vitesse = 5;
}

void initialiserEnnemi(entite_t * ennemi){
    ennemi->attaque = 7;
    ennemi->defense = 5;
    ennemi->pv = 50;
    ennemi->pvMax = 50;
    ennemi->vitesse = 3;
}

/* Fonction utilisée pour attaquer tout simplement, la défense agit comme l'armure dans lol */
void attaquer(entite_t * attaquant, entite_t * defenseur){
    defenseur->pv -= attaquant->attaque - defenseur->defense;
}