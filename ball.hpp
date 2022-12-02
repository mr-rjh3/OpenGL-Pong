
#ifndef BALL_HPP
#define BALL_HPP

#include <iostream>
#include "paddle.hpp"

using namespace std;

/* Ball class
 * Holds all information / methods for dealing with the ball
 */

class Ball {
    public:
        int radius;
        float x; // x position of center of ball
        float y; // y position of center of ball
        float xSpeed;
        float ySpeed;

};

#endif