#include "projectile.h"

void projectile_creer(projectiles_t *projectile){
    projectile->init = init;
    projectile->verifCollision = verifCollision;
    projectile->update = update;
    projectile->render = render;    
}

void init(projectiles_t *projectile, float px, float py, float mx, float my, SDL_Rect *cameraRect){
    projectile->x = px + 50;
    projectile->y = py + 50;

    int d1 = mx + cameraRect->x - px;
    int d2 = my + cameraRect->y - py;

    projectile->vx = d1 / sqrt(d1 * d1 + d2 * d2);
    projectile->vy = d2 / sqrt(d1 * d1 + d2 * d2);

    projectile->w = 50;
    projectile->h = 50;
    projectile->collision = 0;
    projectile->vitesse = 10;
}

int verifCollision(projectiles_t *projectile){
    if (projectile->collision == 1){
        return 1;
    }
    return 0;
}

void update(projectiles_t *projectile, SDL_Rect *cameraRect){
    projectile->x += projectile->vx * projectile->vitesse;
    projectile->y += projectile->vy * projectile->vitesse;
    projectile->rect.x = projectile->x - cameraRect->x;
    projectile->rect.y = projectile->y - cameraRect->y;
    projectile->rect.w = projectile->w;
    projectile->rect.h = projectile->h;
}

void renderCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur bleue
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

void render(SDL_Renderer *rendu, projectiles_t *projectile){
    renderCircle(rendu, projectile->rect.x + projectile->rect.w / 2, 
                            projectile->rect.y + projectile->rect.h / 2, 
                            projectile->rect.w / 2);
}







