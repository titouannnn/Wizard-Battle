#include "game.h"

/* Fonction qui calcule si le projectile passé en parametre est rentré en collision avec soit le joueur soit un ennemi et enleve des points de vie en conséquence */
void collisionProjEntite(projectiles_t *projectile, ennemi_t *ennemi, SDL_Rect *playerRect, SDL_Rect *cameraRect, joueur_t *joueur);



int main() {
    /* 
    * Déclaration des tableaux pour la carte et les colisions
    * Ici tableau de 3 dimensions car il y a plusieurs couches pour la carte (herbe et structures)
    */
    int tilemap[2][NB_TILE_WIDTH][NB_TILE_WIDTH];
    int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT];
    int direction = DROITE;
    int menu = 1;
    
    /* Initialisation des variables, encapsulées dans trois fonctions pour plus de clarté*/
    initFonctions(tilemap, tabColision, &fenetre, &rendu, &cameraRect, &position, &colision, &pers_destination, &temps_ancien, &barTextureVieMax, &barTextureVie, &healthBar);
    initEnnemis(projJoueur, projEnnemi, &joueur, ennemi, rendu);
    initBoutons(&jouerButton, &difficulteButton, &facileButton, &normalButton, &difficileButton, &accueilButton, &gameoverButton, &retryButton, rendu);
    chargerTextures(rendu);
 

    // Création de deux rectangles : un pour la barre de vie fixe et l'autre pour celle qui baisse (vie restante)
    SDL_Rect healthBarMaxRect = { healthBar.x, healthBar.y, healthBar.maxWidth, HEALTH_BAR_HEIGHT };
    SDL_Rect *healthBarRect = malloc(sizeof(SDL_Rect));
    *healthBarRect = (SDL_Rect){ healthBar.x, healthBar.y, healthBar.width, HEALTH_BAR_HEIGHT };

 

   
    
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            // Pour fermer la fenêtre 
            switch(event.type){
                case SDL_QUIT:
                    isRunning = 0;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if(menu == 1 && clickButton(event, jouerButton)){
                        menu = 0;
                    }
                    
                    if(menu == 1 && clickButton(event, difficulteButton)){
                        menu = 2;
                    }

                    if(menu == 2 && clickButton(event, accueilButton)){
                        menu = 1;
                    }

                    if(menu == 3 && clickButton(event, retryButton)){
                        menu = 1;
                        joueur.pv = 100;
                    }
                    else{

                        int mouse_x, mouse_y;
                        SDL_GetMouseState(&mouse_x, &mouse_y);
            
                        /* Initialisation du tableau de projectiles appartenant au joueur */
                        projJoueur[projNbJoueur].initProj(&projJoueur[projNbJoueur], cameraRect->x + pers_destination.x, cameraRect->y + pers_destination.y, mouse_x, mouse_y, PROJ_JOUEUR, cameraRect);
                        projNbJoueur++;
                        if (projNbJoueur == MAX_PROJ){
                            projNbJoueur = 0;
                        }
                    }
                    
                    break;
                    

            }
        }

        /*
        * MENU =
        * 0 - Jeu
        * 1 - Page d'accueil
        * 2 - Choix de la difficulté
        * 3 - Game Over
        */
   
        if(menu != 0)  /* Si la valeur menu n'est pas censé renvoyer sur le jeu directement*/
        {
            menuFonc( menu, rendu, jouerButton, difficulteButton, difficileButton, accueilButton, gameoverButton, retryButton, facileButton, normalButton);
        }

        else if (menu == 0)
        /* On entre dans le jeu */
        {
            /* On efface le rendu précédent*/
            SDL_RenderClear(rendu);

            // Récupération de l'état du clavier : 
            const Uint8 *clavier = SDL_GetKeyboardState(NULL);
            
            updateHealthBar(&healthBar, healthBarRect, joueur.pv, joueur.pvMax);
            updateCamera(&pers_destination,rendu, cameraRect,tilemap, colision, tabColision, position);
            action(clavier, &pers_destination, colision, &direction);
            
            /* Rendu des enemis et des projectiles*/
            for (int i = 0; i < NB_ENNEMI; i++){
                Uint32 temp_vivant = SDL_GetTicks() - ennemi[i].delta;
                ennemi[i].updateEnnemi(&ennemi[i], cameraRect, &pers_destination, tabColision, projEnnemi, &projNbEnnemi, temp_vivant);
            }
            
            if (projNbEnnemi == MAX_PROJ){
                projNbEnnemi = 0;
            }
                        

            for (int i = 0; i < projNbEnnemi; i++){
                for(int j = 0; j < NB_ENNEMI; j++){
                    collisionProjEntite(&projEnnemi[i], &ennemi[j], &pers_destination, cameraRect, &joueur);
                }
                projEnnemi[i].updateProj(&projEnnemi[i], cameraRect, tabColision);
                projEnnemi[i].renderProj(rendu, &projEnnemi[i], frame);
                
            }
            for (int i = 0; i < projNbJoueur; i++){
                for(int j = 0; j < NB_ENNEMI; j++){
                    collisionProjEntite(&projJoueur[i], &ennemi[j], &pers_destination, cameraRect, &joueur);
                }
                projJoueur[i].updateProj(&projJoueur[i], cameraRect, tabColision);
                projJoueur[i].renderProj(rendu, &projJoueur[i], frame);
                
            }
            renderEnemies(ennemi, rendu, frame);

            actualisationSprite(4, frame, DIM_SPRITE_PLAYER_X, DIM_SPRITE_PLAYER_Y, &direction, &pers_source, &pers_destination, rendu);

            /* La Barre de vie est rendue en dernière pour être affichée devant les autres éléments */
            SDL_RenderCopy(rendu, barTextureVieMax, NULL, &healthBarMaxRect);
            SDL_RenderCopy(rendu, barTextureVie, NULL, healthBarRect);

            SDL_RenderPresent(rendu);

            /* Game Over*/
            if(joueur.pv <= 0){
                menu = 3;
            }
        }
    }
    free(healthBarRect);
    return fin(fenetre, rendu);
}

/* Fonction qui calcule si le projectile passé en parametre est rentré en collision avec soit le joueur soit un ennemi et enleve des points de vie en conséquence 
* La fonction est déclarée ici pour des problèmes de dépendances circulaires
*/
void collisionProjEntite(projectiles_t *projectile, ennemi_t *ennemi, SDL_Rect *playerRect, SDL_Rect *cameraRect, joueur_t *joueur){
    if (projectile->id == PROJ_JOUEUR && projectile->collision != 1){
        if (((projectile->x +25 + projectile->w > ennemi->x) && (projectile->x + 25 < ennemi->x + ennemi->rect.w)) && ((projectile->y + projectile->h/2 > ennemi->y) && (projectile->y + 50 < ennemi->y + ennemi->rect.h))){
            ennemi->pv -= ennemi->attaque;
            projectile->collision = 1;
        }
    }
    else if (projectile->id == PROJ_ENNEMI && projectile->collision != 1){
        if (projectile->x + projectile->w/2 > cameraRect->x + playerRect->x && projectile->x < cameraRect->x + playerRect->x + playerRect->w && projectile->y + projectile->h/2 > playerRect->y + cameraRect->y && projectile->y < playerRect->y + playerRect->h + cameraRect->y){
            joueur->pv -= joueur->attaque;
            projectile->collision = 1;
        }
    }

}