#ifndef CARTE_H
#define CARTE_H

#include <SDL2/SDL_image.h>
#include "fonctions.h"

#define TILE_WIDTH 160
#define TILE_HEIGHT 160

#define NB_TILE_WIDTH 18
#define NB_TILE_HEIGHT 18

#define TILE_VERTE 0



/*Représentation de la position du joueur*/


/**
 * @struct case_t
 * @brief Structure représentant une case sur la carte.
 * 
 * Cette structure contient les coordonnées x et y d'une case sur la carte.
 */
typedef struct {
    int casx; /**< Coordonnée x de la case. */
    int casy; /**< Coordonnée y de la case. */
} case_t;

/**
 * @struct positionJoueur_t
 * @brief Structure représentant la position du joueur sur la carte.
 * 
 * Cette structure contient les cases correspondant aux quatre coins du joueur.
 */
typedef struct{
    case_t case_hg; /**< Case en haut à gauche du joueur. */
    case_t case_hd; /**< Case en haut à droite du joueur. */
    case_t case_bg; /**< Case en bas à gauche du joueur. */
    case_t case_bd; /**< Case en bas à droite du joueur. */
}positionJoueur_t;

/**
 * @struct colision_t
 * @brief Structure représentant les collisions du joueur.
 * 
 * Cette structure contient les informations de collision pour chaque direction (haut, bas, gauche, droite) 
 * et un pointeur vers la position du joueur.
 */
typedef struct{
    int haut; /**< Collision en haut. */
    int bas; /**< Collision en bas. */
    int gauche; /**< Collision à gauche. */
    int droite; /**< Collision à droite. */
    positionJoueur_t *position; /**< Pointeur vers la position du joueur. */
}colision_t;

positionJoueur_t * initPositionJoueur();
colision_t * initColision();

void chargerCarte(char * fichier, int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], int nb);
int afficherCarte(int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu,
    SDL_Rect * camera,
    positionJoueur_t position,
    colision_t *colision,
    SDL_Texture *tilemap, 
    int nb);

void chargerColisions(int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT], int nb);
void colisions(positionJoueur_t position, colision_t * colision, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]);
int peutDash(positionJoueur_t position,int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT], int direction);

#endif