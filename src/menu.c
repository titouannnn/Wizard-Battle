
/**
 * @file projectile.h
 * @brief Gestion des projectiles
 */

#include "./menu.h"

/**
 * \brief Crée un bouton avec du texte.
 *
 * \param renderer Rendu SDL.
 * \param text Texte à afficher sur le bouton.
 * \param x Position horizontale du bouton.
 * \param y Position verticale du bouton.
 * \param width Largeur du bouton.
 * \param height Hauteur du bouton.
 * \param couleur Couleur du texte du bouton.
 * \return Button Structure représentant le bouton créé.
 */

void afficherMessage(SDL_Renderer *rendu, TTF_Font *font, char *texte, int x, int y, int taille){
    // Créer la surface de texte
    SDL_Color color = {0, 0, 0};
    SDL_Surface* surfaceMessage;
    
    surfaceMessage = TTF_RenderText_Solid(font, texte, color);
    if (!surfaceMessage) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Texture* messageScore = SDL_CreateTextureFromSurface(rendu, surfaceMessage);

    SDL_Rect messageRect;

    messageRect.x = x;
    messageRect.y = y;
    messageRect.w = taille;
    messageRect.h = 50;

    SDL_RenderCopy(rendu, messageScore, NULL, &messageRect);
    
    SDL_DestroyTexture(messageScore);
    SDL_FreeSurface(surfaceMessage);
}

/**
 * \brief Crée un bouton.
 *
 * Cette fonction crée un bouton.
 *
 * \param renderer Le renderer SDL pour l'affichage.
 * \param text Texte du bouton.
 * \param x Position horizontale du bouton.
 * \param y Position verticale du bouton.
 * \param width Largeur du bouton.
 * \param height Hauteur du bouton.
 * \param couleur Couleur du bouton.
 * \return Le bouton créé.
 */

Button createButton(SDL_Renderer* renderer, TTF_Font *font, const char* text, int x, int y, int width, int height, Couleur_t couleur) {
    Button button;
    button.rect.x = x;
    button.rect.y = y;
    button.rect.w = width;
    button.rect.h = height;
    
    // Créer la surface de texte
    SDL_Color color = {couleur.red, couleur.green, couleur.blue}; 
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    
    
    if (!surface) {
        printf("Erreur lors de la création de la surface de texte : %s\n", TTF_GetError());
        exit(1);
    }
    
    // Créer la texture à partir de la surface
    button.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!button.texture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(surface);

    return button;
}

/**
 * \brief Affiche un bouton.
 *
 * \param renderer Rendu SDL.
 * \param button Bouton à afficher.
 */
void drawButton(SDL_Renderer* renderer, Button button) {
    SDL_RenderCopy(renderer, button.texture, NULL, &button.rect);
}

/**
 * \brief Vérifie si un bouton est cliqué.
 *
 * \param event Événement SDL.
 * \param button Bouton à vérifier.
 * \return 1 si le bouton est cliqué, 0 sinon.
 */
int clickButton(SDL_Event event, Button button){
    return (event.button.x > button.rect.x && event.button.x < (button.rect.x + BUTTON_WIDTH) && event.button.y > button.rect.y && event.button.y < (button.rect.y + BUTTON_HEIGHT));
}

/**
 * \brief Vérifie si la souris est sur un bouton.
 *
 * \param button Bouton à vérifier.
 * \return 1 si la souris est sur le bouton, 0 sinon.
 */
int mouseOnButton(Button button){
    int mouse_x, mouse_y;

    SDL_GetMouseState(&mouse_x, &mouse_y);

    return (mouse_x > button.rect.x && mouse_x < (button.rect.x + BUTTON_WIDTH) && mouse_y > button.rect.y && mouse_y < (button.rect.y + BUTTON_HEIGHT));
}

/**
 * \brief Initialise les boutons.
 *
 * \param jouerButton Bouton pour jouer.
 * \param difficulteButton Bouton pour choisir la difficulté.
 * \param facileButton Bouton pour choisir la difficulté facile.
 * \param normalButton Bouton pour choisir la difficulté normale.
 * \param difficileButton Bouton pour choisir la difficulté difficile.
 * \param accueilButton Bouton pour revenir à l'accueil.
 * \param gameoverButton Bouton pour afficher le game over.
 * \param retryButton Bouton pour recommencer.
 * \param rendu Rendu SDL.
 */
void initBoutons(TTF_Font *font, Button *jouerButton, Button *difficulteButton, Button *facileButton, Button *normalButton, Button *difficileButton, Button *accueilButton, Button *retryButton, Button *reprendreButton, SDL_Renderer *rendu) {
    printf("2222\n");
    *jouerButton = createButton(rendu, font, "JOUER", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 +70, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);
    *difficulteButton = createButton(rendu, font, "DIFFICULTE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_HEIGHT +70, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    *facileButton = createButton(rendu, font,"FACILE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT, VERT);
    *normalButton = createButton(rendu, font, "NORMAL", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 1, BUTTON_WIDTH, BUTTON_HEIGHT, ORANGE);
    *difficileButton = createButton(rendu, font, "DIFFICILE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 0, BUTTON_WIDTH, BUTTON_HEIGHT, ROUGE);
    *accueilButton = createButton(rendu, font, "ACCUEIL", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 3 + 100, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    *retryButton = createButton(rendu, font, "RETRY", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_HEIGHT +70, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);
    *reprendreButton = createButton(rendu, font, "REPRENDRE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);
}

/**
 * \brief Gère le menu principal.
 *
 * \param rendu Rendu SDL.
 * \param jouerButton Bouton pour jouer.
 * \param difficulteButton Bouton pour choisir la difficulté.
 * \param difficileButton Bouton pour choisir la difficulté difficile.
 */
void menuPrincipal(SDL_Renderer *rendu, TTF_Font *font, Button jouerButton, Button difficulteButton){
    SDL_RenderClear(rendu);
    affichageAccueilImage(rendu);

    // Dessiner les boutons
    drawButton(rendu, jouerButton);
    drawButton(rendu, difficulteButton);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_ADD);


    if(mouseOnButton(jouerButton)){   
        /* I want to fill the rect with transparent color */
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &jouerButton.rect);
    }

    if(mouseOnButton(difficulteButton)){
        /* I want to fill the rect with transparent color */
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &difficulteButton.rect);
    }

    afficherMessage(rendu, font, "Appuyer sur la touche 'ESC' pour faire PAUSE", (WINDOWS_WIDTH) / 2 -410, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 +270, 800);

    SDL_RenderPresent(rendu);
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);
}


