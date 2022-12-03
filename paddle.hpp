#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <iostream>

using namespace std;

/* Paddle class
 * Holds all information for dealing with the paddle
 */
class Paddle {
    public:
        Paddle(){
            y = 300;
            width = 10;
            height = 50;
            speed = 5;
        }
        int width;
        int height;
        float x; // x position of center of paddle
        float y; // y position of center of paddle
        float speed;
};
#endif