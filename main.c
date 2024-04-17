#include "game.h"
#include "src/global.h"

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
    initFonctions(tilemap, tabColision, &fenetre, &rendu, &cameraRect, &position, &colision, &pers_destination, &temps_ancien, &barTextureVieMax, &barTextureVie, &healthBar, &barTextureManaMax, &barTextureMana, &manaBar);
    initEnnemis(projJoueur, projEnnemi, &joueur, ennemi, rendu);

    TTF_Font *arial = TTF_OpenFont("police/arial.ttf", 24);

    initBoutons(arial, &jouerButton, &difficulteButton, &facileButton, &normalButton, &difficileButton, &accueilButton, &gameoverButton, &retryButton, &reprendreButton, rendu);
    chargerTextures(rendu);
    
 
    
    // Création de deux rectangles : un pour la barre de vie fixe et l'autre pour celle qui baisse (vie restante)
    SDL_Rect healthBarMaxRect = { healthBar.x, healthBar.y, healthBar.maxWidth, BAR_HEIGHT };
    SDL_Rect *healthBarRect = malloc(sizeof(SDL_Rect));
    *healthBarRect = (SDL_Rect){ healthBar.x, healthBar.y, healthBar.width, BAR_HEIGHT };
    
    // Création de deux rectangles : un pour la barre de vie fixe et l'autre pour celle qui baisse (vie restante)
    SDL_Rect manaBarMaxRect = { manaBar.x, manaBar.y, manaBar.maxWidth, BAR_HEIGHT };
    SDL_Rect *manaBarRect = malloc(sizeof(SDL_Rect));
    *manaBarRect = (SDL_Rect){ manaBar.x, manaBar.y, manaBar.width, BAR_HEIGHT };

    
    /*
    * MENU =
    * 0 - Jeu
    * 1 - Page d'accueil
    * 2 - Choix de la difficulté
    * 3 - Game Over
    * 4 - Pause
    * */
    int mx, my;
    vague = 1;
    nb_ennemis = 5;
    nb_kill = 0;
    ennemis_initialises = 0;
    projNbEnnemi = 0; 
    projNbJoueur = 0;
    isRunning = 1; 
    frame = 0; 
    delta_temps = 0;
    char texte[52];
    strcpy(texte, "Difficulte choisie : Normale");
    
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            // Pour fermer la fenêtre 
            switch(event.type){
                case SDL_QUIT:
                    isRunning = 0;
                    break;
                case SDL_MOUSEMOTION:
                    mx = event.motion.x;
                    my = event.motion.y;
                    break;
                
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                        menu = 4;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(menu == 1 && clickButton(event, jouerButton)){
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        gain_mana = SDL_GetTicks();
                        duree_partie = SDL_GetTicks();
                        menu = 0;
                    }
                    
                    if(menu == 1 && clickButton(event, difficulteButton)){
                        menu = 2;
                    }

                    if(menu == 2 && clickButton(event, facileButton)){
                        coefDifficulte = 0.7;
                        nb_ennemis = 5;
                        strcpy(texte, "Difficulte choisie : Facile");
                    }
                    if (menu == 2 && clickButton(event, normalButton)){
                        coefDifficulte = 1;
                        nb_ennemis = 7;
                        strcpy(texte, "Difficulte choisie : Normale");
                    }
                    if (menu == 2 && clickButton(event, difficileButton)){
                        coefDifficulte = 1.3;
                        nb_ennemis = 10;
                        strcpy(texte, "Difficulte choisie : Difficile");
                    }
                    if(menu == 2 && clickButton(event, accueilButton)){
                        menu = 1;
                    }

                    if(menu == 4 && clickButton(event, retryButton)){
                        joueur.pv = 100;
                        joueur.mana = 100;

                        vague = 1;
                        ennemis_initialises = 0;
                        nb_kill = 0;
                        joueur.x = 400;
                        joueur.y = 400;
                        projNbEnnemi = 0; 
                        projNbJoueur = 0;
                        frame = 0; 
                        delta_temps = 0;
                        
                        if (coefDifficulte == 0.7){
                            nb_ennemis = 5;
                        }
                        else if (coefDifficulte == 1){
                            nb_ennemis = 7;
                        }
                        else if (coefDifficulte == 1.3){
                            nb_ennemis = 10;
                        }
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        menu = 0;

                        gain_mana = SDL_GetTicks();
                        duree_partie = SDL_GetTicks();
                        
                    }
                    if(menu == 4 && clickButton(event, accueilButton)){
                        joueur.pv = 100;
                        joueur.mana = 100;

                        vague = 1;
                        ennemis_initialises = 0;
                        nb_kill = 0;
                        joueur.x = 400;
                        joueur.y = 400;
                        projNbEnnemi = 0; 
                        projNbJoueur = 0;
                        frame = 0; 
                        delta_temps = 0;
                        
                        if (coefDifficulte == 0.7){
                            nb_ennemis = 5;
                        }
                        else if (coefDifficulte == 1){
                            nb_ennemis = 7;
                        }
                        else if (coefDifficulte == 1.3){
                            nb_ennemis = 10;
                        }

                        menu = 1;
                        
                    }

                    if (menu == 4 && clickButton(event, reprendreButton)){
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        menu = 0;
                    }
                    if(menu == 3 && clickButton(event, retryButton)){
                        joueur.pv = 100;
                        joueur.mana = 100;

                        vague = 1;
                        ennemis_initialises = 0;
                        nb_kill = 0;
                        joueur.x = 400;
                        joueur.y = 400;
                        projNbEnnemi = 0; 
                        projNbJoueur = 0;
                        frame = 0; 
                        delta_temps = 0;
                        
                        if (coefDifficulte == 0.7){
                            nb_ennemis = 5;
                        }
                        else if (coefDifficulte == 1){
                            nb_ennemis = 7;
                        }
                        else if (coefDifficulte == 1.3){
                            nb_ennemis = 10;
                        }
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        menu = 0;

                        gain_mana = SDL_GetTicks();
                        duree_partie = SDL_GetTicks();
                        
                    }
                    if(menu == 3 && clickButton(event, accueilButton)){
                        joueur.pv = 100;
                        joueur.mana = 100;

                        vague = 1;
                        ennemis_initialises = 0;
                        nb_kill = 0;
                        joueur.x = 400;
                        joueur.y = 400;
                        projNbEnnemi = 0; 
                        projNbJoueur = 0;
                        frame = 0; 
                        delta_temps = 0;
                        
                        if (coefDifficulte == 0.7){
                            nb_ennemis = 5;
                        }
                        else if (coefDifficulte == 1){
                            nb_ennemis = 7;
                        }
                        else if (coefDifficulte == 1.3){
                            nb_ennemis = 10;
                        }

                        menu = 1;
                    }
                    else{
                        /* Lancer un projectile si on appuie sur le click gauche, que le jeu à débuté et que le joueur a assez de mana */
                        if (menu == 0 && event.button.button == SDL_BUTTON_LEFT && joueur.mana >= 10){
                                
                            int mouse_x, mouse_y;
                            SDL_GetMouseState(&mouse_x, &mouse_y);
                            joueur.mana -= 5;
                            /* Initialisation du tableau de projectiles appartenant au joueur */
                            projJoueur[projNbJoueur].initProj(&projJoueur[projNbJoueur], cameraRect->x + pers_destination.x, cameraRect->y + pers_destination.y, mouse_x, mouse_y, PROJ_JOUEUR, cameraRect);
                            projNbJoueur++;
                            if (projNbJoueur == MAX_PROJ){
                                projNbJoueur = 0;
                            }
                        }
                    }
                    
                    break;
                    

            }
        }
        
        if(menu == 1){
            
            menuPrincipal(rendu, arial, jouerButton, difficulteButton);
        }
        else if(menu == 2){
            menuDifficulte(rendu, facileButton, normalButton, difficileButton, accueilButton, texte, arial);
        }
        else if(menu == 3){
            menuGameOver(rendu, arial, gameoverButton, retryButton, vague, duree_partie, nb_kill); 
        }
        else if(menu == 4){
            MenuPause(rendu, reprendreButton, retryButton, accueilButton);
        }

        else if (menu == 0)
        /* On entre dans le jeu */
        {   
            printf("mx et my : %d %d\n", mx, my);
            //calcul du temps
            temps_actuel = SDL_GetTicks();
            delta_temps += temps_actuel - temps_ancien;
            temps_ancien = temps_actuel;

            if (temps_actuel - gain_mana >= 500){
                joueur.mana += 10;
                if (joueur.mana > joueur.manaMax){
                    joueur.mana = joueur.manaMax;
                }
                gain_mana = temps_actuel;
            }

            if(delta_temps >= 100){ // ms entre les images du sprite
                delta_temps = 0;
                frame = (frame + 1) % 6;
            }

            

            /* On efface le rendu précédent*/
            SDL_RenderClear(rendu);

            // Récupération de l'état du clavier : 
            const Uint8 *clavier = SDL_GetKeyboardState(NULL);
            
            updateBar(&healthBar, healthBarRect, joueur.pv, joueur.pvMax);
            updateBar(&manaBar, manaBarRect, joueur.mana, joueur.manaMax);


            updateCamera(&pers_destination,rendu, cameraRect,tilemap, colision, tabColision, position);
            action(clavier, &pers_destination, colision, &direction);
            

            

            if (!ennemis_initialises){
                duree_vague = SDL_GetTicks();
                initEnnemisVague(ennemi, nb_ennemis);
                joueur.mana = 100;
                joueur.pv = 100;
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

            if (projNbEnnemi > MAX_PROJ - 1){
                projNbEnnemi = 0;
            }
            
                   
            
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
            actualisationSprite(4, frame, &direction, &pers_source, &pers_destination, rendu);
            
           
            SDL_RenderCopy(rendu, barTextureVieMax, NULL, &healthBarMaxRect);
            SDL_RenderCopy(rendu, barTextureVie, NULL, healthBarRect);

            SDL_RenderCopy(rendu, barTextureManaMax, NULL, &manaBarMaxRect);
            SDL_RenderCopy(rendu, barTextureMana, NULL, manaBarRect);

            afficherAim(rendu, mx, my);

            SDL_RenderPresent(rendu);



            /* Game Over*/
            if(joueur.pv <= 0){
                duree_partie = SDL_GetTicks() - duree_partie;
                SDL_SetRelativeMouseMode(SDL_FALSE);
                menu = 3;
            }
        }
    }
    for (int i = 0; i < 50; i++){
        free(ennemi[i].initEnnemi);
        free(ennemi[i].updateEnnemi);
        free(ennemi[i].renderEnnemi);
        free(ennemi[i].renderVecteur);
    }
    free(healthBarRect);
    free(manaBarRect);
    return fin(fenetre, rendu, arial);
}

/* Fonction qui calcule si le projectile passé en parametre est rentré en collision avec soit le joueur soit un ennemi et enleve des points de vie en conséquence 
* La fonction est déclarée ici pour des problèmes de dépendances circulaires
*/
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
