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

void chargerColisions(int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT], int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]){
    for(int y = 0; y < NB_TILE_WIDTH; y++){
        for(int x = 0; x < NB_TILE_HEIGHT; x++){
            //ici on consiède que les tiles de colisions sont les tiles 0 et 2
            if(tab[y][x] == 0 || tab[y][x] == 2){
                tabColision[y][x] = 1;
            }
            else{
                tabColision[y][x] = 0;
            }
        }
    }
}

int afficherCarte(int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu,
    SDL_Texture *tabTex[5],
    SDL_Rect * camera,
    positionJoueur_t position,
    colision_t *colision)    {
    int x;
    int y;
    SDL_Rect * dest = malloc(sizeof(SDL_Rect));
    dest->h = TILE_HEIGT;
    dest->w = TILE_WIDTH;
  

    for (y=0;y<NB_TILE_WIDTH;y++)
    {
        for (x=0;x<NB_TILE_HEIGHT;x++)
        {
    
            if(tab[y][x] >= 0 && tab[y][x] <= 4){
                dest->x = x*TILE_HEIGT - camera->x;
                dest->y = y*TILE_WIDTH - camera->y;
                SDL_RenderCopy(rendu, tabTex[tab[y][x]], NULL, dest);
            }   

        }
    }
    free(dest);
}



void colisions(positionJoueur_t position, colision_t * colision, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]){
    
        
        if(tabTilesColision[position.case_hg.casy][position.case_hg.casx] == 1 || tabTilesColision[position.case_hd.casy][position.case_hd.casx] == 1){
            colision->haut = 1;
        }
        else{
            colision->haut = 0;
        }
        if(tabTilesColision[position.case_bg.casy][position.case_bg.casx] == 1 || tabTilesColision[position.case_bd.casy][position.case_bd.casx] == 1){
            colision->bas = 1;
        }
        else{
            colision->bas = 0;
        }
        if(tabTilesColision[position.case_hg.casy][position.case_hg.casx] == 1 || tabTilesColision[position.case_bg.casy][position.case_bg.casx] == 1){
            colision->gauche = 1;
        }
        else{
            colision->gauche = 0;
        }
        if(tabTilesColision[position.case_hd.casy][position.case_hd.casx] == 1 || tabTilesColision[position.case_bd.casy][position.case_bd.casx] == 1){
            colision->droite = 1;
        }
        else{
            colision->droite = 0;
        }
    
    //printf("colision : h %d b %d g %d d %d\n",colision->haut,colision->bas,colision->gauche,colision->droite);
    
    
}