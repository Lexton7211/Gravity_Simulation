#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <SDL2/SDL.h>

struct Ball {
    double x, y;
    double vx, vy;
    int radius;
    double mass;
    SDL_Color color;
};

void checkWallCollisions(Ball& ball, double deltaTime);
void ballCollisions(Ball& ball1, Ball& ball2);
void updateGravity(Ball& ball, double gravity, double deltaTime);

#endif