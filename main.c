#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdlib.h>
#include "src/fonctions.h"

SDL_Renderer *rendu;
SDL_Window *fenetre;

SDL_Rect pers_source, pers_destination;

int main() {
    int isRunning = 1;
    initialisation(&fenetre, &rendu);
    chargerTextures(rendu);

    pers_destination.y = WINDOWS_WIDTH/ 2 - TAILLE_SPRITE_PLAYER / 2;
    pers_destination.x = WINDOWS_HEIGHT/ 2 - TAILLE_SPRITE_PLAYER / 2;

    // Gestion des événements SDL
    SDL_Event event;
    int frame = 0;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            // Pour fermer la fenêtre 
            if (event.type == SDL_QUIT) {
                isRunning = 0; 
            } 
        }
        //récupération de l'état du clavier : 
        const Uint8 *clavier = SDL_GetKeyboardState(NULL);
        frame = (frame + 1) % 6;
        
        action(clavier, &pers_destination, &pers_source, frame, DIM_SPRITE_PLAYER, rendu);

        SDL_Delay(DELAI);
    }
    return fin(fenetre, rendu);
}
