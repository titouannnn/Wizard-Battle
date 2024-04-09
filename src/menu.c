#include "./menu.h"

// Fonction pour créer un bouton
Button createButton(SDL_Renderer* renderer, const char* text, int x, int y, int width, int height, Couleur_t couleur) {
    Button button;
    button.rect.x = x;
    button.rect.y = y;
    button.rect.w = width;
    button.rect.h = height;

    // Charger la police
    TTF_Font* font = TTF_OpenFont("police/arial.ttf", 30);
    if (!font) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
        exit(1);
    }

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
    TTF_CloseFont(font);

    return button;
}

// Fonction pour dessiner un bouton
void drawButton(SDL_Renderer* renderer, Button button) {
    SDL_RenderCopy(renderer, button.texture, NULL, &button.rect);
}

/* Renvoie 1 si la souris est sur le bouton en paramètre, 0 sinon */
int clickButton(SDL_Event event, Button button){
    return (event.button.x > button.rect.x && event.button.x < (button.rect.x + BUTTON_WIDTH) && event.button.y > button.rect.y && event.button.y < (button.rect.y + BUTTON_HEIGHT));
}

int mouseOnButton(Button button){
    int mouse_x, mouse_y;

    SDL_GetMouseState(&mouse_x, &mouse_y);

    return (mouse_x > button.rect.x && mouse_x < (button.rect.x + BUTTON_WIDTH) && mouse_y > button.rect.y && mouse_y < (button.rect.y + BUTTON_HEIGHT));
}


