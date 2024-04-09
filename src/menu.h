#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "./fonctions.h"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 75

// Structure pour représenter un bouton
typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
} Button;

Button createButton(SDL_Renderer* renderer, const char* text, int x, int y, int width, int height, Couleur_t couleur);
void drawButton(SDL_Renderer* renderer, Button button);
int clickButton(SDL_Event event, Button button);
int mouseOnButton(Button button);

#endif