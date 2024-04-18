#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "src/projectile.h"
#include "src/entite.h"
#include "src/fonctions.h"
#include "src/carte.h"
#include "src/menu.h"
#include "src/barre.h"
#include "src/vague.h"

SDL_Renderer *rendu;
SDL_Window *fenetre;
SDL_Rect pers_source, pers_destination;
SDL_Rect * cameraRect;
positionJoueur_t position;
colision_t *colision;
joueur_t joueur;
ennemi_t ennemi[NB_ENNEMI];
projectiles_t projJoueur[MAX_PROJ];
projectiles_t projEnnemi[MAX_PROJ];
SDL_Event event;
Uint32 temps_ancien;
Uint32 temps_actuel;
Uint32 gain_mana;
SDL_Texture *barTextureVie ;
SDL_Texture *barTextureVieMax ;
bar_t healthBar;
SDL_Texture *barTextureMana ;
SDL_Texture *barTextureManaMax ;
bar_t manaBar;
Button jouerButton, difficulteButton, facileButton, normalButton, difficileButton, accueilButton, retryButton, reprendreButton;


TTF_Font *arial;
SDL_Texture* messageScore;
int vague;
int nb_ennemis;
int nb_kill;
int ennemis_initialises;

int projNbEnnemi; 
int projNbJoueur;
int isRunning; 
int frame; 
int delta_temps;
int duree_vague;
int duree_partie;

