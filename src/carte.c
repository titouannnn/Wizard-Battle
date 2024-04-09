#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "fonctions.h"
#include "carte.h"

void chargerCarte(char * fichier, int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], int nb){
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
                    fscanf(fp, "%d ",&tab[nb][y][x]);
                }
            }
    }
    fclose(fp);
}

void chargerColisions(int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT], int nb){
    for(int y = 0; y < NB_TILE_WIDTH; y++){
        for(int x = 0; x < NB_TILE_HEIGHT; x++){
            //ici on consiède que les tiles de colisions sont les tiles 0 et 2
            if(tab[nb][y][x] == 6 || tab[nb][y][x] == 7){
                tabColision[y][x] = 1;
            }
            else{
                tabColision[y][x] = 0;
            }
        }
    }
}
/*
int afficherCarte(int tab[NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu,
    SDL_Texture *tabTex[5],
    SDL_Rect * camera,
    positionJoueur_t position,
    colision_t *colision,
    SDL_Texture *tilemap)    {

    int x;
    int y;
    SDL_Rect * dest = malloc(sizeof(SDL_Rect));
    SDL_Rect * origin = malloc(sizeof(SDL_Rect));
    dest->h = TILE_HEIGHT; 
    dest->w = TILE_WIDTH; 
  
    origin->h = TILE_HEIGHT;
    origin->w = TILE_WIDTH;


    
    for (y=0;y<NB_TILE_WIDTH;y++)
    {
        for (x=0;x<NB_TILE_HEIGHT;x++)
        {
    
            if(tab[y][x] >= 0 && tab[y][x] <= 4){
                switch (tab[y][x])
                {
                case 0:
                    origin->h = TILE_HEIGHT;
                    origin->w = TILE_WIDTH;
                    origin->x = TILE_HEIGHT*0;
                    origin->y = 0;
                    break;

                case 1:
                    origin->h = TILE_HEIGHT;
                    origin->w = TILE_WIDTH;
                    origin->x = TILE_HEIGHT*1 ;
                    origin->y = 0;
                    break;
                case 2:
                    origin->h = TILE_HEIGHT;
                    origin->w = TILE_WIDTH;
                    origin->x = TILE_HEIGHT*2;
                    origin->y = 0;        
                    break;
                
                case 3:
                    origin->h = TILE_HEIGHT;
                    origin->w = TILE_WIDTH;
                    origin->x = TILE_HEIGHT*3;
                    origin->y = 0;
                    break;

                case 4:
                    origin->h = TILE_HEIGHT;
                    origin->w = TILE_WIDTH;
                    origin->x = TILE_HEIGHT*4;
                    origin->y = 0;
                    break;
                
                default:
                    origin->h = TILE_HEIGHT;
                    origin->w = TILE_WIDTH;
                    origin->x = TILE_HEIGHT*0;
                    origin->y = 0;
                    break;
                }
                dest->x = x*TILE_HEIGHT - camera->x;
                dest->y = y*TILE_WIDTH - camera->y;          
                //SDL_RenderCopy(rendu, tabTex[tab[y][x]], NULL, dest);
                SDL_RenderCopy(rendu,tilemap,origin,dest);
            }   

        }
    }
    
    free(dest);
} */

//test avec tilemap 2

int afficherCarte(int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu,
    SDL_Texture *tabTex[5],
    SDL_Rect * camera,
    positionJoueur_t position,
    colision_t *colision,
    SDL_Texture *tilemap,
    int nb)    {

    int x;
    int y;
    int case_y;
    int case_x;
    int val = 0;

    SDL_Rect * dest = malloc(sizeof(SDL_Rect));
    SDL_Rect * origin = malloc(sizeof(SDL_Rect));
    dest->h = TILE_HEIGHT; 
    dest->w = TILE_WIDTH; 
  
    origin->h = TILE_HEIGHT;
    origin->w = TILE_WIDTH;


    
    for (y=0;y<NB_TILE_WIDTH;y++)
    {
        for (x=0;x<NB_TILE_HEIGHT;x++)
        {
            /* Les cases vont de 0 à 63 */

            if(nb == 0){
                /* couche ou on affiche l'herbe*/
                        val = tab[nb][y][x];
                        case_y = val / 8;
                        case_x = val % 8;

                        origin->h = TILE_HEIGHT;
                        origin->w = TILE_WIDTH;
                        origin->y = TILE_HEIGHT * case_y;
                        origin->x = TILE_WIDTH * case_x;

                        dest->x = x * TILE_HEIGHT - camera->x;
                        dest->y = y * TILE_WIDTH - camera->y;

                        SDL_RenderCopy(rendu, tilemap, origin, dest);
            }
            else if(nb == 1)
            {
                /* couche structures*/
                /*
                * index des structures
                * 1 : banc (face)
                */
                val = tab[nb][y][x];
                if(val == 1)
                {
                    printf("dans la boucle\n");
                    origin->h = TILE_HEIGHT*4;
                    origin->w = TILE_WIDTH*4;
                    origin->y = TILE_HEIGHT * 0;
                    origin->x = TILE_WIDTH * 10;
                    dest->x = x * TILE_HEIGHT - camera->x;
                    dest->y = y * TILE_WIDTH - camera->y;
                    SDL_RenderCopy(rendu, tilemap, origin, dest);
                }

            }

        }
        
    }
    free(dest);
    free(origin);
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

