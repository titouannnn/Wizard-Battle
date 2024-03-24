#ifndef PROJECTILE_H
#define PROJECTILE_H

/* https://github.com/JOJOBOIIIIIII/Projectiles-Scrolling */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "fonctions.h"


typedef struct projectiles_s projectiles_t;

struct projectiles_s {
    float vitesse;
    float x;
    float y;
    int w;
    int h;

    float vx;
    float vy;

    SDL_Rect rect;
    int collision; /* Si la collision est égal à un 1, l'ennemi est détecté */
    
    void (*init)(projectiles_t *, float, float, float, float, SDL_Rect *);
    int (*verifCollision)(projectiles_t *);
    void (*update)(projectiles_t *, SDL_Rect *);
    void (*render)(SDL_Renderer *, projectiles_t *);

} ;


void projectile_creer(projectiles_t *projectile) ;
void init(projectiles_t *projectile, float px, float py, float mx, float my, SDL_Rect *cameraRect);
int verifCollision(projectiles_t *projectile);
void update(projectiles_t *projectile, SDL_Rect *cameraRect);
void render(SDL_Renderer *rendu, projectiles_t *projectile);

#endif // PROJECTILE_H