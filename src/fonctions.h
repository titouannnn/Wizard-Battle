#ifndef FONCTIONS_H
#define FONCTIONS_H


#define WINDOWS_WIDTH 1200
#define WINDOWS_HEIGHT 800

#define TAILLE_SPRITE_PLAYER 180
#define DIM_SPRITE_PLAYER 160
#define FPS 60
#define DELAI 1000 / FPS
#define VITESSE_JOUEUR 3.5

#define HAUT 0
#define BAS 1
#define DROITE 2
#define GAUCHE 3

#define LARGEUR_FOND 2560
#define HAUTEUR_FOND 1440

typedef struct {
    int x;
    int y;
} Camera_t;


int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu);
void chargerTextures(SDL_Renderer *rendu);
int fin(SDL_Window *fenetre, SDL_Renderer *rendu);
void actualisationSprite(int nb_sprite, int frame, int largeur, int hauteur, int direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu);
void action(const Uint8 *clavier, SDL_Rect *pers_destination, SDL_Rect *pers_source, int frame, int DIM_SPRITE, SDL_Renderer *rendu);
void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect);
void updateCamera(SDL_Rect *pers_destination, SDL_Renderer *rendu, SDL_Rect * cameraRect);


#endif
