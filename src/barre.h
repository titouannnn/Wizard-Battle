/**
 * @file barre.h
 * @brief Gestion des barres de vie et de mana
 */
#ifndef BARRE_H
#define BARRE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define BAR_WIDTH 300
#define BAR_HEIGHT 20

/**
 * \struct bar_t
 * \brief Structure représentant une barre quelconque.
*/
typedef struct {
    int x, y;     /**< Position de la barre de vie */ 
    int width;    /**< Largeur de la barre de vie */
    int maxWidth; /**< Largeur maximale de la barre de vie */
} bar_t;

// Structure pour représenter une couleur en RGB
typedef struct {
    int red;
    int green;
    int blue;
} Couleur_t;

SDL_Texture *creationTextureBar(SDL_Renderer *rendu, Couleur_t couleur);
void initBar(bar_t *bar, int x, int y, int maxWidth);
void updateBar(bar_t *bar, SDL_Rect *barRect, int currentValue, int maxValue);

#endif