#ifndef BALL_HPP
#define BALL_HPP

#include <iostream>

using namespace std;

/* Ball class
 * Holds all information for dealing with the ball
 */
class Ball {
    public:
        Ball(){
            x = 400;
            y = 300;
            radius = 10;
            xSpeed = 2;
            ySpeed = 2;
        }
        int radius;
        float x; // x position of center of ball
        float y; // y position of center of ball
        float xSpeed;
        float ySpeed;
};
#endif