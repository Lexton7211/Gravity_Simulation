#include "logic.hpp"
#include <iostream>

void checkWallCollisions(Ball& ball, double deltaTime){
    if(ball.y + ball.radius >= 1000){
        ball.vy *= -0.8;
    }
}