#ifndef CARTE_H
#define CARTE_H

#include <SDL2/SDL_image.h>
#include "fonctions.h"

#define TILE_WIDTH 160
#define TILE_HEIGT 160

#define NB_TILE_WIDTH 18
#define NB_TILE_HEIGHT 18

#define TILE_VERTE 0

typedef struct {
    int num;
    SDL_Texture *tex;
    SDL_Rect tile;
}tile_t;

/*Représentation de la position du joueur*/

typedef struct {
    int casx;
    int casy;
} case_t;

typedef struct {
    int posx;
    int posy;
    case_t caseJoueur;
} position_t;


typedef struct{
    position_t haut_droit;
    position_t haut_gauche;
    position_t bas_droit;
    position_t bas_gauche;

}positionJoueur_t;


void chargerCarte(char * fichier, int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT]);
int afficherCarte(int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu,
    SDL_Texture *tabTex[5],
    SDL_Rect * camera,
    positionJoueur_t position);

#endif