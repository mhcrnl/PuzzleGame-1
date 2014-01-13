#ifndef PUZZLECHUNK_H_
#define PUZZLECHUNK_H_
#include "GL/freeglut.h"
#include "GL/gl.h"

class PuzzleChunk
{
public:
	//PuzzleChunk();
	PuzzleChunk(GLubyte* rawChunk, int width, int height, int depth);
	int getChunkWidth();
	int getChunkHeight();
	GLubyte* getRawChunk();
private:
	GLubyte* rawChunk;
	int width;
	int height;
	int depth;
};
#endif
