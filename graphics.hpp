#include <GL/glut.h>
#include "ball.hpp"
#include "paddle.hpp"
//#include <GL/gl.h>
//#include <GL_A/glfw.h>

class graphics
{
    private:
        static void circlePlotPoints(GLint x, GLint y, GLint radius);
        static void circleFillPoints(GLint x, GLint y, GLint radius);
        static void squareFill(GLint x, GLint y, GLint width, GLint height);
        static void squareOutline(GLint x, GLint y, GLint width, GLint height);
        static void drawBall(const Game& game);
        static void drawPaddle(const Paddle& paddle);

    public:
        static void init(void);
        static void drawGame(const Game& game);
};