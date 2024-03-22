#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "fonctions.h"
#include "carte.h"

void chargerCarte(char * fichier, int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT]){
    FILE * fp;
    int x;
    int y;
    fp = fopen(fichier,"rb");

    if(fp == NULL){
        printf("Erreur lors de l'ouverture du fichier %s\n",fichier);
    }
    else{ 
        for (y=0;y<NB_TILE_WIDTH;y++)
            {
                for (x=0;x<NB_TILE_HEIGHT;x++)
                {
                    fscanf(fp, "%d ",&tab[y][x]);
                }
            }
    }
    fclose(fp);
}

int afficherCarte(int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu,
    SDL_Texture *tabTex[5],
    SDL_Rect * camera,
    positionJoueur_t position)    {
    int x;
    int y;
    SDL_Rect * dest = malloc(sizeof(SDL_Rect));
    dest->h = TILE_HEIGT;
    dest->w = TILE_WIDTH;

    int playerTileX;
    int playerTileY;    
    
    position.haut_gauche.caseJoueur.casx = position.haut_gauche.posx /80;
    position.haut_gauche.caseJoueur.casy = position.haut_gauche.posy /80; 

    printf("case haut gauche : %d %d\n", position.haut_gauche.caseJoueur.casx, position.haut_gauche.caseJoueur.casy);

    position.haut_droit.caseJoueur.casx = position.haut_droit.posx / 40;
    position.haut_droit.caseJoueur.casy = position.haut_droit.posy / 40;

    position.bas_gauche.caseJoueur.casx = position.bas_gauche.posx / 40;
    position.bas_gauche.caseJoueur.casy = position.bas_gauche.posy / 40; 

    position.bas_droit.caseJoueur.casx = position.bas_droit.posx / 40;
    position.bas_droit.caseJoueur.casy = position.bas_droit.posy / 40;


    for (y=0;y<NB_TILE_WIDTH;y++)
{
    for (x=0;x<NB_TILE_HEIGHT;x++)
    {
        /*
        // Si la tuile actuelle est une des tuiles du joueur, ne pas la rendre
        if ((x == position.haut_gauche.caseJoueur.casx && y == position.haut_gauche.caseJoueur.casy) ||
            (x == position.haut_droit.caseJoueur.casx && y == position.haut_droit.caseJoueur.casy) ||
            (x == position.bas_gauche.caseJoueur.casx && y == position.bas_gauche.caseJoueur.casy) ||
            (x == position.bas_droit.caseJoueur.casx && y == position.bas_droit.caseJoueur.casy)) {
            continue;
        }*/

        if(tab[y][x] >= 0 && tab[y][x] <= 4){
            dest->x = x*TILE_HEIGT - camera->x;
            dest->y = y*TILE_WIDTH - camera->y;
            SDL_RenderCopy(rendu, tabTex[tab[y][x]], NULL, dest);
        }    
        //affiche la case sur laquelle sont les coordonnées du point haut gauche

        if (x == position.haut_gauche.caseJoueur.casx && y == position.haut_gauche.caseJoueur.casy) {
            printf("case haut gauche : %d %d\n", x, y);
        }

    }
}
    free(dest);
}