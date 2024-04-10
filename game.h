#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/projectile.h"
#include "src/entite.h"
#include "src/fonctions.h"
#include "src/carte.h"
#include "src/menu.h"
#include "src/barre.h"





// Définition des couleurs avec les directives de préprocesseur
#define JAUNE ((Couleur_t){255, 255, 0})
#define BLEU ((Couleur_t){0, 0, 255})
#define ROUGE ((Couleur_t){255, 0, 0})
#define VERT ((Couleur_t){0, 255, 0})
#define NOIR ((Couleur_t){0, 0, 0})
#define BLANC ((Couleur_t){255, 255, 255})
#define ORANGE ((Couleur_t){255, 165, 0})

