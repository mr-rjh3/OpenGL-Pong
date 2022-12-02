
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
        Ball ball;
        Paddle paddleLeft;
        Paddle paddleRight;
        void ballMove(); // move the ball based on the speed values (called every frame unless the game is paused)
        void ballBounce(); // check if the ball has hit a wall or paddle and change the direction if it has (called every frame unless the game is paused)
};

#endif