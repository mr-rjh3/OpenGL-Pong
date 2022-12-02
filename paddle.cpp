

#include "paddle.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

void Paddle::moveUp() {
    y += speed;
}
void Paddle::moveDown() {
    y -= speed;
}
