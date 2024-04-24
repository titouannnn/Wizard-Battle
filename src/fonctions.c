/**
 * \file fonctions.c
 * \brief Ce fichier contient diverses fonctions afin de gérer la caméra, le joueur, le jeu dans sa globalité.
 * 
 * Ce fichier contient les fonctions pour initialiser la caméra, le joueur, les textures, les menus, les collisions, les actions du joueur, le rendu du fond, la mise à jour de la caméra, la position du joueur, la destruction des textures, la destruction de la police, l'affichage des images des différents menus, l'affichage du viseur, l'initialisation des fonctions, l'actualisation du sprite, l'obtention de la direction de la position de la souris, la mise à jour de la caméra, l'initialisation de la position du joueur, la destruction des textures des barres, la destruction de la police, l'affichage du fond.
 * 
 */
#include "fonctions.h"


SDL_Surface *temp_surface;

int vrai = 1;
int direction = 0;

/*
SDL_Texture *run_front_tex;
SDL_Texture *run_back_tex;
*/
SDL_Texture *run_right_tex;
SDL_Texture *run_left_tex;

SDL_Texture *fond_tex;

// Texture du menu
SDL_Texture *accueil_tex;
SDL_Texture *gameover_tex;
SDL_Texture *pause_tex;
SDL_Texture *difficulte_tex;


SDL_Texture *tile_verte_tex;
SDL_Texture *tilemap_grass_tex;
SDL_Texture *tilemap_structures_tex;

SDL_Texture *aim_tex;
//a supprimer
SDL_Texture *tilemap;



/**
 * @brief Initializes the camera.
 * @return A pointer to the initialized SDL_Rect representing the camera.
 */
SDL_Rect * initCamera(){
    SDL_Rect *cameraRect = malloc(sizeof(SDL_Rect));
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = CAMERA_WIDTH;
    cameraRect->h = CAMERA_HEIGHT;
    return cameraRect;
}

/**
 * @brief Initializes the player.
 * @param x The x-coordinate of the player.
 * @param y The y-coordinate of the player.
 * @return A pointer to the initialized SDL_Rect representing the player.
 */
SDL_Rect * initJoueur(int x, int y){
    SDL_Rect *pers_destination = malloc(sizeof(SDL_Rect));
    pers_destination->x = x;
    pers_destination->y = y;
    pers_destination->w = DIM_SPRITE_PLAYER_X;
    pers_destination->h = DIM_SPRITE_PLAYER_Y;
    return pers_destination;
}

/**
 * @brief Initializes various game functions.
 * @param tilemap The tilemap of the game.
 * @param tabColision The collision table.
 * @param fenetre The game window.
 * @param rendu The game renderer.
 * @param cameraRect The camera rectangle.
 * @param position The position of the player.
 * @param colision The collision object.
 * @param pers_destination The destination of the player.
 * @param temps_ancien The old time.
 * @param barTextureVieMax The texture for the maximum life bar.
 * @param barTextureVie The texture for the life bar.
 * @param healthBar The health bar.
 * @param barTextureManaMax The texture for the maximum mana bar.
 * @param barTextureMana The texture for the mana bar.
 * @param manaBar The mana bar.
 */

void initFonctions(
    int tilemap[2][NB_TILE_WIDTH][NB_TILE_WIDTH],
    int tabColision[NB_TILE_WIDTH][NB_TILE_HEIGHT],
    SDL_Window **fenetre,
    SDL_Renderer **rendu,
    SDL_Rect **cameraRect,
    positionJoueur_t *position,
    colision_t **colision,
    SDL_Rect *pers_destination,
    Uint32 *temps_ancien,
    SDL_Texture **barTextureVieMax,
    SDL_Texture **barTextureVie,
    bar_t *healthBar,
    SDL_Texture **barTextureManaMax,
    SDL_Texture **barTextureMana,
    bar_t *manaBar
) {
    chargerCarte("src/tilemap_grass.txt",tilemap,0);
    chargerCarte("src/tilemap_structs.txt",tilemap,1);
    chargerColisions(tilemap, tabColision, 1);
    initialisation(fenetre, rendu);
    *cameraRect = initCamera();
    *position = *initPositionJoueur();
    *colision = initColision();
    *pers_destination = *initJoueur(400, 400); 
    *temps_ancien = SDL_GetTicks();
    *barTextureVieMax = creationTextureBar(*rendu, VERT_FONCE);
    *barTextureVie = creationTextureBar(*rendu, VERT);
    initBar(healthBar, 50, 50, BAR_WIDTH);
    *barTextureManaMax = creationTextureBar(*rendu, BLEU_FONCE);
    *barTextureMana = creationTextureBar(*rendu, BLEU);
    initBar(manaBar, 50, 100, BAR_WIDTH);
}

