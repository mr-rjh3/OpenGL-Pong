#include <stdio.h>
#include "game.hpp"
#include "graphics.hpp"
#include "textureLoader.hpp"

bool leftUp = false, leftDown = false, rightUp = false, rightDown = false; // booleans for key presses
Game game; // create a game object

#define MAX_FPS 120
#define ESC_KEY 27

enum MAIN_MENU_OPTIONS
{
    RESET_GAME,
    PAUSE_GAME,
    EXIT_GAME
};

enum TEXTURE_MENU
{
    DISABLE_TEXTURE,
    ENABLE_TEXTURE
};

void keyboardFunc(unsigned char Key, int x, int y)
{
    switch(Key){
        case 'w':
            leftUp = true;
            break;
        case 's':
            leftDown = true;
            break;
        case ESC_KEY: // escape key
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
        case GLUT_KEY_F1:
            graphics::isTexturesEnabled = !graphics::isTexturesEnabled;
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


void idle(int) 
{
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
    glutTimerFunc(1000/MAX_FPS, idle, 0); // call idle again after 1000/MAX_FPS milliseconds to maintain the frame rate
}

void drawGame() 
{
    graphics::drawGame(game);
}

void mainMenuFcn(GLint menuOption) {
	switch (menuOption) {
	case RESET_GAME:
        game.resetGame();
		break;
	case PAUSE_GAME:
        game.pauseGame();
        break;
    case EXIT_GAME:
        exit(1);
	}
	glutPostRedisplay();
}
void textureMenuFcn(GLint menuOption) {
    switch (menuOption) {
    case DISABLE_TEXTURE:
        graphics::isTexturesEnabled = false;
        break;
    case ENABLE_TEXTURE:
        graphics::isTexturesEnabled = true;
        break;
    }
    glutPostRedisplay();
}

void addMenu() {
	GLint textureMenuID;
    textureMenuID = glutCreateMenu(textureMenuFcn);
    glutAddMenuEntry("No Texture", DISABLE_TEXTURE);
    glutAddMenuEntry("Texture", ENABLE_TEXTURE);

	glutCreateMenu(mainMenuFcn); // Create main pop-up menu.
	glutAddMenuEntry("Restart \'r\'", RESET_GAME);
	glutAddMenuEntry("Pause \'Space\'", PAUSE_GAME);
	glutAddSubMenu("Textures \'Toggle: F1\'", textureMenuID);
    glutAddMenuEntry("Quit \'Esc\'", EXIT_GAME);
}




int main(int argc, char** argv) 
{
	setvbuf(stdout, NULL, _IONBF, 0); // For Eclipse stdout debugging

	glutInit(&argc, argv);
	graphics::init();

	glutDisplayFunc(drawGame);
    glutKeyboardFunc(keyboardFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutSpecialFunc(specialFunc);
    glutSpecialUpFunc(specialUpFunc);
    // add glut menu
    addMenu();
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutTimerFunc(1000/MAX_FPS, idle, 0); // call the idle function every 1/MAX_FPS seconds

	// glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}