/**
 * \file barre.c
 * \brief Ce fichier contient les fonctions liées à la gestion des barres en jeu.
 * 
 * Ce fichier contient les définitions des fonctions permettant de gérer les barres de vie et de mana des joueurs et des ennemis.
 * 
 */
#include "barre.h"

/**
 * \brief Crée une texture pour la barre de vie ou de mana.
 * 
 * Cette fonction crée une texture pour la barre de vie ou de mana en fonction de la couleur passée en paramètre.
 * 
 * \param rendu Le renderer SDL pour l'affichage.
 * \param couleur La couleur de la barre.
 * 
 * \return La texture de la barre de vie ou de mana.
 * 
*/
SDL_Texture *creationTextureBar(SDL_Renderer *rendu, Couleur_t couleur){
    SDL_Surface *barSurface = SDL_CreateRGBSurface(0, BAR_WIDTH, BAR_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(barSurface, NULL, SDL_MapRGB(barSurface->format, couleur.red, couleur.green, couleur.blue));
    SDL_Texture *barTexture = SDL_CreateTextureFromSurface(rendu, barSurface);
    SDL_FreeSurface(barSurface);
    return barTexture;


}


/**
 * \brief Initialise la barre de vie ou de mana.
 * 
 * Cette fonction initialise la barre de vie ou de mana en fonction des paramètres passés.
 * 
 * \param bar La barre de vie ou de mana à initialiser.
 * \param x La position en x de la barre.
 * \param y La position en y de la barre.
 * \param maxWidth La largeur maximale de la barre.
*/
void initBar(bar_t *bar, int x, int y, int maxWidth) {
    bar -> x = x;
    bar -> y = y;
    bar -> width = maxWidth;
    bar -> maxWidth = maxWidth;
}

/**
 * \brief Met à jour la barre passée en paramètre.
 * 
 * Cette fonction met à jour la barre de vie ou de mana en fonction des paramètres passés.
 * 
 * \param bar La barre de vie ou de mana à mettre à jour.
 * \param barRect Le rectangle de la barre de vie ou de mana.
 * \param currentValue La valeur actuelle de la barre.
 * \param maxValue La valeur maximale de la barre.
*/
void updateBar(bar_t *bar, SDL_Rect *barRect, int currentValue, int maxValue) {
    /* Je veux que ma barre de ma vie ai la meme taille n'importe le montant de vie */
    // Calculer le pourcentage de vie actuel par rapport à la vie maximale
    float valuePercentage = (float)currentValue / (float)maxValue;

    // Mettre à jour la largeur de la barre de vie en fonction du pourcentage de vie
    barRect->w = (int)(BAR_WIDTH * valuePercentage);
}





