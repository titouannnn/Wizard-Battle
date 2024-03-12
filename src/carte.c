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

void afficherCarte(int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu, SDL_Texture * tile, SDL_Rect * camera)
    {
    int x;
    int y;
    SDL_Rect * dest = malloc(sizeof(SDL_Rect));
    dest->h = TILE_HEIGT;
    dest->w = TILE_WIDTH;
    for (y=0;y<NB_TILE_WIDTH;y++)
    {
        for (x=0;x<NB_TILE_HEIGHT;x++)
        {
            if(tab[y][x] == 1){
            dest->x = x*TILE_HEIGT - camera->x;
            dest->y = y*TILE_WIDTH - camera->y;
            SDL_RenderCopy(rendu, tile, NULL, dest);
            }    
        }
    }
    free(dest);
}