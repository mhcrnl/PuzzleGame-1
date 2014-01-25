#include "PuzzleChunk.hpp"


PuzzleChunk::PuzzleChunk(GLubyte* rawChunk, int width, int height, int depth, int index)
{
	this->rawChunk = (GLubyte*) malloc(sizeof(GLubyte) * width * height * depth);
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->index = index;

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

int PuzzleChunk::getIndex()
{
	return index;
}

//void PuzzleChunk::setIndex(int index)
//{
//	this->index = index;
//}

GLubyte* PuzzleChunk::getRawChunk()
{
	return rawChunk;
}

