#include <GL/glut.h>

class textureLoader
{
    private:
        struct Image 
        {
            unsigned long sizeX;
            unsigned long sizeY;
            char *data;
        } ;

        static int ImageLoad(char *filename, Image *image);
        static Image* loadTexture(char *filename);

    public:
        static GLuint* BindTexturesToArray();
        enum TEXTURE_INDEXES
        {
            LEFT_PADDLE,
            RIGHT_PADDLE,
            BACKGROUND,
            
            TEXTURE_COUNT  //Used to find number of textures for the texture array
        };
};