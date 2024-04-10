#include "projectile.h"

SDL_Surface *projectile_temp_surface;

SDL_Texture *lancer_joueur_tex;
SDL_Texture *lancer_ennemi_tex;

SDL_Texture *impact_joueur_tex;
SDL_Texture *impact_ennemi_tex;

/* Fonction pour calculer l'angle en radians entre deux points */
/* sert à calculer l'angle du sprite projectile */
double calculerAngle(int x1, int y1, int x2, int y2) {
    return atan2(y2 - y1, x2 - x1);
}


void initTabProj(projectiles_t proj[MAX_PROJ])
{
    for (int i = 0; i < MAX_PROJ; i++){
        projectile_creer(&proj[i]);
        projectile_creer(&proj[i]);
    }
}

void chargerTexturesProj(SDL_Renderer *rendu){

    projectile_temp_surface = SDL_LoadBMP("images/projectiles/lancer.bmp");
    lancer_joueur_tex = SDL_CreateTextureFromSurface(rendu, projectile_temp_surface);
    SDL_FreeSurface(projectile_temp_surface);
    if(lancer_joueur_tex == NULL){
        printf("Erreur de chargement de l'image 'lancer.bmp': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'lancer.bmp' réussi\n");

    projectile_temp_surface = SDL_LoadBMP("images/projectiles/lancer_ennemi.bmp");
    lancer_ennemi_tex = SDL_CreateTextureFromSurface(rendu, projectile_temp_surface);
    SDL_FreeSurface(projectile_temp_surface);
    if(lancer_ennemi_tex == NULL){
        printf("Erreur de chargement de l'image 'lancer_ennemi.bmp': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'lancer_ennemi.bmp' réussi\n");

    projectile_temp_surface = SDL_LoadBMP("images/projectiles/impact.bmp");
    impact_joueur_tex = SDL_CreateTextureFromSurface(rendu, projectile_temp_surface);
    SDL_FreeSurface(projectile_temp_surface);
    if(impact_joueur_tex == NULL){
        printf("Erreur de chargement de l'image 'impact.bmp': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'impact.bmp' réussi\n");

    projectile_temp_surface = SDL_LoadBMP("images/projectiles/impact_ennemi.bmp");
    impact_ennemi_tex = SDL_CreateTextureFromSurface(rendu, projectile_temp_surface);
    SDL_FreeSurface(projectile_temp_surface);
    if(impact_ennemi_tex == NULL){
        printf("Erreur de chargement de l'image 'impact_ennemi.bmp': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'impact_ennemi.bmp' réussi\n");
}

void actualisationSpriteProj(projectiles_t *projectile, int nb_sprite, int frame, int largeur, int hauteur, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu){
    SDL_Texture *texSprite;
    if (projectile->id == PROJ_JOUEUR && projectile->collision == 0){
        texSprite = lancer_joueur_tex;
    }
    else if (projectile->id == PROJ_ENNEMI && projectile->collision == 0){
        texSprite = lancer_ennemi_tex;
    }
    else if (projectile->id == PROJ_JOUEUR && projectile->collision == 1){
        texSprite = impact_joueur_tex;
    }
    else if (projectile->id == PROJ_ENNEMI && projectile->collision == 1){
        texSprite = impact_ennemi_tex;
    }
    src->x = (frame % nb_sprite)*largeur;
    src->y = 0;
    src->w = largeur;
    src->h = hauteur;

    // On affiche les sprites  :
    SDL_RenderCopyEx(rendu, texSprite, src, dst, projectile->angle * 180 / M_PI, NULL, SDL_FLIP_NONE);
}

void projectile_creer(projectiles_t *projectile){
    projectile->initProj = initProj;
    projectile->verifCollisionProj = verifCollisionProj;
    projectile->updateProj = updateProj;
    projectile->renderProj = renderProj;
}

void initProj(projectiles_t *projectile, float px, float py, float mx, float my, int id, SDL_Rect *cameraRect){

    projectile->id = id;
    projectile->animation_impact = 0;

    projectile->x = px -50;
    projectile->y = py +50;

    projectile->angle = calculerAngle(px + 50, py + 50, mx + cameraRect->x, my + cameraRect->y);

    int d1 = mx + cameraRect->x - projectile->x - 100;
    int d2 = my + cameraRect->y - projectile->y - 100;

    projectile->vx = d1 / sqrt(d1 * d1 + d2 * d2);
    projectile->vy = d2 / sqrt(d1 * d1 + d2 * d2);

    projectile->w = 100;
    projectile->h = 100;
    projectile->collision = 0;
    projectile->vitesse = 10;
}

void verifCollisionProj(projectiles_t *projectile, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]){
    int x = projectile->x / TILE_WIDTH;
    int y = projectile->y / TILE_HEIGHT;
    if(tabTilesColision[y][x] == 1){
        projectile->collision = 1;
    }

}

void updateProj(projectiles_t *projectile, SDL_Rect *cameraRect, int tabTilesColision[NB_TILE_WIDTH][NB_TILE_HEIGHT]){
    verifCollisionProj(projectile, tabTilesColision);
    if(projectile->collision == 1){
        return;
    }
    else{
        projectile->x += projectile->vx * projectile->vitesse;
        projectile->y += projectile->vy * projectile->vitesse;
        projectile->rect.x = projectile->x - cameraRect->x;
        projectile->rect.y = projectile->y - cameraRect->y;
        projectile->rect.w = 170;
        projectile->rect.h = 170;
    }
    
}

void renderProj(SDL_Renderer *rendu, projectiles_t *projectile, int frame){
    if (projectile->collision == 1) projectile->animation_impact++;
    if (projectile->collision == 1 && projectile->animation_impact < 6){
        actualisationSpriteProj(projectile, 6, frame, DIM_SPRITE_LANCER_X, DIM_SPRITE_LANCER_Y, &projectile->sprite, &projectile->rect, rendu);
        return;
    }
    else if (projectile->collision == 1 && projectile->animation_impact >= 4){
        return;
    }
    else{
        /* Regler la taille du projectile beaucoup trop gros */
        actualisationSpriteProj(projectile, 4, frame, DIM_SPRITE_LANCER_X, DIM_SPRITE_LANCER_Y, &projectile->sprite, &projectile->rect, rendu);
        
    }
    
}







