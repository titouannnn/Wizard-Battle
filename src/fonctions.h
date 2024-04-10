#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "carte.h"

#define WINDOWS_WIDTH 1080
#define WINDOWS_HEIGHT 720

#define DIM_SPRITE_PLAYER_X 128
#define DIM_SPRITE_PLAYER_Y 224
#define FPS 60
#define DELAI 1000 / FPS
#define VITESSE_JOUEUR_X 3
#define VITESSE_JOUEUR_Y 2

#define HAUT 0
#define BAS 1
#define DROITE 2
#define GAUCHE 3

#define LARGEUR_FOND NB_TILE_WIDTH*TILE_WIDTH
#define HAUTEUR_FOND NB_TILE_HEIGHT*TILE_HEIGHT

#define CAMERA_WIDTH 1080
#define CAMERA_HEIGHT 720

typedef struct {
    float x;
    float y;
} Camera_t;

// Structure pour représenter une couleur en RGB
typedef struct {
    int red;
    int green;
    int blue;
} Couleur_t;



SDL_Rect * initCamera();
SDL_Rect * initJoueur(int x, int y);
int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu);
void chargerTextures(SDL_Renderer *rendu, SDL_Texture * tabTile[5]);
int fin(SDL_Window *fenetre, SDL_Renderer *rendu);
void actualisationSprite(int nb_sprite, int frame, int largeur, int hauteur, int *direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu);
void action(const Uint8 *clavier, SDL_Rect *pers_destination, colision_t *colision, int *direction);
void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect);
void updateCamera(SDL_Rect *pers_destination, SDL_Renderer *rendu, SDL_Rect *cameraRect, int tab[2][NB_TILE_HEIGHT][NB_TILE_WIDTH], SDL_Texture *tabTile[5], colision_t *colision, int tabColision[NB_TILE_HEIGHT][NB_TILE_WIDTH], positionJoueur_t position);
int tabInit(SDL_Texture *tab[5], SDL_Renderer* rendu);
void initialiser_position_joueur(positionJoueur_t *positionJoueur, SDL_Rect *cameraRect, SDL_Rect *pers_destination);
void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect);
int getMousePositionDirection(SDL_Rect *pers_destination);
void affichageMenuImage(SDL_Renderer *rendu);
#endif