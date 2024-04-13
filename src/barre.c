#include "barre.h"

SDL_Texture *creationTextureBar(SDL_Renderer *rendu, Couleur_t couleur){
    SDL_Surface *barSurface = SDL_CreateRGBSurface(0, BAR_WIDTH, BAR_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(barSurface, NULL, SDL_MapRGB(barSurface->format, couleur.red, couleur.green, couleur.blue));
    SDL_Texture *barTexture = SDL_CreateTextureFromSurface(rendu, barSurface);
    SDL_FreeSurface(barSurface);
    return barTexture;


}

// Initialise la barre de vie du joueur au max
void initBar(bar_t *bar, int x, int y, int maxWidth) {
    bar -> x = x;
    bar -> y = y;
    bar -> width = maxWidth;
    bar -> maxWidth = maxWidth;
}

// Met à jour la barre de vie du joueur (currentHealth prend un pourcentage)
void updateBar(bar_t *bar, SDL_Rect *barRect, int currentValue, int maxValue) {
    /* Je veux que ma barre de ma vie ai la meme taille n'importe le montant de vie */
    // Calculer le pourcentage de vie actuel par rapport à la vie maximale
    float valuePercentage = (float)currentValue / (float)maxValue;

    // Mettre à jour la largeur de la barre de vie en fonction du pourcentage de vie
    barRect->w = (int)(BAR_WIDTH * valuePercentage);
}





