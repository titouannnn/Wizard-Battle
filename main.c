#include "game.h"

SDL_Renderer *rendu;
SDL_Window *fenetre;

SDL_Rect pers_source, pers_destination;
SDL_Rect * cameraRect;

/* Désolé Titouan j'ai du mettre cette fonction ici car elle nécéssite projectile.h et entite.h et je peux pas dcp la mettre dans projectile.c vu que ça crée une dépendance circulaire (entite.h a besoin de projectile.h et inversement) */

/* Fonction qui calcule si le projectile passé en parametre est rentré en collision avec soit le joueur soit un ennemi et enleve des points de vie en conséquence */
void collisionProjEntite(projectiles_t *projectile, ennemi_t *ennemi, SDL_Rect *playerRect, SDL_Rect *cameraRect, joueur_t *joueur){
    if (projectile->id == PROJ_JOUEUR && projectile->collision != 1){
        if (projectile->x + projectile->w/2 > ennemi->x && projectile->x < ennemi->x + ennemi->rect.w && projectile->y + projectile->h/2 > ennemi->y && projectile->y < ennemi->y + ennemi->rect.h){
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

int main() {
    projectiles_t projJoueur[MAX_PROJ];
    projectiles_t projEnnemi[MAX_PROJ];

    int projNbEnnemi = 0;
    int projNbJoueur = 0;

    /* Initialisation de l'objet Projectile */
    for (int i = 0; i < MAX_PROJ; i++){
        projectile_creer(&projJoueur[i]);
        projectile_creer(&projEnnemi[i]);
    }
    int isRunning = 1; int direction = DROITE;
    int tilemap[2][NB_TILE_WIDTH][NB_TILE_WIDTH];
    chargerCarte("src/tilemap_grass.txt",tilemap,0);
    chargerCarte("src/tilemap_structs.txt",tilemap,1);
    initialisation(&fenetre, &rendu);

    /* Maintenant le tableau représentant les tiles à afficher marche de la manière suivante :
    * C'est un tableau à 3 dimensions, la première dimension est le numéro de la couche (0 pour le sol, 1 pour les structures, etc...)
    * Et ensuite c'est un tableau classique à deux dimensions qui représente les tiles à afficher (x et y)
    * Pour les colisions ça reste un tableau à deux dimensions classique, qu'on charge à partir d'une des couches du tableau de tiles
    */

    //initialisation du tableau de colision
    int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT];
    chargerColisions(tilemap, tabColision, 0);

    SDL_Texture *tabTile[5];
    chargerTextures(rendu, tabTile);
    chargerTexturesEnnemi(rendu);
    chargerTexturesProj(rendu);

    cameraRect = malloc(sizeof(SDL_realloc));
    colision_t *colision = malloc(sizeof(colision_t));
    positionJoueur_t position;
    colision->haut = 0; colision->bas = 0; colision->gauche = 0; colision->droite = 0;
    colision->position = &position;
    
    cameraRect->h = CAMERA_HEIGHT;
    cameraRect->w = CAMERA_WIDTH;   

    //doivent être des cases vides
    pers_destination.y = 400;
    pers_destination.x = 400;

    cameraRect->x = pers_destination.x;
    cameraRect->y = pers_destination.y;

    

    joueur_t joueur;
    initialiserJoueur(&joueur);

    ennemi_t ennemi[NB_ENNEMI];
    for (int i = 0; i < NB_ENNEMI; i++){
        int positionRand_x = rand() % 1000;
        int positionRand_y = rand() % 1000;
        ennemi_creer(&ennemi[i]);
        ennemi[i].initEnnemi(&ennemi[i], positionRand_x, positionRand_y, 1, 100, 10);
    }

    // Gestion des événements SDL
    SDL_Event event;
    int frame = 0;
    Uint32 temps_ancien = SDL_GetTicks();
    Uint32 temps_actuel;
    int delta_temps;

    SDL_Texture *barTextureVieMax = creationTextureBar(rendu, JAUNE);
    SDL_Texture *barTextureVie = creationTextureBar(rendu, ROUGE);

    // Initialisation de la structure barre de vie
    HealthBar healthBar;
    initHealthBar(&healthBar, 50, 50, HEALTH_BAR_WIDTH);

    // Création de deux rectangles : un pour la barre de vie fixe et l'autre pour celle qui baisse (vie restante)
    SDL_Rect healthBarMaxRect = { healthBar.x, healthBar.y, healthBar.maxWidth, HEALTH_BAR_HEIGHT };
    SDL_Rect *healthBarRect = malloc(sizeof(SDL_Rect));
    *healthBarRect = (SDL_Rect){ healthBar.x, healthBar.y, healthBar.width, HEALTH_BAR_HEIGHT };

    // Variable temporaire
    int count = 100;

    Button jouerButton, difficulteButton, facileButton, normalButton, difficileButton, accueilButton, gameoverButton, retryButton;

    // Création des boutons
    jouerButton = createButton(rendu, "JOUER", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);
    difficulteButton = createButton(rendu, "DIFFICULTE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    facileButton = createButton(rendu, "FACILE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 0, BUTTON_WIDTH, BUTTON_HEIGHT, VERT);
    normalButton = createButton(rendu, "NORMAL", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 1, BUTTON_WIDTH, BUTTON_HEIGHT, ORANGE);
    difficileButton = createButton(rendu, "DIFFICILE", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 2, BUTTON_WIDTH, BUTTON_HEIGHT, ROUGE);
    accueilButton = createButton(rendu, "ACCUEIL", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, 250 + BUTTON_HEIGHT * 3, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    gameoverButton = createButton(rendu, "GAME OVER", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);
    retryButton = createButton(rendu, "RETRY", (WINDOWS_WIDTH - BUTTON_WIDTH) / 2, (WINDOWS_HEIGHT - BUTTON_HEIGHT) / 2 + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT, NOIR);

    /*
    * MENU =
    * 0 - Jeu
    * 1 - Page d'accueil
    * 2 - Choix de la difficulté
    * 3 - Game Over
    * */

   int menu = 1;
    
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
        
        if(menu == 1){
            SDL_RenderClear(rendu);
            affichageMenuImage(rendu);

            // Dessiner les boutons
            drawButton(rendu, jouerButton);
            drawButton(rendu, difficulteButton);

            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_ADD);


            if(mouseOnButton(jouerButton)){   
                /* I want to fill the rect with transparent color */
                SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
                SDL_RenderFillRect(rendu, &jouerButton.rect);
            }

            if(mouseOnButton(difficileButton)){
                /* I want to fill the rect with transparent color */
                SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
                SDL_RenderFillRect(rendu, &difficileButton.rect);
            }

            SDL_RenderPresent(rendu);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);
            
        }

        else if(menu == 2){
            SDL_RenderClear(rendu);
            affichageMenuImage(rendu);

            drawButton(rendu, facileButton);
            drawButton(rendu, normalButton);
            drawButton(rendu, difficileButton);
            drawButton(rendu, accueilButton);

            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_ADD);

            // Dessiner les boutons
            if(mouseOnButton(facileButton)){
                SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
                SDL_RenderFillRect(rendu, &facileButton.rect);
            }
            if(mouseOnButton(normalButton)){
                SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
                SDL_RenderFillRect(rendu, &normalButton.rect);
            }
            if(mouseOnButton(accueilButton)){
                SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
                SDL_RenderFillRect(rendu, &accueilButton.rect);
            }
            if(mouseOnButton(difficileButton)){
                SDL_SetRenderDrawColor(rendu, 255, 255, 255, 100);
                SDL_RenderFillRect(rendu, &difficileButton.rect);
            }
            

            SDL_RenderPresent(rendu);
            SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);
        }

        


        else if(menu == 3){
            SDL_RenderClear(rendu);
            affichageMenuImage(rendu);

            // Dessiner les boutons
            drawButton(rendu, gameoverButton);
            drawButton(rendu, retryButton);
            
            SDL_RenderPresent(rendu);
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
            
            updateHealthBar(&healthBar, healthBarRect, joueur.pv);

            if(joueur.pv <= 0){
                menu = 3;
            }

            updateCamera(&pers_destination,rendu, cameraRect,tilemap, tabTile, colision, tabColision, position);
            action(clavier, &pers_destination, colision, &direction);
            updateCamera(&pers_destination,rendu, cameraRect,tilemap, tabTile, colision, tabColision, position);
            
            for (int i = 0; i < NB_ENNEMI; i++){
                Uint32 temp_vivant = SDL_GetTicks() - ennemi[i].delta;
                ennemi[i].updateEnnemi(&ennemi[i], cameraRect, &pers_destination, tabColision, projEnnemi, &projNbEnnemi, temp_vivant);
            }
            
            if (projNbEnnemi == MAX_PROJ){
                projNbEnnemi = 0;
            }
            
            action(clavier, &pers_destination, colision, &direction);
            

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
            for (int i = 0; i < NB_ENNEMI; i++){
                ennemi[i].renderEnnemi(rendu, &ennemi[i], frame);
            }

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