#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <stdlib.h>
#include "PuzzleTable.hpp"
#include "PuzzleChunk.hpp"

const int startwinsize = 512; // Starting window width & height, in pixels

// Keyboard
const int ESCKEY = 27;        // ASCII value of escape character

// For image
const int img_width = 512;
const int img_height = 512;
GLubyte*** the_image;
GLubyte* image;

double zoom = 1.0;            // Pixel zoom, for both x & y
const double maxzoom = 10.0;
const double minzoom = -10.0;
PuzzleTable* table;

/* display function - code from:
     http://fly.cc.fer.hr/~unreal/theredbook/chapter01.html
This is the actual usage of the OpenGL library.
The following code is the same for any platform */
void renderFunction()
{
	   glClear(GL_COLOR_BUFFER_BIT);

	   // Draw image
	   glRasterPos2d( -1.0, -1.0);
	   PuzzleChunk pChunk = table->getChunkAt(1,1);
	   glDrawPixels(pChunk.getChunkWidth(), pChunk.getChunkHeight(), GL_RGB, GL_UNSIGNED_BYTE, pChunk.getRawChunk() );

	   glFlush();
}

void loadImage()
{
	FILE * file;
	file = fopen("/home/davidbo/Desktop/images.bmp","rb");

	image = (GLubyte*)malloc(sizeof(GLubyte) * img_width * img_height * 3 );
	fread(image, img_width * img_height * 3, 1, file);

	for( int i = 0; i < img_width * img_height ; ++i)
	{
		int ind = i * 3;

		char tmp = image[ind];
		image[ind] = image[ind + 2];
		image[ind + 2] = tmp;
	}

	table = new PuzzleTable(image, img_width, img_height, 3, 4);

	fclose( file );
}

/* Main method - main entry point of application
the freeglut library does the window creation work for us,
regardless of the platform. */
int main(int argc, char** argv)
{
	loadImage();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(startwinsize,startwinsize);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}



