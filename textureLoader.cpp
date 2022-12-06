#include "textureLoader.hpp"

//C headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/*
These are C code functions because, HBF wrote them this way.
They use Malloc,fopen, printf and other stuff C++ programs 
shouldn't use. Maybe change later. Maybe...
*/

int textureLoader::ImageLoad(char *filename, Image *image)
{
    FILE *file;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)

	char temp; // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}

	// read the height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}

	size = image->sizeX * image->sizeY * 3;

	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i = 0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	return 1;
}

textureLoader::Image* textureLoader::loadTexture(char *filename)
{
	Image *image = (Image *) malloc(sizeof(Image));
	if (image == NULL) {
		printf("Error allocating space for image\n");
		exit(0);
	}
	if (!ImageLoad(filename, image)) {
        printf("Error creating Image\n");
		exit(1);
	}
	return image;
}

GLuint* textureLoader::BindTexturesToArray()
{
    //Create texture array
    GLuint* textureArray = new GLuint[TEXTURE_COUNT];

    //Generate texture names
    glGenTextures(TEXTURE_COUNT, textureArray);

    //Load in left paddle
    Image* image = loadTexture("images/LeftPaddle.bmp");
	glBindTexture(GL_TEXTURE_2D, textureArray[LEFT_PADDLE]);
    std::cout << "Left Paddle\n";
    std::cout << image->sizeX << "\n";
    std::cout << image->sizeY << "\n\n";

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    //Load in right paddle
    image = loadTexture("images/RightPaddle.bmp");
	glBindTexture(GL_TEXTURE_2D, textureArray[RIGHT_PADDLE]);
    std::cout << "Right Paddle\n";
    std::cout << image->sizeX << "\n";
    std::cout << image->sizeY << "\n\n";

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    //Load in background texture
    image = loadTexture("images/Background.bmp");
	glBindTexture(GL_TEXTURE_2D, textureArray[BACKGROUND]);
    std::cout << "Background\n";
    std::cout << image->sizeX << "\n";
    std::cout << image->sizeY << "\n\n";

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	//Unbind textures
	glBindTexture(GL_TEXTURE_2D, 0);

    return textureArray;
}
