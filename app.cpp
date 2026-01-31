#include <iostream>
#include <vector>
#include "display.hpp"
#include "logic.hpp"

int main(){
    double deltaTime = 1.0 / 100.0;
    SDL_Renderer* renderer = nullptr;

    renderer = setupDisplay();
    if(renderer == nullptr){
        return 1;
    }
    //colors
    SDL_Color white = {255, 255, 255, 255};

    const int circleRadius = 52;
    std::vector<Ball> balls;
    Ball temp;
    temp.x = 800;
    temp.y = 500;
    temp.vx = 0;
    temp.vy = 0;
    temp.radius = circleRadius;
    temp.color = white;
    balls.push_back(temp); 
    bool running = true;
    SDL_Event event;
    double gravity = 0.5;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
        }
        balls[0].vy += gravity;
        checkWallCollisions(balls[0], deltaTime);
        balls[0].y += balls[0].vy;

        clearDisplay(renderer);
        for(Ball ball : balls){
            drawCircle(renderer, ball.x, ball.y, ball.radius);
        }
        presentDisplay(renderer);
        SDL_Delay(10);
    }

    teardownDisplay(renderer);
    return 0;
}