#include "game.hpp"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

using namespace std;

void Game::ballMove() {
    if(!scored && !paused && score[0] < MATCH_POINT && score[0] < MATCH_POINT){
        ball.x += ball.xSpeed;
        ball.y += ball.ySpeed;
    }
}

void Game::checkCollision() {
    // right paddle
    if(ball.x + ball.radius >= paddleRight.x - paddleRight.width && ball.x - ball.radius < paddleRight.x + paddleRight.width) { // if the ball.x is within the paddle.x range
        if(ball.y + ball.radius >= paddleRight.y - paddleRight.height && ball.y - ball.radius <= paddleRight.y + paddleRight.height) { // if the ball.y is within the paddle.y range
            // Bounce ball
            if(ball.xSpeed > 0){ // only bounce if the ball is moving towards the paddle to prevent multiple bounces
                if(abs(ball.xSpeed) < SPEED_CAP) { // Caps the speed 
                    ball.xSpeed *= -1.1; // increase the speed by 5% and invert the direction
                }
                else { // if the speed is capped
                    ball.xSpeed = -ball.xSpeed; // just invert the direction
                }
                PlaySound(TEXT("sounds/hitPaddle.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
                
        }
    }
    // left paddle
    if(ball.x - ball.radius <= paddleLeft.x + paddleLeft.width && ball.x + ball.radius > paddleLeft.x - paddleLeft.width) { // if the ball.x is within the paddle.x range
        if(ball.y + ball.radius >= paddleLeft.y - paddleLeft.height && ball.y - ball.radius <= paddleLeft.y + paddleLeft.height) { // if the ball.y is within the paddle.y range
            // Bounce ball
            if(ball.xSpeed < 0){ // only bounce if the ball is moving towards the paddle to prevent multiple bounces
                if(abs(ball.xSpeed) < SPEED_CAP) { // Caps the speed
                    ball.xSpeed *= -1.1; // increase the speed by 5% and invert the direction
                }
                else{ // if the speed is capped
                    ball.xSpeed = -ball.xSpeed; // just invert the direction
                }
                PlaySound(TEXT("sounds/hitPaddle.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
        }
    }
    // bottom wall
    if (ball.y + ball.radius >= 600) { 
        ball.ySpeed = -ball.ySpeed;
        PlaySound(TEXT("sounds/hitWall.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    // top wall
    if (ball.y - ball.radius <= 0) { 
        ball.ySpeed = -ball.ySpeed;
        PlaySound(TEXT("sounds/hitWall.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    // right wall 
    if(ball.x + ball.radius >= 800) { 
        scorePoint();
    }
    // left wall
    if(ball.x - ball.radius <= 0) { 
        scorePoint();
    }
}

void Game::paddleLeftMoveUp(){
    if(!paused && paddleLeft.y - paddleLeft.height> 0 && score[0] < MATCH_POINT && score[1] < MATCH_POINT){
        paddleLeft.y -= paddleLeft.speed;
        scored = false;
    }
}
void Game::paddleLeftMoveDown(){
    if(!paused && paddleLeft.y + paddleLeft.height < 600 && score[0] < MATCH_POINT && score[1] < MATCH_POINT){
        paddleLeft.y += paddleLeft.speed;
        scored = false;
    }
}
void Game::paddleRightMoveUp(){
    if(!paused && paddleRight.y - paddleRight.height > 0 && score[0] < MATCH_POINT && score[1] < MATCH_POINT){
        paddleRight.y -= paddleRight.speed;
        scored = false;
    }
}
void Game::paddleRightMoveDown(){
    if(!paused && paddleRight.y + paddleRight.height < 600 && score[0] < MATCH_POINT && score[1] < MATCH_POINT){
        paddleRight.y += paddleRight.speed;
        scored = false;
    }
}

void Game::resetGame() {
    PlaySound(TEXT("sounds/restart.wav"), NULL, SND_FILENAME | SND_ASYNC);
    ball.x = 400;
    ball.y = 300;
    ball.xSpeed = 2;
    ball.ySpeed = 2;
    paddleLeft.y = 300;
    paddleRight.y = 300;
    score [0] = 0;
    score [1] = 0;
    scored = true;
    paused = false;
}
void Game::scorePoint() {
    scored = true;
    if(ball.x + ball.radius >= 800) { // right wall 
        score[0]++;
        ball.xSpeed = 2;
        if(score[0] == MATCH_POINT) {
            PlaySound(TEXT("sounds/win.wav"), NULL, SND_FILENAME | SND_ASYNC);            
        }
        else {
            PlaySound(TEXT("sounds/pointScored.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
    }
    if(ball.x - ball.radius <= 0) { // left wall
        score[1]++;
        ball.xSpeed = -2;
        if(score[1] == MATCH_POINT) {
            PlaySound(TEXT("sounds/win.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        else{
            PlaySound(TEXT("sounds/pointScored.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
    }
    // randomize the ySpeed to be either -2 or 2
    ball.ySpeed = (rand() % 2) * 4 - 2;

    // set the ball and paddles to the center of the screen
    ball.x = 400;
    ball.y = 300;
    paddleLeft.y = 300;
    paddleRight.y = 300;
    cout<<"Score: "<<score[0]<<" - "<<score[1]<<endl;
}
void Game::pauseGame() {
    if(!scored) {
        paused = !paused;
        if(paused) {
            PlaySound(TEXT("sounds/pause.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        else {
            PlaySound(TEXT("sounds/unpause.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
    }
}