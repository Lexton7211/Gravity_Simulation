#include <iostream>
#include <vector>
#include "display.hpp"
#include "logic.hpp"

int main(){
    const double TARGET_FPS = 180.0;
    const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;
    double deltaTime = 1.0 / TARGET_FPS;
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
    temp.x = 200;
    temp.y = 200;
    temp.vx = 0;
    temp.vy = 0;
    temp.radius = 32;
    temp.mass = 30;
    temp.color = white;
    balls.push_back(temp);

    temp.x = 800;
    temp.y = 500;
    temp.vx = 0;
    temp.vy = 0;
    temp.radius = circleRadius;
    temp.mass = 50;
    temp.color = white;
    balls.push_back(temp);

    bool running = true;
    SDL_Event event;
    double gravity = 0.005;
    int selectedball = 0;
    while (running){
        Uint64 start = SDL_GetPerformanceCounter();
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

                    balls[1].vx = 0;
                    balls[1].vy = 0;
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

        int x, y;
        Uint32 buttons = SDL_GetMouseState(&x, &y);

        if(buttons & SDL_BUTTON_LMASK){
            balls[selectedball].x = x;
            balls[selectedball].y = y;
        }

        balls[0].vy += gravity;
        checkWallCollisions(balls[0], deltaTime);
        balls[0].x += balls[0].vx;
        balls[0].y += balls[0].vy;

        //balls[1].vy += gravity;
        checkWallCollisions(balls[1], deltaTime);
        balls[1].x += balls[1].vx;
        balls[1].y += balls[1].vy;

        ballCollisions(balls[0], balls[1]);
        clearDisplay(renderer);
        drawCircle(renderer, balls[0]);
        drawCircle(renderer, balls[1]);

        presentDisplay(renderer);
        Uint64 end = SDL_GetPerformanceCounter();
        double frameTime =
            (double)(end - start) / SDL_GetPerformanceFrequency();
        double fps = 1.0 / frameTime;

        if (frameTime < TARGET_FRAME_TIME)
        {
            SDL_Delay((Uint32)((TARGET_FRAME_TIME - frameTime) * 1000.0));
        }
    }


    teardownDisplay(renderer);
    return 0;
}