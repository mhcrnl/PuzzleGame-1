#include "PuzzleTable.hpp"

PuzzleTable::PuzzleTable(GLubyte* rawChunk, int width, int height, int depth,int tableSize)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->tableSize = tableSize;

	puzzle = new PuzzleChunk*[tableSize];

	for(int i = 0; i < tableSize ; ++i)
		puzzle[i] = static_cast<PuzzleChunk*> (::operator new (sizeof(PuzzleChunk[tableSize])));

	int stepW = (int)(width/tableSize);
	int stepH = (int)(height/tableSize);

	for(int i = 0; i < width ; i += stepW)
	{
		for(int j = 0; j < height ; j += stepH)
		{
			GLubyte* chunk = (GLubyte*)malloc(stepW * stepH * depth * sizeof(GLubyte));
			int chunkInd = 0;

			for(int iChunk = i ; iChunk < i + stepW ; ++iChunk)
			{
				for(int jChunk = j ; jChunk < j + stepH ; ++jChunk)
				{
					for(int z = 0 ; z < depth ; ++z)
					{
						chunk[ chunkInd++ ] =
								rawChunk[iChunk * height * depth + jChunk * depth + z];
					}
				}
			}
			puzzle[i/stepW][j/stepH] = PuzzleChunk(chunk, stepW, stepH, depth);
		}
	}

}

PuzzleChunk PuzzleTable::getChunkAt(int x, int y)
{
	return puzzle[x][y];
}
