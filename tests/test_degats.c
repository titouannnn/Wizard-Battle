#include <stdio.h>
#include "../src/entite.h"
#include "../src/projectile.h"
#include "../src/global.h"

int main() {
    printf("Début du test de msie à jour de dégâts (joueur/ennemi) :\n") ;
    // Initialisation du joueur
    joueur_t joueur;
    initialiserJoueur(&joueur);
    
    // Initialisation d'un ennemi
    ennemi_t ennemi;
    initEnnemi(&ennemi, 0, 0, 1, 100, 10);
    
    // Affichage des points de vie initiaux
    printf("\nSanté du joueur : %d\n", joueur.pv);
    printf("Santé de l'ennemi : %d\n", ennemi.pv);
    
    // Simuler une attaque de l'ennemi sur le joueur
    joueur.pv -= ennemi.attaque;
    printf("\nLe joueur subit une attaque de l'ennemi\n");
    printf("Santé du joueur après l'attaque : %d\n", joueur.pv);
    
    // Simuler une attaque du joueur sur l'ennemi
    ennemi.pv -= joueur.attaque;
    printf("\nLe joueur attaque l'ennemi\n");
    printf("Santé de l'ennemi après l'attaque : %d\n", ennemi.pv);

    if(joueur.pv < 100 && ennemi.pv < 100)
        printf("\nTest réussi avec succès !!!\n");
    else    
        printf("\nLe test a echoué !!!\n");
    
    return 0;
}
