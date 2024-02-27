#ifndef CARTE_H
#define CARTE_H

#include <SDL2/SDL_image.h>

#define TILE_WIDTH 160
#define TILE_HEIGT 160

#define NB_TILE_WIDTH 18
#define NB_TILE_HEIGHT 18

#define TILE_VERTE 0

typedef struct tile_s{
    int type;
    SDL_Rect rect;
}tile_t;

void chargerCarte(char * fichier, int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT]);
void afficherCarte(int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT], SDL_Renderer * rendu, SDL_Texture * tile, SDL_Rect * camera);

#endif