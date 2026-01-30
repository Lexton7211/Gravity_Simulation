#include <iostream>
#include "display.hpp"

int main(){
    double deltaTime = 1.0 / 100.0;
    SDL_Renderer* renderer = nullptr;

    renderer = setupDisplay();
    if(renderer == nullptr){
        return 1;
    }

    bool running = true;
    SDL_Event event;
    const int circleRadius = 52;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
        }

        clearDisplay(renderer);
        
        drawCircle(renderer, 800, 500, circleRadius);
        presentDisplay(renderer);
        SDL_Delay(10);
    }

    teardownDisplay(renderer);
    return 0;
}