#ifndef VAGUE_H
#define VAGUE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "fonctions.h"

void afficherTemps(SDL_Renderer *rendu, TTF_Font *font, int temps);
void afficherVague(SDL_Renderer *rendu, TTF_Font *font, int vague, int duree_vague);
void afficherNbKill(SDL_Renderer *rendu, TTF_Font *font, int nbKill, int nbEnnemis);
void nextVague(int *vague, int *nb_ennemis, int *nb_kill, int *ennemis_initialises);
void afficherScore(SDL_Renderer *rendu, int vague, int temps, int nbKills);
void renitialiserStats(int *joueurPv, int *joueurMana, int *joueurX, int *joueurY, int *vague, int *ennemis_initialises, int *nb_ennemis, int *nb_kill, int *projNbJoueur, int *projNbEnnemi, int *frame, int *delta_temps, float *coefDifficulte, Uint32 *gain_mana, int *duree_parti);
void gameOver(int *joueurPv, int *menu, int *duree_partie);
void calculTemps(Uint32 *temps_actuel, int *delta_temps, Uint32 *temps_ancien, Uint32 *gain_mana, int *joueurMana, int *joueurManaMax, int *frame);


#endif