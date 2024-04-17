#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdarg.h>

#include "./fonctions.h"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 75

/**
 * \struct Button
 * \brief Structure pour représenter un bouton.
 */
typedef struct {
    SDL_Rect rect;  /**< Rectangle définissant la position et la taille du bouton. */
    SDL_Texture* texture;   /**< Texture du bouton. */
} Button;


Button createButton(SDL_Renderer* renderer, TTF_Font *font, const char* text, int x, int y, int width, int height, Couleur_t couleur);

void drawButton(SDL_Renderer* renderer, Button button);

int clickButton(SDL_Event event, Button button);

int mouseOnButton(Button button);

void initBoutons(TTF_Font *font, Button *jouerButton, Button *difficulteButton, Button *facileButton, Button *normalButton, Button *difficileButton, Button *accueilButton, Button *gameoverButton, Button *retryButton, Button *reprendreButton, SDL_Renderer *rendu);

void menuFonc(int menu, SDL_Renderer * rendu, Button jouerButton, Button difficulteButton, Button difficileButton, Button accueilButton, Button gameoverButton, Button retryButton, Button facileButton, Button normalButton);

void menuPrincipal(SDL_Renderer *rendu, TTF_Font *font, Button jouerButton, Button difficulteButton);

void MenuPause(SDL_Renderer *rendu, Button reprendreButton, Button retryButton, Button accueilButton);

void menuDifficulte(SDL_Renderer *rendu, Button facileButton, Button normalButton, Button difficileButton, Button accueilButton, char* difficulte, TTF_Font *font);

int menuGameOver( SDL_Renderer *rendu, TTF_Font *font, Button gameoverButton, Button retryButton, int vague, int duree_partie, int nb_kill);

void afficherMessage(SDL_Renderer *rendu, TTF_Font *font, char *texte, int x, int y, int taille);

/* FONCTIONS DE DESTRUCTION */

void destructionBoutons(Button *bouton, ...) ;


#endif