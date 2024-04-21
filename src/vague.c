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

void afficherNbKill(SDL_Renderer *rendu, TTF_Font *font, int nbKill, int nbEnnemis) {
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

    messageRect.x = WINDOWS_WIDTH-130;
    messageRect.y = 10;
    messageRect.w = 100;
    messageRect.h = 50;

    SDL_RenderCopy(rendu, Message, NULL, &messageRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void afficherTemps(SDL_Renderer *rendu, TTF_Font *font, int temps) {
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

    messageRect.x = WINDOWS_WIDTH-130;
    messageRect.y = WINDOWS_HEIGHT-70;
    messageRect.w = 100;
    messageRect.h = 50;

    SDL_RenderCopy(rendu, Message, NULL, &messageRect);

    
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
}

void renitialiserStats(int *joueurPv, int *joueurMana, int *joueurX, int *joueurY, int *vague, int *ennemis_initialises, int *nb_ennemis, int *nb_kill, int *projNbJoueur, int *projNbEnnemi, int *frame, int *delta_temps, float *coefDifficulte, Uint32 *gain_mana, int *duree_parti) {
    *joueurPv = 100;
    *joueurMana = 100;

    *vague = 1;
    *ennemis_initialises = 0;
    *nb_kill = 0;
    *joueurX = 400;
    *joueurY = 400;
    *projNbEnnemi = 0; 
    *projNbJoueur = 0;
    *frame = 0; 
    *delta_temps = 0;
    
    if (*coefDifficulte == 0.7){
        *nb_ennemis = 5;
    }
    else if (*coefDifficulte == 1){
        *nb_ennemis = 7;
    }
    else if (*coefDifficulte == 1.3){
        *nb_ennemis = 10;
    }

    *gain_mana = SDL_GetTicks();
    *duree_parti = SDL_GetTicks();
}

void gameOver(int *joueurPv, int *menu, int *duree_partie){
    if (*joueurPv <= 0){
        *menu = 3;
        *duree_partie = SDL_GetTicks() - *duree_partie;
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}


void calculTemps(Uint32 *temps_actuel, int *delta_temps, Uint32 *temps_ancien, Uint32 *gain_mana, int *joueurMana, int *joueurManaMax, int *frame){
    *temps_actuel = SDL_GetTicks();
    *delta_temps += *temps_actuel - *temps_ancien;
    *temps_ancien = *temps_actuel;

    if (*temps_actuel - *gain_mana >= 500){
        *joueurMana += 10;
        if (*joueurMana > *joueurManaMax){
            *joueurMana = *joueurManaMax;
        }
        *gain_mana = *temps_actuel;
    }
    if(*delta_temps >= 100){ // ms entre les images du sprite
        *delta_temps = 0;
        *frame = (*frame + 1) % 6;
    }

}
