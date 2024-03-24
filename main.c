#include "game.h"

SDL_Renderer *rendu;
SDL_Window *fenetre;

SDL_Rect pers_source, pers_destination;
SDL_Rect * cameraRect;

int main() {
    int isRunning = 1;
    int tile_lvl1[NB_TILE_WIDTH][NB_TILE_WIDTH];
    chargerCarte("src/tilemap_lvl1.txt",tile_lvl1);
    initialisation(&fenetre, &rendu);

    SDL_Texture *tabTile[5];
    chargerTextures(rendu, tabTile);

    cameraRect = malloc(sizeof(SDL_realloc));
    colision_t *colision = malloc(sizeof(colision_t));
    colision->haut = 0; colision->bas = 0; colision->gauche = 0; colision->droite = 0;

    //initialisation du tableau de colision
    int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT];
    chargerColisions(tile_lvl1, tabColision);
    
    cameraRect->h = CAMERA_HEIGHT;
    cameraRect->w = CAMERA_WIDTH;   

    pers_destination.y = 400;
    pers_destination.x = 400;

    cameraRect->x = pers_destination.x;
    cameraRect->y = pers_destination.y;

    /* Création de l'objet Projectile */
    projectiles_t projectile;

    /* Initialisation de l'objet Projectile */
    projectile_creer(&projectile);

    entite_t joueur;
    initialiserJoueur(&joueur);

    entite_t ennemi;
    initialiserEnnemi(&ennemi);

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
                        printf("perso x : %d, perso y : %d\n", pers_destination.x, pers_destination.y);
                        projectile.init(&projectile, cameraRect->x + pers_destination.x, cameraRect->y + pers_destination.y, mouse_x, mouse_y, cameraRect);
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

            if(mouseOnButton(jouerButton)){
                /* I want to fill the rect with transparent color */
                SDL_SetRenderDrawColor(rendu, 255, 0, 255, 100);
                SDL_RenderFillRect(rendu, &jouerButton.rect);
            }

            if(mouseOnButton(difficileButton)){
                /* I want to fill the rect with transparent color */
                SDL_SetRenderDrawColor(rendu, 0, 255, 255, 100);
                SDL_RenderFillRect(rendu, &difficileButton.rect);
            }

            SDL_RenderPresent(rendu);

            
        }

        else if(menu == 2){
            SDL_RenderClear(rendu);
            affichageMenuImage(rendu);

            // Dessiner les boutons
            drawButton(rendu, facileButton);
            drawButton(rendu, normalButton);
            drawButton(rendu, difficileButton);
            drawButton(rendu, accueilButton);

            SDL_RenderPresent(rendu);
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
        
            // Récupération de l'état du clavier : 
            const Uint8 *clavier = SDL_GetKeyboardState(NULL);
            
            updateHealthBar(&healthBar, healthBarRect, joueur.pv);

            if(joueur.pv <= 0){
                menu = 3;
            }

            SDL_RenderClear(rendu);

            updateCamera(&pers_destination,rendu, cameraRect,tile_lvl1, tabTile, colision, tabColision);

            

            action(clavier, &pers_destination, &pers_source, frame, rendu, colision);
            projectile.update(&projectile, cameraRect);
            projectile.render(rendu, &projectile);
            SDL_RenderCopy(rendu, barTextureVieMax, NULL, &healthBarMaxRect);
            SDL_RenderCopy(rendu, barTextureVie, NULL, healthBarRect);

            SDL_RenderPresent(rendu);

            SDL_Delay(DELAI);
        }
    }
    free(healthBarRect);
    return fin(fenetre, rendu);
}