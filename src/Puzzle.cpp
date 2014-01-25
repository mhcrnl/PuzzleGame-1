#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "PuzzleTable.hpp"
#include "PuzzleChunk.hpp"

using namespace std;
using std::cerr;

const int startwinsize = 512; // Starting window width & height, in pixels
const int img_width = 512;
const int img_height = 512;
GLubyte* image;

const int tableSize = 4;
const int chunkSize = int(img_width / tableSize);
PuzzleTable* table;
PuzzleChunk* activeChunk;
double acX, acY;

void renderFunction()
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	int ind = 0;

	for(double i = 0.5, x = 0 ; i > -1.1 ; i-= double(2.0/tableSize), ++x)
	{
		for(double j = -1.0, y = 0; j < 1 ; j+= double(2.0/tableSize), ++y)
		{
			glRasterPos2d( j,i );
			PuzzleChunk* pChunk = table->getChunkByIndex(ind++);

			cout<< "scr x: " << j << " " << " scr y: " << i << " "
					<< " arr x:"<<  x << " arr y: "<<  y << " ind: "<< pChunk->getIndex() ;

			if( ( activeChunk && pChunk->getIndex() != activeChunk->getIndex() ) || !activeChunk)
				glDrawPixels( pChunk->getChunkWidth(), pChunk->getChunkHeight(), GL_RGB, GL_UNSIGNED_BYTE, pChunk->getRawChunk() );
		}
		cout<<endl;
	}

	cout<<endl;
	if(activeChunk != NULL)
	{
		glRasterPos2d(acX, acY);
		glDrawPixels( activeChunk->getChunkWidth(), activeChunk->getChunkHeight(),
				GL_RGB, GL_UNSIGNED_BYTE, activeChunk->getRawChunk() );
	}
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

	table = new PuzzleTable(image, img_width, img_height, 3, tableSize);

	fclose( file );
}

void mouseCallBack(int button, int state, int x, int y)
{
	if( GLUT_LEFT_BUTTON == button )
	{
		int chunkYInd = int(x/chunkSize);
		int chunkXInd = int(y/chunkSize);


		activeChunk = table->getChunkAt(chunkXInd, chunkYInd);
		cout<< "picked chunk at:" << chunkXInd << " " << chunkYInd << " index: " << activeChunk->getIndex() <<endl;

	}
}


void motionCallBack(int x, int y)
{
	if(activeChunk!= NULL)
	{
		acX = double(x)/startwinsize;
		acY = double(startwinsize-y)/startwinsize; //Invert mouse y (as its measured from top)
//		cout<< acX << "  " << acY <<endl;
		glutPostRedisplay();
	}
}

// idle
// The GLUT idle function
void idle()
{
   // Print OpenGL errors, if there are any (for debugging)
   if (GLenum err = glGetError())
   {
      cerr << "OpenGL ERROR: " << gluErrorString(err) << endl;
   }
}

/* Main method - main entry point of application
the freeglut library does the window creation work for us,
regardless of the platform. */
int main(int argc, char** argv)
{
	loadImage();
	activeChunk = NULL;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(startwinsize,startwinsize);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(renderFunction);
    glutMouseFunc(mouseCallBack);
    glutMotionFunc(motionCallBack);
    glutMainLoop();
    glutIdleFunc(idle);
    return 0;
}



