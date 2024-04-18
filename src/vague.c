#include "vague.h"

void nextVague(int *vague, int *nb_ennemis, int *nb_kill, int *ennemis_initialises)
{
    printf("Vague suivante\n");
    *vague += 1;
    *nb_ennemis += 5;
    *nb_kill = 0;
    *ennemis_initialises = 0;
}

void afficherVague(SDL_Renderer *rendu, TTF_Font *font, int vague, int duree_vague) {
    SDL_Color blanc = {255, 255, 255};
    char texte[20];
    sprintf(texte, "Vague %d", vague);

    // Allouer dynamiquement la mémoire pour la chaîne de caractères
    char* texte_dyn = malloc(strlen(texte) + 1);
    if (texte_dyn == NULL) {
        // Gestion de l'erreur de l'allocation mémoire
        printf("Erreur d'allocation de mémoire\n");
        return;
    }
    strcpy(texte_dyn, texte); // Copier la chaîne dans l'espace alloué dynamiquement

    
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, texte_dyn, blanc);
    SDL_SetSurfaceAlphaMod(surfaceMessage, (0.5*duree_vague));
    free(texte_dyn); // Libérer la mémoire allouée dynamiquement

    SDL_Texture* Message = SDL_CreateTextureFromSurface(rendu, surfaceMessage);

    SDL_Rect messageRect;

    messageRect.x = WINDOWS_WIDTH/2-240;
    messageRect.y = WINDOWS_HEIGHT/2 - 300;
    messageRect.w = 500;
    messageRect.h = 150;

    SDL_RenderCopy(rendu, Message, NULL, &messageRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void afficherNbKill(SDL_Renderer *rendu, int nbKill, int nbEnnemis) {
    TTF_Font* font = TTF_OpenFont("police/arial.ttf", 30);
    SDL_Color blanc = {255, 255, 255};
    char texte[20];
    sprintf(texte, "%d / %d", nbKill, nbEnnemis);

    // Allouer dynamiquement la mémoire pour la chaîne de caractères
    char* texte_dyn = malloc(strlen(texte) + 1);
    if (texte_dyn == NULL) {
        // Gestion de l'erreur de l'allocation mémoire
        printf("Erreur d'allocation de mémoire\n");
        return;
    }
    strcpy(texte_dyn, texte); // Copier la chaîne dans l'espace alloué dynamiquement

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, texte_dyn, blanc);
    free(texte_dyn); // Libérer la mémoire allouée dynamiquement

    SDL_Texture* Message = SDL_CreateTextureFromSurface(rendu, surfaceMessage);

    SDL_Rect messageRect;

    messageRect.x = 100;
    messageRect.y = 10;
    messageRect.w = 100;
    messageRect.h = 50;

    SDL_RenderCopy(rendu, Message, NULL, &messageRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void afficherTemps(SDL_Renderer *rendu, int temps) {
    TTF_Font* font = TTF_OpenFont("police/arial.ttf", 30);
    SDL_Color blanc = {255, 255, 255};
    char texte[20];
    sprintf(texte, "Time : %d", temps);

    // Allouer dynamiquement la mémoire pour la chaîne de caractères
    char* texte_dyn = malloc(strlen(texte) + 1);
    if (texte_dyn == NULL) {
        // Gestion de l'erreur de l'allocation mémoire
        printf("Erreur d'allocation de mémoire\n");
        return;
    }
    strcpy(texte_dyn, texte); // Copier la chaîne dans l'espace alloué dynamiquement

    SDL_Surface* surfaceMessage;
    
    surfaceMessage = TTF_RenderText_Solid(font, texte_dyn, blanc);
    free(texte_dyn); // Libérer la mémoire allouée dynamiquement

    SDL_Texture* Message = SDL_CreateTextureFromSurface(rendu, surfaceMessage);

    SDL_Rect messageRect;

    messageRect.x = 200;
    messageRect.y = 10;
    messageRect.w = 100;
    messageRect.h = 50;

    SDL_RenderCopy(rendu, Message, NULL, &messageRect);

    
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
}


