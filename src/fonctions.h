#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

#include "carte.h"
#include "barre.h"

#define WINDOWS_WIDTH 1080
#define WINDOWS_HEIGHT 720

#define DIM_SPRITE_PLAYER_X 128
#define DIM_SPRITE_PLAYER_Y 224
#define FPS 60
#define DELAI 1000 / FPS
#define VITESSE_JOUEUR_X 6
#define VITESSE_JOUEUR_Y 4

#define HAUT 0
#define BAS 1
#define DROITE 2
#define GAUCHE 3

#define LARGEUR_FOND NB_TILE_WIDTH*TILE_WIDTH
#define HAUTEUR_FOND NB_TILE_HEIGHT*TILE_HEIGHT

#define CAMERA_WIDTH 1080
#define CAMERA_HEIGHT 720

#define JAUNE ((Couleur_t){255, 255, 0})

#define ROUGE ((Couleur_t){255, 0, 0})

#define VERT ((Couleur_t){0, 204, 0})
#define VERT_FONCE ((Couleur_t){0, 51, 0})

#define BLEU ((Couleur_t){0, 102, 204})
#define BLEU_FONCE ((Couleur_t){0, 25, 51})

#define NOIR ((Couleur_t){0, 0, 0})
#define BLANC ((Couleur_t){255, 255, 255})
#define ORANGE ((Couleur_t){255, 165, 0})


SDL_Rect * initCamera();
SDL_Rect * initJoueur(int x, int y);
int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu);
void chargerTextures(SDL_Renderer *rendu);
int fin(SDL_Window *fenetre, SDL_Renderer *rendu, TTF_Font *arial);
void actualisationSprite(int nb_sprite, int hauteur, int *direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu);
void action(const Uint8 *clavier, SDL_Rect *pers_destination, colision_t *colision, int *direction);
void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect);
void updateCamera(SDL_Rect *pers_destination, SDL_Renderer *rendu, SDL_Rect *cameraRect, int tab[2][NB_TILE_HEIGHT][NB_TILE_WIDTH], colision_t *colision, int tabColision[NB_TILE_HEIGHT][NB_TILE_WIDTH], positionJoueur_t position);
void initialiser_position_joueur(positionJoueur_t *positionJoueur, SDL_Rect *cameraRect, SDL_Rect *pers_destination);
void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect);
int getMousePositionDirection(SDL_Rect *pers_destination);
void affichageMenuImage(SDL_Renderer *rendu);

void initFonctions(
    int tilemap[2][NB_TILE_WIDTH][NB_TILE_WIDTH],
    int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT],
    SDL_Window **fenetre,
    SDL_Renderer **rendu,
    SDL_Rect **cameraRect,
    positionJoueur_t *position,
    colision_t **colision,
    SDL_Rect *pers_destination,
    Uint32 *temps_ancien,
    SDL_Texture **barTextureVieMax,
    SDL_Texture **barTextureVie,
    bar_t *healthBar,
    SDL_Texture **barTextureManaMax,
    SDL_Texture **barTextureMana,
    bar_t *manaBar
);



#endif