#ifndef PUZZLETABLE_H_
#define PUZZLETABLE_H_
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "PuzzleChunk.hpp"

class PuzzleTable
{
public:
	PuzzleTable(GLubyte* rawChunk, int width, int height, int depth,int tableSize);
	PuzzleChunk* getChunkAt(int x, int y);
	PuzzleChunk* getChunkByIndex(int index);
private:
	PuzzleChunk** puzzle;
	int width;
	int height;
	int depth;
	int tableSize;
};
#endif
