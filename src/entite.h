#ifndef ENTITE_H
#define ENTITE_H

typedef struct entite_s entite_t;

struct entite_s {
    int x;
    int y;
    int pv;
    int pvMax;
    int attaque;
    int defense;
    int vitesse;
    int id;
};

void initialiserJoueur(entite_t * joueur);
void initialiserEnnemi(entite_t * ennemi);

void attaquer(entite_t * attaquant, entite_t * defenseur);

#endif // ENTITE_H
