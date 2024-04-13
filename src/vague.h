#ifndef VAGUE_H
#define VAGUE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "fonctions.h"

void afficherTemps(SDL_Renderer *rendu, int temps);
void afficherVague(SDL_Renderer *rendu, int vague, int duree_vague);
void afficherNbKill(SDL_Renderer *rendu, int nbKill, int nbEnnemis);
void nextVague(int *vague, int *nb_ennemis, int *nb_kill, int *ennemis_initialises);
void afficherScore(SDL_Renderer *rendu, int vague, int temps, int nbKills);


#endif