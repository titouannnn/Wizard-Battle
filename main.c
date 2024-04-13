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
    
    /* Initialisation des variables, encapsulées dans trois fonctions pour plus de clarté*/
    initFonctions(tilemap, tabColision, &fenetre, &rendu, &cameraRect, &position, &colision, &pers_destination, &temps_ancien, &barTextureVieMax, &barTextureVie, &healthBar);
    initEnnemis(projJoueur, projEnnemi, &joueur, ennemi, rendu);
    initBoutons(&jouerButton, &difficulteButton, &facileButton, &normalButton, &difficileButton, &accueilButton, &gameoverButton, &retryButton, rendu);

    
    /* A supprimer, inutile*/
    SDL_Texture *tabTile[5];
    chargerTextures(rendu, tabTile);

    // Initialisation de la structure barre de vie
    
    

    // Création de deux rectangles : un pour la barre de vie fixe et l'autre pour celle qui baisse (vie restante)
    SDL_Rect healthBarMaxRect = { healthBar.x, healthBar.y, healthBar.maxWidth, BAR_HEIGHT };
    SDL_Rect *healthBarRect = malloc(sizeof(SDL_Rect));
    *healthBarRect = (SDL_Rect){ healthBar.x, healthBar.y, healthBar.width, BAR_HEIGHT };



    
    /*
    * MENU =
    * 0 - Jeu
    * 1 - Page d'accueil
    * 2 - Choix de la difficulté
    * 3 - Game Over
    * */

    int menu = 1;
    vague = 1;
    nb_ennemis = 5;
    nb_kill = 0;
    ennemis_initialises = 0;
    
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
                        duree_partie = SDL_GetTicks();
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
        
        if(menu == 1){
            menuPrincipal(rendu, jouerButton, difficulteButton);
        }
        else if(menu == 2){
            menuDifficulte(rendu, facileButton, normalButton, difficileButton, accueilButton);
        }
        else if(menu == 3){
            menuGameOver(rendu, gameoverButton, retryButton, vague, duree_partie, nb_kill); 
        }

        else if (menu == 0){
            
            //calcul du temps
            temps_actuel = SDL_GetTicks();
            delta_temps += temps_actuel - temps_ancien;
            temps_ancien = temps_actuel;

            if(delta_temps >= 100){ // ms entre les images du sprite
                delta_temps = 0;
                frame = (frame + 1) % 6;
            }
            SDL_RenderClear(rendu);

            // Récupération de l'état du clavier : 
            const Uint8 *clavier = SDL_GetKeyboardState(NULL);
            
            updateBar(&healthBar, healthBarRect, joueur.pv, joueur.pvMax);

            if(joueur.pv <= 0){
                duree_partie = SDL_GetTicks() - duree_partie;
                menu = 3;
            }

            updateCamera(&pers_destination,rendu, cameraRect,tilemap, tabTile, colision, tabColision, position);
            action(clavier, &pers_destination, colision, &direction);
            updateCamera(&pers_destination,rendu, cameraRect,tilemap, tabTile, colision, tabColision, position);

            

            if (!ennemis_initialises){
                duree_vague = SDL_GetTicks();
                initEnnemisVague(ennemi, nb_ennemis);
                ennemis_initialises = 1;
            }

            /* Update de la position des ennemis */
            for (int i = 0; i < nb_ennemis; i++){
                Uint32 temp_vivant = SDL_GetTicks() - ennemi[i].delta;
                if (ennemi[i].pv <= 0 && ennemi[i].mort == 0){
                    nb_kill++;
                }
                ennemi[i].updateEnnemi(&ennemi[i], cameraRect, &pers_destination, tabColision, projEnnemi, &projNbEnnemi, temp_vivant);
                
            }            

            if (projNbEnnemi == MAX_PROJ){
                projNbEnnemi = 0;
            }
            
            action(clavier, &pers_destination, colision, &direction);            
            
            /* Update et rendu des projectile ennemis */
            for (int i = 0; i < projNbEnnemi; i++){
                for(int j = 0; j < nb_ennemis; j++){
                    collisionProjEntite(&projEnnemi[i], &ennemi[j], &pers_destination, cameraRect, &joueur);
                }
                projEnnemi[i].updateProj(&projEnnemi[i], cameraRect, tabColision);
                projEnnemi[i].renderProj(rendu, &projEnnemi[i], frame);
                
            }

            /* Update et rendu des projectiles du joueur */
            for (int i = 0; i < projNbJoueur; i++){
                for(int j = 0; j < nb_ennemis; j++){
                    collisionProjEntite(&projJoueur[i], &ennemi[j], &pers_destination, cameraRect, &joueur);
                    
                }
                projJoueur[i].updateProj(&projJoueur[i], cameraRect, tabColision);
                projJoueur[i].renderProj(rendu, &projJoueur[i], frame);
                
            }

            /* Rendu des ennemis */
            for (int i = 0; i < nb_ennemis; i++){
                ennemi[i].renderEnnemi(rendu, &ennemi[i], frame);
            }

            /* Si on a fait suffisamment de kill on passe à la manche suivante */
            if (nb_kill >= nb_ennemis) {
                nextVague(&vague, &nb_ennemis, &nb_kill, &ennemis_initialises); 
            }

            if (SDL_GetTicks() - duree_vague < 2000){
                afficherVague(rendu, vague, SDL_GetTicks() - duree_vague);
            }

            /* Rendu du joueur */
            actualisationSprite(4, frame, DIM_SPRITE_PLAYER_X, DIM_SPRITE_PLAYER_Y, &direction, &pers_source, &pers_destination, rendu);

           
            SDL_RenderCopy(rendu, barTextureVieMax, NULL, &healthBarMaxRect);
            SDL_RenderCopy(rendu, barTextureVie, NULL, healthBarRect);

            SDL_RenderPresent(rendu);


            SDL_Delay(DELAI);
        }
    }
    free(healthBarRect);
    return fin(fenetre, rendu);
}

/* Fonction qui calcule si le projectile passé en parametre est rentré en collision avec soit le joueur soit un ennemi et enleve des points de vie en conséquence */
void collisionProjEntite(projectiles_t *projectile, ennemi_t *ennemi, SDL_Rect *playerRect, SDL_Rect *cameraRect, joueur_t *joueur){
    if (projectile->id == PROJ_JOUEUR && projectile->collision != 1){
        if (((projectile->x +25 + projectile->w > ennemi->x) && (projectile->x + 25 < ennemi->x + ennemi->rect.w)) && ((projectile->y + projectile->h/2 > ennemi->y) && (projectile->y + 50 < ennemi->y + ennemi->rect.h))){
            ennemi->pv -= joueur->attaque;
            projectile->collision = 1;
            
        }
    }
    else if (projectile->id == PROJ_ENNEMI && projectile->collision != 1){
        if (projectile->x + projectile->w/2 > cameraRect->x + playerRect->x && projectile->x < cameraRect->x + playerRect->x + playerRect->w && projectile->y + projectile->h/2 > playerRect->y + cameraRect->y && projectile->y < playerRect->y + playerRect->h + cameraRect->y){
            joueur->pv -= ennemi->attaque;
            projectile->collision = 1;
            
        }
    }

}