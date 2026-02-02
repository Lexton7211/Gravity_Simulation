#include <iostream>
#include <vector>
#include "display.hpp"
#include "logic.hpp"

int main(){
    double deltaTime = 1.0 / 180;
    SDL_Renderer* renderer = nullptr;

    renderer = setupDisplay();
    if(renderer == nullptr){
        return 1;
    }
    //colors
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};

    //setup balls
    const int circleRadius = 52;
    std::vector<Ball> balls;
    Ball temp;
    temp.x = 200;
    temp.y = 200;
    temp.vx = 0;
    temp.vy = 0;
    temp.radius = circleRadius;
    temp.mass = 50;
    temp.color = white;
    balls.push_back(temp);

    /*
    temp.x = 800;
    temp.y = 500;
    temp.vx = 0;
    temp.vy = 0;
    temp.radius = circleRadius;
    temp.mass = 50;
    temp.color = white;
    balls.push_back(temp);
    */
    bool running = true;
    SDL_Event event;
    double gravity = 0.005;
    int selectedball = 0;
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
            //debug tools
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_1) selectedball = 0;
                if(event.key.keysym.sym == SDLK_2) selectedball = 1;
                if(event.key.keysym.sym == SDLK_f){
                    balls[0].vx = 0;
                    balls[0].vy = 0;

                    //balls[1].vx = 0;
                    //balls[1].vy = 0;
                }
                if(event.key.keysym.sym == SDLK_e){
                    if(balls[selectedball].vx > 0) balls[selectedball].vx += 2;
                    else balls[selectedball].vx -= 2;
                }
                if(event.key.keysym.sym == SDLK_r){
                    if(balls[selectedball].vy > 0) balls[selectedball].vy += 2;
                    else balls[selectedball].vy -= 2;
                }
            }

        }

        //mouse clicks for debug
        int x, y;
        Uint32 buttons = SDL_GetMouseState(&x, &y);

        if(buttons & SDL_BUTTON_LMASK){
            balls[selectedball].x = x;
            balls[selectedball].y = y;
        }
 
        //logic checks and rendering
        clearDisplay(renderer);
        for(int i = 0; i < balls.size(); i++){
            updateGravity(balls[i], gravity, deltaTime);
            if(i + 1 < balls.size()) ballCollisions(balls[i], balls[i + 1]);
            drawCircle(renderer, balls[i]);
        }

        presentDisplay(renderer);
        SDL_Delay(5.56);
    }
    teardownDisplay(renderer);
    return 0;
}