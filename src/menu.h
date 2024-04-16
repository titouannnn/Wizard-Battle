#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "./fonctions.h"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 75

/**
 * \struct Button
 * \brief Structure pour représenter un bouton.
 */
typedef struct {
    SDL_Rect rect;  /**< Rectangle définissant la position et la taille du bouton. */
    SDL_Texture* texture;   /**< Texture du bouton. */
} Button;

/**
 * \brief Crée un bouton.
 *
 * Cette fonction crée un bouton.
 *
 * \param renderer Le renderer SDL pour l'affichage.
 * \param text Texte du bouton.
 * \param x Position horizontale du bouton.
 * \param y Position verticale du bouton.
 * \param width Largeur du bouton.
 * \param height Hauteur du bouton.
 * \param couleur Couleur du bouton.
 * \return Le bouton créé.
 */
Button createButton(SDL_Renderer* renderer, TTF_Font *font, const char* text, int x, int y, int width, int height, Couleur_t couleur);

/**
 * \brief Affiche un bouton.
 *
 * Cette fonction affiche un bouton.
 *
 * \param renderer Le renderer SDL pour l'affichage.
 * \param button Bouton à afficher.
 */
void drawButton(SDL_Renderer* renderer, Button button);

/**
 * \brief Vérifie si un bouton est cliqué.
 *
 * Cette fonction vérifie si un bouton est cliqué.
 *
 * \param event Événement SDL.
 * \param button Bouton à vérifier.
 * \return 1 si le bouton est cliqué, 0 sinon.
 */
int clickButton(SDL_Event event, Button button);

/**
 * \brief Vérifie si la souris est sur un bouton.
 *
 * Cette fonction vérifie si la souris est sur un bouton.
 *
 * \param button Bouton à vérifier.
 * \return 1 si la souris est sur le bouton, 0 sinon.
 */
int mouseOnButton(Button button);

/**
 * \brief Initialise les boutons.
 *
 * Cette fonction initialise les boutons.
 *
 * \param jouerButton Bouton jouer.
 * \param difficulteButton Bouton difficulté.
 * \param facileButton Bouton facile.
 * \param normalButton Bouton normal.
 * \param difficileButton Bouton difficile.
 * \param accueilButton Bouton accueil.
 * \param gameoverButton Bouton game over.
 * \param retryButton Bouton retry.
 * \param rendu Renderer.
 */
void initBoutons(TTF_Font *font, Button *jouerButton, Button *difficulteButton, Button *facileButton, Button *normalButton, Button *difficileButton, Button *accueilButton, Button *gameoverButton, Button *retryButton, SDL_Renderer *rendu);

/**
 * \brief Gère les boutons.
 *
 * Cette fonction gère les boutons.
 *
 * \param menu Menu actuel.
 * \param rendu Renderer.
 * \param jouerButton Bouton jouer.
 * \param difficulteButton Bouton difficulté.
 * \param difficileButton Bouton difficile.
 * \param accueilButton Bouton accueil.
 * \param gameoverButton Bouton game over.
 * \param retryButton Bouton retry.
 * \param facileButton Bouton facile.
 * \param normalButton Bouton normal.
 */
void menuFonc(int menu, SDL_Renderer * rendu, Button jouerButton, Button difficulteButton, Button difficileButton, Button accueilButton, Button gameoverButton, Button retryButton, Button facileButton, Button normalButton);



/**
 * \brief Affiche le menu principal.
 *
 * Cette fonction affiche le menu principal.
 *
 * \param rendu Renderer.
 * \param jouerButton Bouton jouer.
 * \param difficulteButton Bouton difficulté.
 */
void menuPrincipal(SDL_Renderer *rendu, Button jouerButton, Button difficulteButton);

/**
 * \brief Affiche le menu de difficulté.
 *
 * Cette fonction affiche le menu de difficulté.
 *
 * \param rendu Renderer.
 * \param facileButton Bouton facile.
 * \param normalButton Bouton normal.
 * \param difficileButton Bouton difficile.
 * \param accueilButton Bouton accueil.
 */
void menuDifficulte(SDL_Renderer *rendu, Button facileButton, Button normalButton, Button difficileButton, Button accueilButton, char* difficulte, TTF_Font *font);

/**
 * \brief Affiche le menu de pause.
 *
 * Cette fonction affiche le menu de pause.
 *
 * \param rendu Renderer.
 * \param accueilButton Bouton accueil.
 */
int menuGameOver( SDL_Renderer *rendu, TTF_Font *font, Button gameoverButton, Button retryButton, int vague, int duree_partie, int nb_kill);

/**
 * \brief Affiche un texte.
 *
 * Cette fonction affiche à l'écran.
 *
 * \param rendu Renderer.
 * \param texte Texte à afficher.
 * \param x Position horizontale du texte.
 * \param y Position verticale du texte.
 * \param taille Taille du texte.
 * \param couleur Couleur du texte
 */
void afficherMessage(SDL_Renderer *rendu, TTF_Font *font, char *texte, int x, int y, int taille);


#endif