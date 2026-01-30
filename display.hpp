#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SDL2/SDL.h>
#include <iostream>

const int window_width = 1600;
const int window_height = 1000;

SDL_Renderer* setupDisplay();
void presentDisplay(SDL_Renderer *renderer);
void clearDisplay(SDL_Renderer *renderer);
void teardownDisplay(SDL_Renderer *renderer);
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius);

#endif