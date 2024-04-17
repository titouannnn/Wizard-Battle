
/**
 * @file projectile.h
 * @brief Gestion des projectiles
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "fonctions.h"
#include "carte.h"


#define PROJ_ENNEMI 1
#define PROJ_JOUEUR 2

#define MAX_PROJ 512

#define M_PI 3.14159265358979323846

#define DIM_SPRITE_LANCER_X 48
#define DIM_SPRITE_LANCER_Y 48

#define DIM_SPRITE_IMPACT_X 48
#define DIM_SPRITE_IMPACT_Y 48

/**
 * \struct projectiles_s
 * \brief Structure représentant un projectile.
 */

typedef struct projectiles_s projectiles_t;

struct projectiles_s {
    int id;

    float vitesse;  /**< Vitesse du projectile */
    float x;    /**< Position horizontale du projectile */
    float y;    /**< Position verticale du projectile */
    int w;  /**< Largeur du projectile */
    int h;  /**< Hauteur du projectile */

    float vx; /**< Vitesse horizontale du projectile */
    float vy; /**< Vitesse verticale du projectile */

    double angle; /**< Angle du projectile */
    int animation_impact; /**< Animation de l'impact */

    SDL_Rect rect; /**< Rectangle du projectile */
    SDL_Rect sprite; /**< Sprite du projectile */

    int collision; /**< Collision du projectile */
    
    void (*initProj)(projectiles_t *projectile, float px, float py, float mx, float my, int, SDL_Rect *camera); /**< Fonction d'initialisation d'un projectile */
    void (*verifCollisionProj)(projectiles_t *, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]);   /**< Fonction de vérification de collision d'un projectile */
    void (*updateProj)(projectiles_t *, SDL_Rect *, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]); /**< Fonction de mise à jour d'un projectile */
    void (*renderProj)(SDL_Renderer *, projectiles_t *, int frame); /**< Fonction d'affichage d'un projectile */

} ;



void initTabProj(projectiles_t proj[MAX_PROJ]);
void chargerTexturesProj(SDL_Renderer *rendu);
void projectile_creer(projectiles_t *projectile) ;
void initProj(projectiles_t *projectile, float px, float py, float mx, float my, int id, SDL_Rect *cameraRect);
void verifCollisionProj(projectiles_t *projectile, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]);
void updateProj(projectiles_t *projectile, SDL_Rect *cameraRect, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]);
void actualisationSpriteProj(projectiles_t *projectile, int nb_sprite, int frame, int largeur, int hauteur, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu);
void renderProj(SDL_Renderer *rendu, projectiles_t *projectile, int frame);

#endif // PROJECTILE_H