/**
 * @brief Initialise la SDL, la SDL_ttf, la fenêtre et le rendu.
 * @param fenetre Pointeur vers la fenêtre à initialiser.
 * @param rendu Pointeur vers le rendu à initialiser.
 * @return 0 si l'initialisation de la SDL ou la création de la fenêtre échoue, 1 sinon.
 */

int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu) {
    // Initialisation de la bibliothèque SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Problème d'initialisation de la bibliothèque SDL : %s\n", SDL_GetError());
        return 0;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre et du rendu
    *fenetre = SDL_CreateWindow("Wizard Battle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWS_WIDTH, WINDOWS_HEIGHT, SDL_WINDOW_OPENGL);
    *rendu = SDL_CreateRenderer(*fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(*rendu, 255, 255, 255, 255);

    if (*fenetre != NULL && *rendu != NULL) {
        return 1;
    } else {
        printf("Problème de création de la fenêtre : %s\n", SDL_GetError());
        return 0;
    }
    
}

/**
 * @brief Charge les textures nécessaires pour le jeu.
 * @param rendu Pointeur vers le rendu utilisé pour créer les textures.
 */

void chargerTextures(SDL_Renderer *rendu){
    temp_surface = IMG_Load("images/aim.png");
    aim_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(aim_tex == NULL){
        printf("Erreur de chargement de l'image 'aim.png': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'aim.png' réussi\n");




    /* Images des menus */

    /* Image d'accueil*/
    temp_surface = IMG_Load("images/menu/Accueil.png");
    accueil_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(accueil_tex == NULL){
        printf("Erreur de chargement de l'image 'accueil.png': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'accueil.png' réussi\n");

    /* Image de game over */
    temp_surface = IMG_Load("images/menu/GameOver.png");
    gameover_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(gameover_tex == NULL){
        printf("Erreur de chargement de l'image 'GameOver.png': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'GameOver.png' réussi\n");

    /* Image de difficulté */
    temp_surface = IMG_Load("images/menu/Difficulte.png");
    difficulte_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(accueil_tex == NULL){
        printf("Erreur de chargement de l'image 'Difficulte.png': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'Diffilculte.png' réussi\n");

    /* Image de pause */
    temp_surface = IMG_Load("images/menu/Pause.png");
    pause_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(accueil_tex == NULL){
        printf("Erreur de chargement de l'image 'Pause.png': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'Pause.png' réussi\n");

    temp_surface = SDL_LoadBMP("images/wizard_run_right.bmp");
    run_right_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_right_tex == NULL){
        printf("Erreur de chargement de l'image 'wizard_run_right': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'wizard_run_right' réussi\n");

    temp_surface = SDL_LoadBMP("images/wizard_run_left.bmp");
    run_left_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_left_tex == NULL){
        printf("Erreur de chargement de l'image 'wizard_run_left': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'wizard_run_left' réussi\n");

    temp_surface = IMG_Load("images/backround.png");
    fond_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(fond_tex == NULL){
        printf("Erreur de chargement du fond: %s\n", SDL_GetError());
    }
    else printf("Chargement du fond réussi\n");

    
    temp_surface = IMG_Load("images/tilemap.png");
    tilemap = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(tilemap == NULL){
        printf("chargement de la tilemap échoué \n");
    }
    else{ printf("Chargement de la tilemap réussi\n"); }

    temp_surface = IMG_Load("images/tilemap_grass.png");
    tilemap_grass_tex = SDL_CreateTextureFromSurface(rendu,temp_surface);
    SDL_FreeSurface(temp_surface);
    if(tilemap_grass_tex == NULL){
        printf("chargement de la tilemap_grass échoué");
    }
    else printf("chargement de la tilemap_grass reussi \n");

    //chargement de la seconde tilemap
    temp_surface = IMG_Load("images/tilemap_structures.png");
    tilemap_structures_tex = SDL_CreateTextureFromSurface(rendu,temp_surface);
    SDL_FreeSurface(temp_surface);
    if(tilemap_structures_tex == NULL){
        printf("chargement de la tilemap_struct échoué");
    }
    else printf("chargement de la tilemap_struct reussi \n");

}

/**
 * @brief Affiche un viseur à la place du curseur de la souris.
 * @param rendu Pointeur vers le rendu utilisé pour créer les textures.
 * @param mx Coordonnée x de la souris.
 * @param my Coordonnée y de la souris.
 */
void afficherAim(SDL_Renderer *rendu, int mx, int my){
    SDL_Rect dest;
    dest.x = mx - 25;
    dest.y = my - 25;
    dest.w = 50;
    dest.h = 50;
    SDL_RenderCopy(rendu, aim_tex, NULL, &dest);
}

/**
 * @brief Libère les ressources de la SDL et ferme la fenêtre.
 * @param fenetre Pointeur vers la fenêtre à détruire.
 * @param rendu Pointeur vers le rendu à détruire.
 * @return 0
 */

int fin(SDL_Window *fenetre, SDL_Renderer *rendu, TTF_Font *arial) {
    TTF_CloseFont(arial);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}

/**
 * @brief Affiche l'image du menu.
 * @param rendu Pointeur vers le rendu utilisé pour afficher l'image.
 */

void affichageAccueilImage(SDL_Renderer *rendu){
    SDL_RenderCopy(rendu, accueil_tex, 0, 0);
}

/**
 * @brief Affiche l'image du menu.
 * @param rendu Pointeur vers le rendu utilisé pour afficher l'image.
 */

void affichageGameOverImage(SDL_Renderer *rendu){
    SDL_RenderCopy(rendu, gameover_tex, 0, 0);
}

/**
 * @brief Affiche l'image du menu.
 * @param rendu Pointeur vers le rendu utilisé pour afficher l'image.
 */

void affichagePauseImage(SDL_Renderer *rendu){
    SDL_RenderCopy(rendu, pause_tex, 0, 0);
}

/**
 * @brief Affiche l'image du menu.
 * @param rendu Pointeur vers le rendu utilisé pour afficher l'image.
 */

void affichageDifficulteImage(SDL_Renderer *rendu){
    SDL_RenderCopy(rendu, difficulte_tex, 0, 0);
}

/**
 * @brief Obtient la direction de la position de la souris par rapport à la position du personnage.
 * @param pers_destination Pointeur vers le rectangle définissant la position du personnage.
 * @return GAUCHE si la souris est à gauche du personnage, DROITE sinon.
 */

int getMousePositionDirection(SDL_Rect *pers_destination){
    int direction = GAUCHE;
    int x_joueur = pers_destination->x;
    int y_joueur = pers_destination->y;
    int x, y;
    SDL_GetMouseState(&x, &y);
    int x_relatif, y_relatif;
    x_relatif = x - x_joueur;
    y_relatif = -(y - y_joueur);

    
    if (x_relatif > 0) {
        direction = DROITE;
    } else if (x_relatif < 0) {
        direction = GAUCHE;
    }
    return direction;
}

/**
 * @brief Actualise le sprite du personnage.
 * @param nb_sprite Le nombre de sprites.
 * @param frame Le numéro du sprite.
 * @param direction La direction du personnage.
 * @param src Le rectangle source du sprite.
 * @param dst Le rectangle de destination du sprite.
 * @param rendu Le rendu utilisé pour afficher le sprite.
 */
void actualisationSprite(int nb_sprite, int frame, int *direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu){
    SDL_Texture *texSprite;
    
    if (*direction == DROITE) { 
        texSprite = run_right_tex;
    } else if (*direction == GAUCHE) { 
        texSprite = run_left_tex;
    }

    src->x = (frame % nb_sprite)*DIM_SPRITE_PLAYER_X;
    src->y = 0;
    src->w = DIM_SPRITE_PLAYER_X;
    src->h = DIM_SPRITE_PLAYER_Y;
    dst->w = DIM_SPRITE_PLAYER_X/1.5;
    dst->h = DIM_SPRITE_PLAYER_Y/1.5;

    // On affiche les sprites  :
    SDL_RenderCopy(rendu, texSprite, src, dst);
}

/**
 * @brief Gère les actions du joueur.
 * @param clavier Les touches du clavier.
 * @param pers_destination Le rectangle définissant la position du personnage.
 * @param colision Les collisions du personnage.
 * @param direction La direction du personnage.
 */
void action(const Uint8 *clavier, SDL_Rect *pers_destination, colision_t *colision, int *direction) {

    /* C'est ici qu'on vérifie les conditions de colisions*/
    if (clavier[SDL_SCANCODE_W] && pers_destination->y > 0 ) {
        if(!colision->haut){
            pers_destination->y -= VITESSE_JOUEUR_Y;
        }
        else if(colision->haut){
            pers_destination->y += VITESSE_JOUEUR_Y;
        }
        
    }
    if (clavier[SDL_SCANCODE_S] && (pers_destination->y < WINDOWS_HEIGHT - DIM_SPRITE_PLAYER_X)) {
        if(!colision->bas){
            pers_destination->y += VITESSE_JOUEUR_Y;
        }
        else if(colision->bas){
            pers_destination->y -= VITESSE_JOUEUR_Y;
        }
    

    }
    if (clavier[SDL_SCANCODE_A] && pers_destination->x > 0 ) {
        if(!colision->gauche){
            pers_destination->x -= VITESSE_JOUEUR_X;
        }
        else if(colision->gauche){
            pers_destination->x += VITESSE_JOUEUR_X;
        }
    
    }
    if (clavier[SDL_SCANCODE_D] && (pers_destination->x < WINDOWS_WIDTH - DIM_SPRITE_PLAYER_X)) {
        if(!colision->droite){
            pers_destination->x += VITESSE_JOUEUR_X;
        }
        else if(colision->droite){
            pers_destination->x -= VITESSE_JOUEUR_X;
        }
        
    }
    *direction = getMousePositionDirection(pers_destination);
}

/**
 * @brief Rendu du fond.
 * @param rendu Le rendu utilisé pour afficher le fond.
 * @param cameraRect Le rectangle définissant la position de la caméra.
 */
void updateCamera(SDL_Rect *pers_destination, SDL_Renderer *rendu, SDL_Rect *cameraRect, int tab[2][NB_TILE_HEIGHT][NB_TILE_WIDTH], colision_t *colision, int tabColisions[NB_TILE_HEIGHT][NB_TILE_WIDTH], positionJoueur_t position) {
    // Facteur d'interpolation linéaire
    const float interpolationFactor = 0.1;

    // Calcul de la différence entre la position actuelle de la caméra et la position désirée du joueur
    int dx = (pers_destination->x * 2) - cameraRect->x;
    int dy = (pers_destination->y * 4) - cameraRect->y;

    // Application de l'interpolation linéaire
    cameraRect->x += (int)(dx * interpolationFactor);
    cameraRect->y += (int)(dy * interpolationFactor);

    // Correction des limites de la caméra
    if (cameraRect->x < 0) {
        cameraRect->x = 0;
    }
    if (cameraRect->y < 0) {
        cameraRect->y = 0;
    }
    if (cameraRect->y > HAUTEUR_FOND - CAMERA_HEIGHT) {
        cameraRect->y = HAUTEUR_FOND - CAMERA_HEIGHT;
    }
    if (cameraRect->x > LARGEUR_FOND - CAMERA_WIDTH) {
        cameraRect->x = LARGEUR_FOND - CAMERA_WIDTH;
    }
    

    // Fonction pour déterminer la position du joueur
    initialiser_position_joueur(&position, cameraRect, pers_destination);
    //printf("case hg : %d %d\n",position.case_hg.casx,position.case_hg.casy);

    //Affichage de la première couche (herbe)
    afficherCarte(tab, rendu, cameraRect, position, colision, tilemap_grass_tex,0);

    // Affichage de la seconde couche (structures)
    afficherCarte(tab, rendu, cameraRect, position, colision, tilemap_structures_tex,1);

    colisions(position, colision, tabColisions);
}


/**
 * @brief Initialise la position du joueur.
 * @param positionJoueur Pointeur vers la structure représentant la position du joueur.
 * @param cameraRect Pointeur vers le rectangle définissant la position de la caméra.
 * @param pers_destination Pointeur vers le rectangle définissant la position du personnage.
 */

void initialiser_position_joueur(positionJoueur_t *positionJoueur, SDL_Rect *cameraRect, SDL_Rect *pers_destination) {
  const int marge_joueur = DIM_SPRITE_PLAYER_X / 7;
  const float unite_x = 54.11; //x = 920 / NB_TILE_WIDTH -1
  const float unite_y = 127.05; //y = 2160 / NB_TILE_HEIGHT -1

    /*Amélioration possible : au lieu de faire avec les 4 coins, faire un cercle (beacoup plus galère)*/

    // Coin supérieur gauche
    positionJoueur->case_hg.casx = ((pers_destination->x + marge_joueur-2) / unite_x); 
    positionJoueur->case_hg.casy = ((cameraRect->y + (1/2)*marge_joueur) / unite_y);

    // Coin supérieur droit 
    positionJoueur->case_hd.casx = ((pers_destination->x + 2*marge_joueur) / unite_x); 
    positionJoueur->case_hd.casy = ((cameraRect->y + (1/2)*marge_joueur) / unite_y);

    // Coin bas gauche 
    positionJoueur->case_bg.casx = ((pers_destination->x + marge_joueur-2) / unite_x); 
    positionJoueur->case_bg.casy = ((cameraRect->y + (5*marge_joueur)) / unite_y);

    // Coin bas droit 
    positionJoueur->case_bd.casx = ((pers_destination->x + 2*marge_joueur) / unite_x); 
    positionJoueur->case_bd.casy = ((cameraRect->y + (5*marge_joueur)) / unite_y);

    /*
    printf("case hg : %d %d\n",positionJoueur->case_hg.casx,positionJoueur->case_hg.casy);
    printf("case hd : %d %d\n",positionJoueur->case_hd.casx,positionJoueur->case_hd.casy);
    printf("case bg : %d %d\n",positionJoueur->case_bg.casx,positionJoueur->case_bg.casy);
    printf("case bd : %d %d\n",positionJoueur->case_bd.casx,positionJoueur->case_bd.casy);

    printf("ratio x : %f\n",(float)cameraRect->x / (float)pers_destination->x);
    printf("pers : %d %d\n",pers_destination->x,pers_destination->y);
    printf("camera : %d %d\n\n",cameraRect->x,cameraRect->y); 
    */
}

/* FONCTION DE DESTRUCTION */

/**
 * @brief Détruit une texture.
 * @param texture Pointeur vers la texture à détruire.
 */

void destructionTextureBarres(SDL_Texture *texture, ...){
    va_list textures;
    va_start(textures, texture);
    SDL_DestroyTexture(texture);
    while((texture = va_arg(textures, SDL_Texture*)) != NULL){
        SDL_DestroyTexture(texture);
    }
    va_end(textures);
}

/**
 * @brief Détruit une police.
 * @param police Pointeur vers la police à détruire.
 */

void destructionPolice(TTF_Font *police, ...){
    va_list polices;
    va_start(polices, police);
    TTF_CloseFont(police);
    while((police = va_arg(polices, TTF_Font*)) != NULL){
        TTF_CloseFont(police);
    }
    va_end(polices);
}