/**
 * \brief Gère le menu difficulte.
 *
 * \param rendu Renderer.
 * \param facileButton Bouton facile.
 * \param normalButton Bouton normal.
 * \param difficileButton Bouton difficile.
 */
void menuDifficulte(SDL_Renderer *rendu, Button facileButton, Button normalButton, Button difficileButton, Button accueilButton, char *difficulte, TTF_Font *font){
    SDL_RenderClear(rendu);
    affichageDifficulteImage(rendu);
    afficherMessage(rendu, font, difficulte, (WINDOWS_WIDTH/2)-700/2, 100, 700);

    
    
    drawButton(rendu, difficileButton);
    drawButton(rendu, normalButton);
    drawButton(rendu, facileButton);
    drawButton(rendu, accueilButton);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_ADD);

    // Dessiner les boutons
    if(mouseOnButton(facileButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &facileButton.rect);
    }
    if(mouseOnButton(normalButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &normalButton.rect);
    }
    if(mouseOnButton(accueilButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &accueilButton.rect);
    }
    if(mouseOnButton(difficileButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &difficileButton.rect);
    }
    
    
    SDL_RenderPresent(rendu);
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);
}

void MenuPause(SDL_Renderer *rendu, Button reprendreButton, Button retryButton, Button accueilButton){
    SDL_RenderClear(rendu);
    affichagePauseImage(rendu);

    drawButton(rendu, reprendreButton);
    drawButton(rendu, retryButton);
    drawButton(rendu, accueilButton);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_ADD);

    // Dessiner les boutons
    if(mouseOnButton(reprendreButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &reprendreButton.rect);
    }
    if(mouseOnButton(retryButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &retryButton.rect);
    }
    if(mouseOnButton(accueilButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &accueilButton.rect);
    }
    
    SDL_RenderPresent(rendu);
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);
}

/**
 * \brief Gère le menu game over.
 *
 * \param rendu Renderer.
 * \param gameoverButton Bouton game over.
 * \param retryButton Bouton retry.
 * \param vague Vague actuelle.
 * \param duree_partie Durée de la partie.
 * \param nb_kill Nombre de kills.
 */
int menuGameOver( SDL_Renderer *rendu, TTF_Font *font, Button retryButton, Button accueilButton, int vague, int duree_partie, int nb_kill){
    SDL_RenderClear(rendu);
    affichageGameOverImage(rendu);

    drawButton(rendu, retryButton);
    drawButton(rendu, accueilButton);


    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_ADD);

    if(mouseOnButton(retryButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &retryButton.rect);
    }

    if(mouseOnButton(accueilButton)){
        SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
        SDL_RenderFillRect(rendu, &accueilButton.rect);
    }
    
    
    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);
    SDL_Color blanc = {255, 255, 255};
    char texte[512];
    sprintf(texte, "Vague : %d | Survie : %d sec | Kills : %d", vague, duree_partie/1000, (nb_kill + 5 * (vague-1)));

    // Allouer dynamiquement la mémoire pour la chaîne de caractères
    char* texte_dyn = malloc(strlen(texte) + 1);
    if (texte_dyn == NULL) {
        // Gestion de l'erreur de l'allocation mémoire
        printf("Erreur d'allocation de mémoire\n");
        return (EXIT_FAILURE);
    }
    strcpy(texte_dyn, texte); // Copier la chaîne dans l'espace alloué dynamiquement

    SDL_Surface* surfaceMessage;
    
    surfaceMessage = TTF_RenderText_Solid(font, texte_dyn, blanc);
    free(texte_dyn); // Libérer la mémoire allouée dynamiquement

    SDL_Texture* messageScore = SDL_CreateTextureFromSurface(rendu, surfaceMessage);

    SDL_Rect messageRect;

    messageRect.x = WINDOWS_WIDTH/2-240;
    messageRect.y = WINDOWS_HEIGHT/2;
    messageRect.w = 500;
    messageRect.h = 50;

    SDL_RenderCopy(rendu, messageScore, NULL, &messageRect);
    SDL_RenderPresent(rendu);
    
    SDL_DestroyTexture(messageScore);
    SDL_FreeSurface(surfaceMessage);
}

void destructionBoutons(Button *bouton, ...){
    va_list args;
    va_start(args, bouton);

    Button *current = bouton;
    while (current != NULL) {
        SDL_DestroyTexture(current->texture);
        free(current);
        current = va_arg(args, Button*);
    }

    va_end(args);
    
}