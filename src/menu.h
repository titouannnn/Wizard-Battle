#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "./fonctions.h"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 75

#define JAUNE ((Couleur_t){255, 255, 0})
#define BLEU ((Couleur_t){0, 0, 255})
#define ROUGE ((Couleur_t){255, 0, 0})
#define VERT ((Couleur_t){0, 255, 0})
#define NOIR ((Couleur_t){0, 0, 0})
#define BLANC ((Couleur_t){255, 255, 255})
#define ORANGE ((Couleur_t){255, 165, 0})

// Structure pour représenter un bouton
typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
} Button;

Button createButton(SDL_Renderer* renderer, const char* text, int x, int y, int width, int height, Couleur_t couleur);
void drawButton(SDL_Renderer* renderer, Button button);
int clickButton(SDL_Event event, Button button);
int mouseOnButton(Button button);
void initBoutons(Button *jouerButton, Button *difficulteButton, Button *facileButton, Button *normalButton, Button *difficileButton, Button *accueilButton, Button *gameoverButton, Button *retryButton, SDL_Renderer *rendu);

/* Fonction des 3 menus */

void menuPrincipal(SDL_Renderer *rendu, Button jouerButton, Button difficulteButton);
void menuDifficulte(SDL_Renderer *rendu, Button facileButton, Button normalButton, Button difficileButton, Button accueilButton);
int menuGameOver( SDL_Renderer *rendu, Button gameoverButton, Button retryButton, int vague, int duree_partie, int nb_kill);


#endif