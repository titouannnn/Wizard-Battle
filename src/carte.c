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
  

    for (y=0;y<NB_TILE_WIDTH;y++)
{
    for (x=0;x<NB_TILE_HEIGHT;x++)
    {
        
        // Si la tuile actuelle est une des tuiles du joueur, ne pas la rendre
        if (x == position.case_hd.casx && y == position.case_hd.casy ||
            x == position.case_hg.casx && y == position.case_hg.casy ||
            x == position.case_bd.casx && y == position.case_bd.casy ||
            x == position.case_bg.casx && y == position.case_bg.casy) {
            
            continue;
        }

        if(tab[y][x] >= 0 && tab[y][x] <= 4){
            dest->x = x*TILE_HEIGT - camera->x;
            dest->y = y*TILE_WIDTH - camera->y;
            SDL_RenderCopy(rendu, tabTex[tab[y][x]], NULL, dest);
        }    
        

    }
}
    free(dest);
}