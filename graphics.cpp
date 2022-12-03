#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL_A/glfw.h>
#include <math.h>
#include <iostream>

#include "game.hpp"

using namespace std;

    // TODO: Sound effects
    // TODO: Better colors / graphics
    // TODO: AI?
    // TODO: Scoreboard


GLsizei minWidth = 800, minHeight = 600; // minimum window size
bool leftUp = false, leftDown = false, rightUp = false, rightDown = false; // booleans for key presses
Game game; // create a game object

void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE);  // GLUT_DOUBLE for double frame buffer
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(minWidth, minHeight);
	glutCreateWindow("Pong");
    glClearColor(0.0, 0.0, 0.0, 0.0); // set background color to gray
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, minWidth, minHeight, 0.0); // set top left as origin
}

void circlePlotPoints(GLint x, GLint y, GLint radius) {
	glBegin(GL_LINE_LOOP); // outline of circle
	for (int i = 0; i < 360; i++) {
		float degInRad = i*3.14159/180;
		glVertex2f(cos(degInRad)*radius + x, sin(degInRad)*radius + y);
	}
	glEnd();
	glFlush( );
			
}
void circleFillPoints(GLint x, GLint y, GLint radius) {
    glBegin(GL_POLYGON); // outline of circle
    for (int i = 0; i < 360; i++) {
        float degInRad = i*3.14159/180;
        glVertex2f(cos(degInRad)*radius + x, sin(degInRad)*radius + y);
    }
    glEnd();
    glFlush( );       
}
void squareFill(GLint x, GLint y, GLint width, GLint height) {
    glBegin(GL_QUADS);
    glVertex2i(x - width, y + height); // top left
    glVertex2i(x + width, y + height); // top right
    glVertex2i(x + width, y - height); // bottom right
    glVertex2i(x - width, y - height); // bottom left
    glEnd();
    glFlush( );
}
void squareOutline(GLint x, GLint y, GLint width, GLint height) {
    glBegin(GL_LINE_LOOP);
    glVertex2i(x - width, y + height); // top left
    glVertex2i(x + width, y + height); // top right
    glVertex2i(x + width, y - height); // bottom right
    glVertex2i(x - width, y - height); // bottom left
    glEnd();
    glFlush( );
}

void drawBall(Ball ball) {

    // Draw the ball
    glColor3f(1, 1, 1);

    circleFillPoints(ball.x, ball.y, ball.radius);

    // Draw the ball's outline
    glColor3f(1, 1, 1);
    glPointSize(2); // set point size to 2
    glLineWidth(2); // set line width to 2 pixel
    circlePlotPoints(game.ball.x, game.ball.y, game.ball.radius);
}
void drawPaddle(Paddle paddle){
    // Draw the paddle
    glColor3f(1, 1, 1);
    squareFill(paddle.x, paddle.y, paddle.width, paddle.height);

    // Draw the paddle's outline
    glColor3f(1, 1, 1);
    glPointSize(2); // set point size to 2
    glLineWidth(2); // set line width to 2 pixel
    squareOutline(paddle.x, paddle.y, paddle.width, paddle.height);
    
}
void drawGame() {
    // draw all game objects
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

    // draw the paddles
    drawPaddle(game.paddleLeft);
    drawPaddle(game.paddleRight);

    // draw the ball
    drawBall(game.ball);

	glFlush(); // Process all OpenGL routines as quickly as possible.
	glutSwapBuffers(); // Swap front and back buffers
}

void idle() {
    // called every frame

    // cout<<"x: "<<game.ball.x<<" y: "<<game.ball.y<<" xSpeed: "<<game.ball.xSpeed<<" ySpeed: "<<game.ball.ySpeed<<endl;
    // cout<<leftUp<<" "<<leftDown<<" "<<rightUp<<" "<<rightDown<<" "<<game.scored<<endl;
    // cout<<"Left: "<<game.paddleLeft.y<<" Right: "<<game.paddleRight.y<<endl;

    game.ballMove(); // move the ball
    game.checkCollision(); // check if the ball has hit a wall or paddle and change the direction if it has

    // move the paddles
    if(leftUp) { // Left paddle up
        game.paddleLeftMoveUp();
    }
    if(leftDown) { // Left paddle down
        game.paddleLeftMoveDown();
    }
    if(rightUp) { // Right paddle up
        game.paddleRightMoveUp();
    }
    if(rightDown) { // Right paddle down
        game.paddleRightMoveDown();
    }
    glutPostRedisplay();
	glFlush();
}

void keyboardFunc(unsigned char Key, int x, int y){
    switch(Key){
        case 'w':
            leftUp = true;
            break;
        case 's':
            leftDown = true;
            break;
        case 27: // escape key
            exit(0);
            break;
        case ' ':
            game.pauseGame();
            break;
        case 'r':
            game.resetGame();
            break;
        default:
            break;
    }
}
void keyboardUpFunc(unsigned char Key, int x, int y){
    switch(Key){
        case 'w':
            leftUp = false;
            break;
        case 's':
            leftDown = false;
            break;
        default:
            break;
    }
}
void specialFunc(int Key, int x, int y){
    switch(Key){
        case GLUT_KEY_UP:
            rightUp = true;
            break;
        case GLUT_KEY_DOWN:
            rightDown = true;
            break;
        default:
            break;
    }
}
void specialUpFunc(int Key, int x, int y){
    switch(Key){
        case GLUT_KEY_UP:
            rightUp = false;
            break;
        case GLUT_KEY_DOWN:
            rightDown = false;
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0); // For Eclipse stdout debugging

	glutInit(&argc, argv);
	init();
	glutDisplayFunc(drawGame);
    glutKeyboardFunc(keyboardFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutSpecialFunc(specialFunc);
    glutSpecialUpFunc(specialUpFunc);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}