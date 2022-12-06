#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL_A/glfw.h>
#include <math.h>
#include <iostream>
#include <time.h>

#include <windows.h>
#include <mmsystem.h>


#include "game.hpp"
#include "graphics.hpp"

using namespace std;

    // TODO: Better colors / graphics

GLsizei winWidth = 800, winHeight = 600; // minimum window size
int timeStart = time(NULL), timeEnd; // used for calculating the time between frames
int frameCount = 0; // used for calculating the time between frames

//Graphics functions-------------------------------------------------------------------------------------------------------------------------------
void graphics::init(void) 
{
	glutInitDisplayMode(GLUT_DOUBLE);  // GLUT_DOUBLE for double frame buffer
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Pong");
    glClearColor(0.0, 0.0, 0.0, 0.0); // set background color to gray
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, winHeight, 0.0); // set top left as origin
}

void graphics::circlePlotPoints(GLint x, GLint y, GLint radius) 
{
	glBegin(GL_LINE_LOOP); // outline of circle
	for (int i = 0; i < 360; i++) {
		float degInRad = i*3.14159/180;
		glVertex2f(cos(degInRad)*radius + x, sin(degInRad)*radius + y);
	}
	glEnd();
	glFlush( );
			
}
void graphics::circleFillPoints(GLint x, GLint y, GLint radius) 
{
    glBegin(GL_POLYGON); // outline of circle
    for (int i = 0; i < 360; i++) {
        float degInRad = i*3.14159/180;
        glVertex2f(cos(degInRad)*radius + x, sin(degInRad)*radius + y);
    }
    glEnd();
    glFlush( );       
}
void graphics::squareFill(GLint x, GLint y, GLint width, GLint height) 
{
    glBegin(GL_QUADS);
    glVertex2i(x - width, y + height); // top left
    glVertex2i(x + width, y + height); // top right
    glVertex2i(x + width, y - height); // bottom right
    glVertex2i(x - width, y - height); // bottom left
    glEnd();
    glFlush( );
}
void graphics::squareOutline(GLint x, GLint y, GLint width, GLint height) 
{
    glBegin(GL_LINE_LOOP);
    glVertex2i(x - width, y + height); // top left
    glVertex2i(x + width, y + height); // top right
    glVertex2i(x + width, y - height); // bottom right
    glVertex2i(x - width, y - height); // bottom left
    glEnd();
    glFlush( );
}
void renderText(GLint x, GLint y, const char *string) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(x, y);
    for (int i = 0; i < strlen(string); i++) {
        // Make font size very large
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

void graphics::drawBall(const Game& game) 
{
    // Draw the ball
    // red
    glColor3f(1.0, 1.2-fabs(game.ball.xSpeed/(float)game.SPEED_CAP), 1.2-fabs(game.ball.xSpeed/(float)game.SPEED_CAP));
    cout<<fabs((float)game.ball.xSpeed/(float)game.SPEED_CAP)<<endl;

    circleFillPoints(game.ball.x, game.ball.y, game.ball.radius);

    // Draw the ball's outline
    glColor3f(1.0, 1.2-fabs(game.ball.xSpeed/(float)game.SPEED_CAP), 1.0-fabs(game.ball.xSpeed/(float)game.SPEED_CAP));
    glPointSize(2); // set point size to 2
    glLineWidth(2); // set line width to 2 pixel
    circlePlotPoints(game.ball.x, game.ball.y, game.ball.radius);
}
void graphics::drawPaddle(const Paddle& paddle)
{
    // Draw the paddle
    glColor3f(1, 1, 1);
    squareFill(paddle.x, paddle.y, paddle.width, paddle.height);

    // Draw the paddle's outline
    glColor3f(1, 1, 1);
    glPointSize(2); // set point size to 2
    glLineWidth(2); // set line width to 2 pixel
    squareOutline(paddle.x, paddle.y, paddle.width, paddle.height);
    
}
void graphics::drawMiddleLine(){
    glColor3f(1, 1, 1);
    glPointSize(2); // set point size to 2
    glLineWidth(2); // set line width to 2 pixel
    glBegin(GL_LINES);
    for (int i = 0; i < winHeight; i += 20) {
        glVertex2i(winWidth/2, i);
        glVertex2i(winWidth/2, i + 10);
    }
    glEnd();
}

void graphics::drawGame(const Game& game) 
{
    // draw all game objects
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

    // draw dotted line down middle
    drawMiddleLine();

    // draw the paddles
    drawPaddle(game.paddleLeft);
    drawPaddle(game.paddleRight);

    // draw the ball
    drawBall(game);

    // draw the left score
    char leftScore[10];
    sprintf(leftScore, "%d", game.score[0]);
    renderText(winWidth/2 - 32, 30, leftScore);

    // draw the right score
    char rightScore[10];
    sprintf(rightScore, "%d", game.score[1]);
    renderText(winWidth/2 + 20, 30, rightScore);

    // draw winner on the winning side once someone reaches 10 points
    if (game.score[0] == game.MATCH_POINT) {
        renderText(winWidth/2 - 200, winHeight/2, "Player 1 Wins!");
        renderText(winWidth/2 - 200, winHeight/2 + 30, "Press 'r' to restart");
    }
    else if (game.score[1] == game.MATCH_POINT) {
        renderText(winWidth/2 + 50, winHeight/2, "Player 2 Wins!");
        renderText(winWidth/2 + 50, winHeight/2 + 30, "Press 'r' to restart");
    }

    if(game.paused){
        glColor3f(1, 1, 1);
        renderText(winWidth/2 - 32, winHeight/2, "PAUSED");
    }

	glFlush(); // Process all OpenGL routines as quickly as possible.
	glutSwapBuffers(); // Swap front and back buffers

    // calculate the frame rate
    frameCount++;
    timeEnd = time(NULL);
    if(timeEnd - timeStart >= 1) { // if a second has passed
        cout << "FPS: " << frameCount << endl;
        frameCount = 0;
        timeStart =  timeEnd;
    }
}