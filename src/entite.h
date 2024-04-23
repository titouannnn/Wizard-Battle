/**
 * \file entite.h
 * \brief Ce fichier contient les structures et les prototypes des fonctions pour la gestion des entités.
 * 
 * Les entités sont les personnages du jeu, c'est-à-dire le joueur et les ennemis.
 * 
 */
#ifndef ENTITE_H
#define ENTITE_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "projectile.h"
#include "fonctions.h"
#include "carte.h"

#define DIM_SPRITE_ENNEMI_X 128
#define DIM_SPRITE_ENNEMI_Y 184

#define CHAMP_DETECTION 500
#define MAX_PROJ_ENNEMI 2

#define NB_ENNEMI 50

typedef struct ennemi_s ennemi_t;
typedef struct joueur_s joueur_t;

/**
 * \struct point_s
 * \brief Structure représentant un point.
 * 
 * Un point est défini par ses coordonnées x et y.
*/
typedef struct point_s{
    int x;  /**< Coordonnée x du point */
    int y;  /**< Coordonnée y du point */
} point_t;


/**
 * \struct joueur_s
 * \brief Structure représentant le joueur.
 * 
 * Le joueur est défini par ses coordonnées x et y, son nombre de points de vie, son nombre de points de mana, son attaque et sa vitesse.
*/
struct joueur_s {
    int id; /**< identifiant du joueur */
    int x;  /**< Coordonnée x du joueur */
    int y;  /**< Coordonnée y du joueur */
    int mana;   /**< Points de mana du joueur */
    int manaMax;    /**< Points de mana maximum du joueur */
    int pv; /**< Points de vie du joueur */
    int pvMax;  /**< Points de vie maximum du joueur */
    int attaque;    /**< Attaque du joueur */
    int vitesse;    /**< Vitesse du joueur */
};

/**
 * \struct ennemi_s
 * \brief Structure représentant un ennemi.
 * 
 * Un ennemi est défini par ses coordonnées x et y, son nombre de points de vie, son nombre de points de vie maximum, son attaque, sa vitesse, sa portée de détection, son état de mort, son rectangle de collision, son rectangle de sprite, son vecteur de déplacement, sa durée d'apparition et ses fonctions d'initialisation, de mise à jour et d'affichage.
*/
struct ennemi_s {
    int id; /**< identifiant de l'ennemi */
    float x;    /**< Coordonnée x de l'ennemi */
    float y;    /**< Coordonnée y de l'ennemi */
    
    float vx;   /**< Vecteur de déplacement en x */
    float vy;   /**< Vecteur de déplacement en y */

    int pv; /**< Points de vie de l'ennemi */
    int pvMax;  /**< Points de vie maximum de l'ennemi */
    int attaque;    /**< Attaque de l'ennemi */
    float vitesse;  /**< Vitesse de l'ennemi */
    int detection;  /**< Portée de détection de l'ennemi */

    int gauche; /**< Booléen indiquant si l'ennemi est tourné vers la gauche */
    int droite; /**< Booléen indiquant si l'ennemi est tourné vers la droite */

    int mort;   /**< Booléen indiquant si l'ennemi est mort */

    Uint32 delta;  /**< Durée d'apparition de l'ennemi */

    SDL_Rect rect;  /**< Rectangle de collision de l'ennemi */
    SDL_Rect sprite;    /**< Rectangle de sprite de l'ennemi */

    void (*initEnnemi)(ennemi_t *ennemi, float x, float y, int id, int pvMax, int attaque); /** < fonction d'initialisation d'un ennemi */
    void (*updateEnnemi)(ennemi_t * ennemi, SDL_Rect * cameraRect, SDL_Rect * playerRect, int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT], projectiles_t projEnnemi[MAX_PROJ], int *projNbEnnemi, int temp_vivant);  /** < fonction de mise à jour d'un ennemi */
    void (*renderEnnemi)(SDL_Renderer * rendu, ennemi_t * ennemi, int frame); /** < fonction d'affichage d'un ennemi */
    void (*renderVecteur)(SDL_Renderer * rendu, ennemi_t * ennemi, SDL_Rect * playerRect);  /** < fonction d'affichage du vecteur de déplacement d'un ennemi */
};

void initTabEnnemi(ennemi_t tabEnnemi[NB_ENNEMI]);
void initialiserJoueur(joueur_t * joueur);
void ennemi_creer(ennemi_t * ennemi);
void initEnnemi(ennemi_t * ennemi, float x, float y, int id, int pvMax, int attaque);
void initEnnemisVague(ennemi_t tabEnnemi[NB_ENNEMI], int nb_ennemis, int *ennemi_initialises, int *joueurMana, int *joueurManaMax, int *joueurPv, int *joueurPvMax, int *duree_vague);
void updateEnnemi(ennemi_t * ennemi, SDL_Rect * cameraRect, SDL_Rect * playerRect, int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT], projectiles_t projEnnemi[MAX_PROJ], int *projNbEnnemi, int temp_vivant);
void renderEnnemi(SDL_Renderer *rendu, ennemi_t *ennemi, int frame);
void renderVecteur(SDL_Renderer *rendu, ennemi_t *ennemi, SDL_Rect * playerRect);
void DessinerPixel(int x, int y, SDL_Renderer *rendu);
void DessinerLigneEnnemiJoueur(point_t A, point_t B, SDL_Renderer *rendu);
void DessinerLigneEnnemiVu(point_t A, point_t B, SDL_Renderer *rendu);
void chargerTexturesEnnemi(SDL_Renderer *rendu);
void renderEnemies(ennemi_t* ennemi, SDL_Renderer* rendu, int frame);



void initEnnemis(
    projectiles_t projJoueur[MAX_PROJ],
    projectiles_t projEnnemi[MAX_PROJ],
    joueur_t *joueur,
    ennemi_t ennemi[NB_ENNEMI],
    SDL_Renderer *rendu
);

#endif // ENTITE_H
