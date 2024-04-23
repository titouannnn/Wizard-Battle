/**
 * @file main.c
 * @brief Fichier principal du jeu contenant la boucle principale.
 * 
 *  Ce fichier contient la boucle principale du jeu.
 */
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

    TTF_Font *arial = TTF_OpenFont("police/wizard.ttf", 24);

    initBoutons(arial, &jouerButton, &difficulteButton, &facileButton, &normalButton, &difficileButton, &accueilButton, &retryButton, &reprendreButton, rendu);
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
    strcpy(texte, "Difficulte choisie : Normal");
    isRunning = 1; 
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
                    if (event.key.keysym.sym == SDLK_ESCAPE && menu != 1 && menu != 2 && menu != 3){
                        menu = 4;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (menu == 1){
                        if(clickButton(event, jouerButton)){
                        
                            gain_mana = SDL_GetTicks();
                            duree_partie = SDL_GetTicks();
                            menu = 0;
                        }
                        if(clickButton(event, difficulteButton)){
                            menu = 2;
                        }
                    } else if (menu == 2){
                        if(clickButton(event, facileButton)){
                            coefDifficulte = 0.7;
                            nb_ennemis = 5;
                            strcpy(texte, "Difficulte choisie : Facile");
                        }
                        else if (clickButton(event, normalButton)){
                            coefDifficulte = 1;
                            nb_ennemis = 7;
                            strcpy(texte, "Difficulte choisie : Normal");
                        }
                        else if (clickButton(event, difficileButton)){
                            coefDifficulte = 1.3;
                            nb_ennemis = 10;
                            strcpy(texte, "Difficulte choisie : Difficile");
                        }
                        else if(clickButton(event, accueilButton)){
                            renitialiserStats(&joueur.pv, &joueur.mana, &joueur.x, &joueur.y, &vague, &ennemis_initialises, &nb_ennemis, &nb_kill, &projNbJoueur, &projNbEnnemi, &frame, &delta_temps, &coefDifficulte, &gain_mana, &duree_partie);
                            menu = 1;
                        }
                    } else if (menu == 4){
                        if(clickButton(event, retryButton) || clickButton(event, accueilButton)){
                            renitialiserStats(&joueur.pv, &joueur.mana, &joueur.x, &joueur.y, &vague, &ennemis_initialises, &nb_ennemis, &nb_kill, &projNbJoueur, &projNbEnnemi, &frame, &delta_temps, &coefDifficulte, &gain_mana, &duree_partie);
                            menu = clickButton(event, retryButton) ? 0 : 1;
                        } else if (clickButton(event, reprendreButton)){
                            SDL_SetRelativeMouseMode(SDL_TRUE);
                            menu = 0;
                        }
                    } else if (menu == 3){
                        if(clickButton(event, retryButton) || clickButton(event, accueilButton)){
                            renitialiserStats(&joueur.pv, &joueur.mana, &joueur.x, &joueur.y, &vague, &ennemis_initialises, &nb_ennemis, &nb_kill, &projNbJoueur, &projNbEnnemi, &frame, &delta_temps, &coefDifficulte, &gain_mana, &duree_partie);
                            menu = clickButton(event, retryButton) ? 0 : 1;
                        }
                    } else if (menu == 0){
                        if (event.button.button == SDL_BUTTON_LEFT && joueur.mana >= 10){
                            joueur.mana -= 5;
                            projJoueur[projNbJoueur].initProj(&projJoueur[projNbJoueur], cameraRect->x + pers_destination.x, cameraRect->y + pers_destination.y, mx, my, PROJ_JOUEUR, cameraRect);
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
            SDL_SetRelativeMouseMode(SDL_FALSE);
            menuPrincipal(rendu, arial, jouerButton, difficulteButton);
        }
        else if(menu == 2){
            SDL_SetRelativeMouseMode(SDL_FALSE);
            menuDifficulte(rendu, facileButton, normalButton, difficileButton, accueilButton, texte, arial);
        }
        else if(menu == 3){
            SDL_SetRelativeMouseMode(SDL_FALSE);
            menuGameOver(rendu, arial, retryButton, accueilButton , vague, duree_partie, nb_kill); 
        }
        else if(menu == 4){
            SDL_SetRelativeMouseMode(SDL_FALSE);
            MenuPause(rendu, reprendreButton, retryButton, accueilButton);
        }
        else if (menu == 0)
        /* On entre dans le jeu */
        {   
            SDL_SetRelativeMouseMode(SDL_FALSE);
            /* Recalcule le temps et effectue la regeneration du mana */
            calculTemps(&temps_actuel, &delta_temps, &temps_ancien, &gain_mana, &joueur.mana, &joueur.manaMax, &frame);
            /* On efface le rendu précédent*/
            SDL_RenderClear(rendu);

            // Récupération de l'état du clavier : 
            const Uint8 *clavier = SDL_GetKeyboardState(NULL);
            
            updateBar(&healthBar, healthBarRect, joueur.pv, joueur.pvMax);
            updateBar(&manaBar, manaBarRect, joueur.mana, joueur.manaMax);

            updateCamera(&pers_destination,rendu, cameraRect,tilemap, colision, tabColision, position);
            action(clavier, &pers_destination, colision, &direction);
            
            initEnnemisVague(ennemi, nb_ennemis, &ennemis_initialises, &joueur.mana, &joueur.manaMax, &joueur.pv, &joueur.pvMax, &duree_vague);

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

            /* Rendu du joueur */
            actualisationSprite(4, frame, &direction, &pers_source, &pers_destination, rendu);
            
           
            SDL_RenderCopy(rendu, barTextureVieMax, NULL, &healthBarMaxRect);
            SDL_RenderCopy(rendu, barTextureVie, NULL, healthBarRect);

            SDL_RenderCopy(rendu, barTextureManaMax, NULL, &manaBarMaxRect);
            SDL_RenderCopy(rendu, barTextureMana, NULL, manaBarRect);

            if (SDL_GetTicks() - duree_vague < 2000){
                afficherVague(rendu, arial, vague, SDL_GetTicks() - duree_vague);
            }
            afficherNbKill(rendu, arial, nb_kill, nb_ennemis);
            afficherTemps(rendu, arial, (SDL_GetTicks() - duree_partie)/1000);

            afficherAim(rendu, mx, my);

            SDL_RenderPresent(rendu);

            /* Verification Game Over */
            gameOver(&joueur.pv, &menu, &duree_partie);
        }
    }
    /* Libération de la mémoire */
    return fin(fenetre, rendu, arial);
}

/**
 * @brief Fonction qui calcule si le projectile passé en parametre est rentré en collision avec soit le joueur soit un ennemi et enleve des points de vie en conséquence
 * 
 * @param projectile Pointeur sur le projectile
 * @param ennemi Pointeur sur l'ennemi
 * @param playerRect Pointeur sur le rectangle du joueur
 * @param cameraRect Pointeur sur le rectangle de la camera
 * @param joueur Pointeur sur le joueur
 * 
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
