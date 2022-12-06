#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "paddle.hpp"
#include "ball.hpp"

using namespace std;

/* Game class
 * Holds all information / methods for dealing with the game logic
 */
class Game {

    public:
        Game(){ // constructor
            // set the initial score to 0
            score[0] = 0;
            score[1] = 0;
            // Set speed cap for the ball
            SPEED_CAP = 15; 
            // Set the boolean values
            scored = true; // True so we can start the game with the ball in the middle of the screen not moving
            paused = false;
            // set the initial paddle positions (Couldn't put this in paddle constructor due to default constructor issues)
            paddleLeft.x = 20;
            paddleRight.x = 780;
            // set the match point
            MATCH_POINT = 5;
        }
        int MATCH_POINT;
        Ball ball;
        Paddle paddleLeft;
        Paddle paddleRight;
        bool paused; // true if the game is paused
        bool scored; // true if the ball has been scored
        int score[2]; // score[0] is the score for the left paddle, score[1] is the score for the right paddle
        int SPEED_CAP; // the maximum speed the ball can reach

        void ballMove(); // move the ball based on the speed values (called every frame unless the game is paused)
        void checkCollision(); // check if the ball has hit a wall or paddle and change the direction if it has (called every frame unless the game is paused)

        void leftPaddleBounce(); // changes the ySpeed of the ball based on the distance from the center of the paddle (called when the ball hits the left paddle)
        void rightPaddleBounce(); // changes the ySpeed of the ball based on the distance from the center of the paddle (called when the ball hits the right paddle)

        void paddleLeftMoveUp(); // move the paddle based on the speed (called when the user presses a key)
        void paddleLeftMoveDown(); // move the paddle based on the speed (called when the user presses a key)
        void paddleRightMoveUp(); // move the paddle based on the speed (called when the user presses a key)
        void paddleRightMoveDown(); // move the paddle based on the speed (called when the user presses a key)

        void resetGame(); // reset the game to the starting state (called when the game is over)
        void scorePoint(); // check if the ball has hit a wall and increase the score if it has (called every frame unless the game is paused)
        void pauseGame(); // pause the game (called when the user presses the space bar)
};
#endif