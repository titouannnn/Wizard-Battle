#ifndef FONCTIONS_H
#define FONCTIONS_H

#define WINDOWS_WIDTH 800
#define WINDOWS_HEIGHT 1200

#define TAILLE_SPRITE_PLAYER 360
#define DIM_SPRITE_PLAYER 160
#define FPS 90
#define DELAI 6000/FPS

#define HAUT 0
#define BAS 1
#define DROITE 2
#define GAUCHE 3

int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu);
void chargerTextures();
int fin(SDL_Window *fenetre, SDL_Renderer *rendu);
void actualisationSprite(int nb_sprite, int frame, int largeur, int hauteur, int direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu);
void action(const Uint8 *clavier, SDL_Rect *pers_destination, SDL_Rect *pers_source, int frame, int DIM_SPRITE, SDL_Renderer *rendu);

#endif 