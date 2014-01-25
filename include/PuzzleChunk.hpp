#ifndef PUZZLECHUNK_H_
#define PUZZLECHUNK_H_
#include "GL/freeglut.h"
#include "GL/gl.h"

class PuzzleChunk
{
public:
	//PuzzleChunk();
	PuzzleChunk(GLubyte* rawChunk, int width, int height, int depth, int index);
	int getChunkWidth();
	int getChunkHeight();
	GLubyte* getRawChunk();
	int getIndex();
	//void setIndex(int i);
private:
	GLubyte* rawChunk;
	int width;
	int height;
	int depth;
	int index;
};
#endif
