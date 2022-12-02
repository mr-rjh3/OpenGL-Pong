
#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <iostream>

using namespace std;


/* Paddle class
 * Holds all information / methods for dealing with the paddle
 */

class Paddle {
    public:
        int width;
        int height;
        float x; // x position of center of paddle
        float y; // y position of center of paddle
        float speed;

        void moveUp(); // move the paddle based on the speed (called when the user presses a key)
        void moveDown(); // move the paddle based on the speed (called when the user presses a key)
};

#endif