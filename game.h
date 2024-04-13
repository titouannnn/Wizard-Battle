#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
SDL_Texture *barTextureVie ;
SDL_Texture *barTextureVieMax ;
bar_t healthBar;
bar_t manaBar;
Button jouerButton, difficulteButton, facileButton, normalButton, difficileButton, accueilButton, gameoverButton, retryButton;

SDL_Texture* messageScore;
int vague;
int nb_ennemis;
int nb_kill;
int ennemis_initialises;

int projNbEnnemi = 0; 
int projNbJoueur = 0;
int isRunning = 1; 
int frame = 0; 
int delta_temps = 0;
int duree_vague;
int duree_partie;



// Définition des couleurs avec les directives de préprocesseur
#define JAUNE ((Couleur_t){255, 255, 0})
#define BLEU ((Couleur_t){0, 0, 255})
#define ROUGE ((Couleur_t){255, 0, 0})
#define VERT ((Couleur_t){0, 255, 0})
#define NOIR ((Couleur_t){0, 0, 0})
#define BLANC ((Couleur_t){255, 255, 255})
#define ORANGE ((Couleur_t){255, 165, 0})

