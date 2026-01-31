#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <SDL2/SDL.h>

struct Ball {
    double x, y;
    double vx, vy;
    int radius;
    SDL_Color color;
};

void checkWallCollisions(Ball& ball, double deltaTime);

#endif