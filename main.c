#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdlib.h>
#include "src/fonctions.h"
#include "src/carte.h"

SDL_Renderer *rendu;
SDL_Window *fenetre;

SDL_Rect pers_source, pers_destination;
SDL_Rect * cameraRect;

// Alors j'ai crée un structure couleur vu qu'en C y a pas de tuple pour gérer les couleurs donc si tu dois mapper des couleurs n'hesite pas à utiliser ces constantes au lieu d'écrire (255,0,255)
const Couleur_t JAUNE = {255,255,0};
const Couleur_t BLEU = {0,0,255};
const Couleur_t ROUGE = {255,0,0};
const Couleur_t VERT = {0,255,0};

int main() {
    int isRunning = 1;
    int tile_lvl1[NB_TILE_WIDTH][NB_TILE_WIDTH];
    initialisation(&fenetre, &rendu);
    chargerTextures(rendu);

    cameraRect = malloc(sizeof(SDL_realloc));
    
    cameraRect->h = CAMERA_HEIGHT;
    cameraRect->w = CAMERA_WIDTH;   

    pers_destination.y = WINDOWS_HEIGHT/ 2 - TAILLE_SPRITE_PLAYER / 2;
    pers_destination.x = WINDOWS_WIDTH / 2 - TAILLE_SPRITE_PLAYER / 2;

    cameraRect->x = pers_destination.x;
    cameraRect->y = pers_destination.y;

    // Gestion des événements SDL
    SDL_Event event;
    int frame = 0;
    Uint32 temps_ancien = SDL_GetTicks();
    Uint32 temps_actuel;
    int delta_temps;

    SDL_Texture *barTextureVie = creationTextureBar(rendu, JAUNE);

    SDL_Texture *barTextureVieRestant = creationTextureBar(rendu, ROUGE);

    // Initialisation de la srtructure barre de vie
    HealthBar healthBar;
    initHealthBar(&healthBar, 50, 50, HEALTH_BAR_WIDTH);

    // Création de deux rectangles : un pour la barre de vie fixe et l'autre pour celle qui baisse (vie restante)
    SDL_Rect healthBarRect = { healthBar.x, healthBar.y, healthBar.maxWidth, HEALTH_BAR_HEIGHT };
    SDL_Rect *healthBarRectRestant = malloc(sizeof(SDL_Rect));
    *healthBarRectRestant = (SDL_Rect){ healthBar.x, healthBar.y, healthBar.width, HEALTH_BAR_HEIGHT };

    // Variable temporaire
    int count = 100;

    chargerCarte("src/tilemap_lvl1.txt",tile_lvl1);
    
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            // Pour fermer la fenêtre 
            if (event.type == SDL_QUIT) {
                isRunning = 0; 
            } 
        }
        

        //calcul du temps
        temps_actuel = SDL_GetTicks();
        delta_temps += temps_actuel - temps_ancien;
        temps_ancien = temps_actuel;

        if(delta_temps >= 100){ // ms entre les images du sprite
            delta_temps = 0;
            frame = (frame + 1) % 6;
            // Test pour tester si l'affichage est OK
            updateHealthBar(&healthBar, healthBarRectRestant, count-1);
            count--;
        }

        

        // Récupération de l'état du clavier : 
        const Uint8 *clavier = SDL_GetKeyboardState(NULL);
        
        
        SDL_RenderClear(rendu);

        updateCamera(&pers_destination,rendu, cameraRect,tile_lvl1);

        action(clavier, &pers_destination, &pers_source, frame, DIM_SPRITE_PLAYER, rendu);

        // Rendu de la barre de viepers_destination
        SDL_RenderCopy(rendu, barTextureVie, NULL, &healthBarRect);
        SDL_RenderCopy(rendu, barTextureVieRestant, NULL, healthBarRectRestant);

        SDL_RenderPresent(rendu);

        SDL_Delay(DELAI);
    }
    free(healthBarRectRestant);
    return fin(fenetre, rendu);
}