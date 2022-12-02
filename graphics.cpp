


#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>

#include "game.hpp"

using namespace std;

GLsizei minWidth = 800, minHeight = 600;
Game game;

void circlePlotPoints(GLint x, GLint y, GLint radius) {
	glBegin(GL_LINE_LOOP); // outline of circle
	for (int i = 0; i < 360; i++) {
		float degInRad = i*3.14159/180;
		glVertex2f(cos(degInRad)*radius + x, sin(degInRad)*radius + y);
	}
	glEnd();
	glFlush( );
			
}
void circlePlotPointsFill(GLint x, GLint y, GLint radius) {
	glBegin(GL_POLYGON); // filled circle
	for (int i = 0; i < 360; i++) { // 360 degree
		float degInRad = i*3.14159/180; // convert to radian
		glVertex2f(cos(degInRad)*radius + x, sin(degInRad)*radius + y);
	}
	glEnd();
	glFlush( );
}

void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE);  // GLUT_DOUBLE for double frame buffer
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(minWidth, minHeight);
	glutCreateWindow("Pong Riley Huston");
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, minWidth, minHeight, 0.0); // set top left as origin
}

void drawGame() {
    // draw the game
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

    // draw filled circle using openGL
    glColor3f(0, 0, 0);
    circlePlotPointsFill(game.ball.x, game.ball.y, game.ball.radius);
        
    // stroke outline of circle
    glColor3f(0, 0, 0); // black
    
    glPointSize(1); // set point size to 1
    glLineWidth(1); // set line width to 1 pixel
    circlePlotPoints(game.ball.x, game.ball.y, game.ball.radius);

    // draw the paddles
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(game.paddleLeft.x - game.paddleLeft.width, game.paddleLeft.y + game.paddleLeft.height); // top left
    glVertex2i(game.paddleLeft.x + game.paddleLeft.width, game.paddleLeft.y + game.paddleLeft.height); // top right
    glVertex2i(game.paddleLeft.x + game.paddleLeft.width, game.paddleLeft.y - game.paddleLeft.height); // bottom right
    glVertex2i(game.paddleLeft.x - game.paddleLeft.width, game.paddleLeft.y - game.paddleLeft.height); // bottom left
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(game.paddleRight.x - game.paddleRight.width, game.paddleRight.y + game.paddleRight.height); // top left
    glVertex2i(game.paddleRight.x + game.paddleRight.width, game.paddleRight.y + game.paddleRight.height); // top right
    glVertex2i(game.paddleRight.x + game.paddleRight.width, game.paddleRight.y - game.paddleRight.height); // bottom right
    glVertex2i(game.paddleRight.x - game.paddleRight.width, game.paddleRight.y - game.paddleRight.height); // bottom left
    glEnd();

	glFlush(); // Process all OpenGL routines as quickly as possible.
	glutSwapBuffers(); // Swap front and back buffers
}
void idle() {
    // called every frame
    game.ballMove();
    game.ballBounce();
    cout<<"x: "<<game.ball.x<<" y: "<<game.ball.y<<" xSpeed: "<<game.ball.xSpeed<<" ySpeed: "<<game.ball.ySpeed<<endl;
    glutPostRedisplay();
	glFlush();
}

void keyboardFunc(unsigned char Key, int x, int y){
        // TODO add more with arrow keys idk why it doesn't work also make it less janky
    switch(Key){
        case 'w':
            game.paddleLeft.y -= 10;
            break;
        case 's':
            game.paddleLeft.y += 10;
            break;
        case 'i':
            game.paddleRight.y -= 10;
            break;
        case 'k':
            game.paddleRight.y += 10;
            break;
        default:
            break;
    }
    glutPostRedisplay();
	glFlush();

}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0); // For Eclipse stdout debugging
	setvbuf(stderr, NULL, _IONBF, 0);
    game.ball.x = 400;
    game.ball.y = 300;
    game.ball.radius = 10;
    game.ball.xSpeed = 1;
    game.ball.ySpeed = 1;

    game.paddleLeft.x = 100;
    game.paddleLeft.y = 300;
    game.paddleLeft.width = 10;
    game.paddleLeft.height = 100;

    game.paddleRight.x = 700;
    game.paddleRight.y = 300;
    game.paddleRight.width = 10;
    game.paddleRight.height = 100;


	glutInit(&argc, argv);
	init();
	glutDisplayFunc(drawGame);
	// glutReshapeFunc(winReshapeFcn);
	// glutMouseFunc(mouseActionFcn);
    glutKeyboardFunc(keyboardFunc);
	glutIdleFunc(idle);
	// glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();


	return 0;
}