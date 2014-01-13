#include "PuzzleChunk.hpp"
//
//PuzzleChunk::PuzzleChunk()
//{
//}

PuzzleChunk::PuzzleChunk(GLubyte* rawChunk, int width, int height, int depth)
{
	this->rawChunk = (GLubyte*) malloc(sizeof(GLubyte) * width * height * depth);
	this->width = width;
	this->height = height;
	this->depth = depth;

	for(int i = 0 ; i < width * height * depth ; ++i )
		this->rawChunk[i] = rawChunk[i];
}

int PuzzleChunk::getChunkWidth()
{
	return width;
}

int PuzzleChunk::getChunkHeight()
{
	return height;
}

GLubyte* PuzzleChunk::getRawChunk()
{
	return rawChunk;
}
