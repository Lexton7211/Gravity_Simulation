#include "logic.hpp"
#include <iostream>

void checkWallCollisions(Ball& ball, double deltaTime){
    if(ball.y + ball.radius >= 1000){
        ball.y = 1000 - ball.radius;
        ball.vy *= -0.8;
    }
    if(ball.y - ball.radius <= 0){
        ball.y = 0 + ball.radius;
        ball.vy *= -0.8;
    }
    if(ball.x + ball.radius >= 1600){
        ball.x = 1600 - ball.radius;
        ball.vx *= -0.8;
    }
    if(ball.x - ball.radius <= 0){
        ball.x = 0 + ball.radius;
        ball.vx *= -0.8;
    }
}

void ballCollisions(Ball& ball1, Ball& ball2){
    //calc centers
    double distX = ball1.x - ball2.x;
    double distY = ball1.y - ball2.y;
    double distance = sqrt((distX * distX) + (distY * distY));

    if(distance <= ball1.radius + ball2.radius){
        distance = ball1.radius + ball2.radius;

        double m1 = ball1.mass;
        double m2 = ball2.mass;

        double nx = (ball2.x - ball1.x) / distance;
        double ny = (ball2.y - ball1.y) / distance;

        double tx = -ny;
        double ty = nx;

        double v1n = ball1.vx * nx + ball1.vy * ny;
        double v1t = ball1.vx * tx + ball1.vy * ty;
        double v2n = ball2.vx * nx + ball2.vy * ny;
        double v2t = ball2.vx * tx + ball2.vy * ty;

        double v1n_final, v2n_final;
        if (m1 == m2)
        {
            v1n_final = v2n;
            v2n_final = v1n;
        }
        else
        {
            v1n_final = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
            v2n_final = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);
        }

        double v1x = v1n_final * nx + v1t * tx;
        double v1y = v1n_final * ny + v1t * ty;
        double v2x = v2n_final * nx + v2t * tx;
        double v2y = v2n_final * ny + v2t * ty;

        ball1.vx = v1x;
        ball1.vy = v1y;
        ball2.vx = v2x;
        ball2.vy = v2y;
    }
}