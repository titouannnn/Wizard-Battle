#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "fonctions.h"
#include "carte.h"

/**
 * @brief Initialise la position du joueur sur la carte.
 * 
 * @return positionJoueur_t* Pointeur vers la structure de position du joueur.
 */
positionJoueur_t * initPositionJoueur(){
    positionJoueur_t * position = malloc(sizeof(positionJoueur_t));
    position->case_hg.casx = 0;
    position->case_hg.casy = 0;
    position->case_hd.casx = 1;
    position->case_hd.casy = 0;
    position->case_bg.casx = 0;
    position->case_bg.casy = 1;
    position->case_bd.casx = 1;
    position->case_bd.casy = 1;
    return position;
}

/**
 * @brief Initialise la structure de colision.
 * 
 * @return colision_t* Pointeur vers la structure de colision.
 */
colision_t * initColision(){
    colision_t * colision = malloc(sizeof(colision_t));
    colision->haut = 0;
    colision->bas = 0;
    colision->gauche = 0;
    colision->droite = 0;
    return colision;
}


/**
 * @brief Charge une carte depuis un fichier.
 * 
 * @param fichier Nom du fichier à charger.
 * @param tab Tableau de la carte.
 * @param nb Numéro de la couche de la carte.
 */
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

/**
 * @brief Charge les colisions depuis un tableau de carte.
 * 
 * @param tab Tableau de la carte.
 * @param tabColision Tableau de colisions.
 * @param nb Numéro de la couche de la carte.
 */
void chargerColisions(int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT], int nb){
    for(int y = 0; y < NB_TILE_WIDTH; y++){
        for(int x = 0; x < NB_TILE_HEIGHT; x++){
            //ici on consiède que les tiles de colisions sont les tiles 0 et 2
            if(tab[nb][y][x] == 2 || tab[nb][y][x] == 1 || tab[nb][y][x] == 3 || tab[nb][y][x] == 4 ){
                tabColision[y][x] = 1;
            }
            else{
                tabColision[y][x] = 0;
            }
        }
    }
}

/**
 * @brief Affiche la carte.
 * 
 * @param tab Tableau de la carte.
 * @param rendu Pointeur vers le rendu.
 * @param camera Pointeur vers la caméra.
 * @param position Structure de position du joueur.
 * @param colision Structure de colision.
 * @param tilemap Texture de la carte.
 * @param nb Numéro de la couche de la carte.
 * @return int Retourne 0 si tout s'est bien passé.
 */

int afficherCarte(int tab[2][NB_TILE_WIDTH][NB_TILE_HEIGHT], 
    SDL_Renderer * rendu,
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
                * 2 : tonneau
                * 3 : Rocher
                * 4 : pillier 
                */
                val = tab[nb][y][x];
                if(val == 1)
                {
                    origin->h = TILE_HEIGHT/2;
                    origin->w = TILE_WIDTH;

                    origin->y = 38;
                    origin->x = 584;

                    dest->h = TILE_HEIGHT;
                    dest->w = TILE_WIDTH*2;

                    dest->x = x * TILE_HEIGHT - camera->x;
                    dest->y = y * TILE_WIDTH - camera->y;
                    SDL_RenderCopy(rendu, tilemap, origin, dest);
                }
                else if(val == 2)
                {
                    origin->h = TILE_HEIGHT/2;
                    origin->w = TILE_WIDTH/2;

                    origin->y = 306;
                    origin->x = 324;

                    dest->h = TILE_HEIGHT*1.2;
                    dest->w = TILE_WIDTH*1.2;

                    dest->x = x * TILE_HEIGHT - camera->x + TILE_WIDTH/6;
                    dest->y = y * TILE_WIDTH - camera->y;
                    SDL_RenderCopy(rendu, tilemap, origin, dest);
                }
                else if(val == 3)
                {
                    origin->h = TILE_HEIGHT/1.5;
                    origin->w = TILE_WIDTH;

                    origin->y = 850;
                    origin->x = 0;

                    dest->h = TILE_HEIGHT;
                    dest->w = TILE_WIDTH*1.5;

                    dest->x = x * TILE_HEIGHT - camera->x;
                    dest->y = y * TILE_WIDTH - camera->y;
                    SDL_RenderCopy(rendu, tilemap, origin, dest);
                }
                else if(val == 4)
                {
                    origin->h = TILE_HEIGHT;
                    origin->w = TILE_WIDTH/2;

                    origin->y = 10;
                    origin->x = 450;

                    dest->h = TILE_HEIGHT*2;
                    dest->w = TILE_WIDTH;

                    dest->x = x * TILE_HEIGHT - camera->x + TILE_WIDTH/6;
                    dest->y = y * TILE_WIDTH - camera->y;
                    SDL_RenderCopy(rendu, tilemap, origin, dest);
                }
                

            }

        }
        
    }
    free(dest);
    free(origin);
    return 0;
}
    


/**
 * @brief Vérifie les collisions entre le joueur et les tuiles de la carte.
 * 
 * Cette fonction vérifie si le joueur est en collision avec une tuile sur la carte. 
 * Elle met à jour les valeurs de la structure de collision en fonction de la position du joueur.
 * 
 * @param position La position actuelle du joueur sur la carte.
 * @param colision Pointeur vers la structure de collision à mettre à jour.
 * @param tabTilesColision Tableau 2D représentant les tuiles de collision de la carte.
 */

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

