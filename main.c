#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdlib.h>

#define HAUT = 0;
#define BAS = 1;
#define DROITE = 2;
#define GAUCHE = 3;

int fenetre_hauteur = 1200;
int fenetre_largeur = 800;
const int FPS =         60;
const int TAILLE_SPRITE = 360;
const int DIM_SPRITE = 160;
int vrai = 1;
int direction = 0;
const int DELAI = 6000/FPS;

SDL_Renderer *rendu;
SDL_Surface *temp_surface;
SDL_Window *fenetre;

SDL_Texture *run_front_tex;
SDL_Surface *run_front_srf;

SDL_Texture *run_back_tex;
SDL_Surface *run_back_srf;

SDL_Texture *run_right_tex;
SDL_Surface *run_right_srf;

SDL_Texture *run_left_tex;
SDL_Surface *run_left_srf;

SDL_Rect pers_source, pers_destination;

int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu) {
    // Initialisation de la bibliothèque SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Problème d'initialisation de la bibliothèque SDL : %s\n", SDL_GetError());
        return 0;
    }

    // Création de la fenêtre et du rendu
    *fenetre = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, fenetre_hauteur, fenetre_largeur, SDL_WINDOW_OPENGL);
    *rendu = SDL_CreateRenderer(*fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(*rendu, 255, 255, 255, 255);

    if (*fenetre != NULL && *rendu != NULL) {
        return 1;
    } else {
        printf("Problème de création de la fenêtre : %s\n", SDL_GetError());
        return 0;
    }
}

void chargerTextures() {
    temp_surface = SDL_LoadBMP("images/run_front.bmp");
    run_front_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_front_tex == NULL){
        printf("Erreur de chargement de l'image 'run_front': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_front' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_back.bmp");
    run_back_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_back_tex == NULL){
        printf("Erreur de chargement de l'image 'run_back': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_back' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_right.bmp");
    run_right_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_right_tex == NULL){
        printf("Erreur de chargement de l'image 'run_right': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_right' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_left.bmp");
    run_left_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_left_tex == NULL){
        printf("Erreur de chargement de l'image 'run_left': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_left' réussi\n");
}

int fin(SDL_Window *fenetre, SDL_Renderer *rendu){
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}

void actualisationSprite(int nb_sprite, int frame, int largeur, int hauteur, int direction, SDL_Rect *src, SDL_Rect *dst){
    SDL_Texture *texSprite;
    if (direction == 0) { // front
        texSprite = run_front_tex;
    } else if (direction == 1) { // back
        texSprite = run_back_tex;
    } else if (direction == 2) { // right
        texSprite = run_right_tex;
    } else if (direction == 3) { // left
        texSprite = run_left_tex;
    }

    src->x = (frame % nb_sprite)*largeur;
    src->y = 0;
    src->w = largeur;
    src->h = hauteur;
    dst->w = TAILLE_SPRITE;
    dst->h = TAILLE_SPRITE;

    // On affiche les sprites  :
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, texSprite, src, dst);
    SDL_RenderPresent(rendu);
}

void action(const Uint8 *clavier, SDL_Rect *pers_destination, SDL_Rect *pers_source, int frame, int DIM_SPRITE) {
    int direction = 0;

    if (clavier[SDL_SCANCODE_W]) {
        pers_destination->y -= 50;
        direction = 1;
    }
    if (clavier[SDL_SCANCODE_S]) {
        pers_destination->y += 50;
        direction = 0;
    }
    if (clavier[SDL_SCANCODE_A]) {
        pers_destination->x -= 50;
        direction = 3;
    }
    if (clavier[SDL_SCANCODE_D]) {
        pers_destination->x += 50;
        direction = 2;
    }
    actualisationSprite(6, frame, DIM_SPRITE, DIM_SPRITE, direction, pers_source, pers_destination);
}


int main() {
    initialisation(&fenetre, &rendu);
    chargerTextures();

    pers_destination.y = fenetre_largeur/ 2 - TAILLE_SPRITE / 2;
    pers_destination.x = fenetre_hauteur/ 2 - TAILLE_SPRITE / 2;

    // Gestion des événements SDL
    SDL_Event event;
    int frame = 0;
    while (vrai) {
        while (SDL_PollEvent(&event)) {
            // Pour fermer la fenêtre 
            if (event.type == SDL_QUIT) {
                vrai = 0; 
            } 
        }
        //récupération de l'état du clavier : 
        const Uint8 *clavier = SDL_GetKeyboardState(NULL);
        frame = (frame + 1) % 6;
        
        action(clavier, &pers_destination, &pers_source, frame, DIM_SPRITE);

        SDL_Delay(DELAI);
    }
    return fin(fenetre, rendu);
}
