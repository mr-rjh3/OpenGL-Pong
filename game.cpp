
#include "game.hpp"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

    
void Game::ballMove() {
    ball.x += ball.xSpeed;
    ball.y += ball.ySpeed;
}

void Game::ballBounce() {
    // right wall / paddle
    if(ball.x + ball.radius >= paddleRight.x - paddleRight.width && ball.x - ball.radius < paddleRight.x + paddleRight.width) { // if the ball.x is within the paddle.x range
        if(ball.y + ball.radius >= paddleRight.y - paddleRight.height && ball.y - ball.radius <= paddleRight.y + paddleRight.height) { // if the ball.y is within the paddle.y range
            // pick a random angle between 45 and 135 degrees
            // TODO might not want it random
            float angle = (rand() % 90 + 45) * (M_PI / 180);
            ball.xSpeed = cos(angle) * 2;
            ball.ySpeed = sin(angle) * 2;
        }
    }
    // left wall / paddle
    if(ball.x - ball.radius <= paddleLeft.x + paddleLeft.width && ball.x + ball.radius > paddleLeft.x - paddleLeft.width) { // if the ball.x is within the paddle.x range
        if(ball.y + ball.radius >= paddleLeft.y - paddleLeft.height && ball.y - ball.radius <= paddleLeft.y + paddleLeft.height) { // if the ball.y is within the paddle.y range
            // pick a random angle between 45 and 135 degrees
            // TODO might not want it random
            float angle = (rand() % 90 + 45) * (M_PI / 180);
            ball.xSpeed = cos(angle) * 2;
            ball.ySpeed = sin(angle) * 2;
        }
    }
    if (ball.y + ball.radius >= 600) { // bottom wall
        ball.ySpeed = -ball.ySpeed;
    }
    if (ball.y - ball.radius <= 0) { // top wall
        ball.ySpeed = -ball.ySpeed;
    }
    if(ball.x + ball.radius >= 800) { // right wall 
        //TODO: add score
        ball.x = 400;
        ball.y = 300;
        ball.xSpeed = -ball.xSpeed;
    }
    if(ball.x - ball.radius <= 0) { // left wall
        //TODO: add score
        ball.x = 400;
        ball.y = 300;
        ball.xSpeed = -ball.xSpeed;
    }

}