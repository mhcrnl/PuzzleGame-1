#include "PuzzleTable.hpp"

PuzzleTable::PuzzleTable(GLubyte* rawImage, int width, int height, int depth,int tableSize)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->tableSize = tableSize;

	puzzle = new PuzzleChunk*[tableSize];

	for(int i = 0; i < tableSize ; ++i)
	{
		//puzzle[i] = new PuzzleChunk[tableSize];
		puzzle[i] = static_cast<PuzzleChunk*> (::operator new (sizeof(PuzzleChunk[tableSize])));
	}

	int stepW = (int)(width/tableSize);
	int stepH = (int)(height/tableSize);

	int chunkIndex = 0;

	for(int i = 0; i < width ; i += stepW)
	{
		for(int j = 0; j < height ; j += stepH)
		{
			GLubyte* rawChunk = (GLubyte*)malloc(stepW * stepH * depth * sizeof(GLubyte));
			int pixelInd = 0;

			for(int iChunk = i ; iChunk < i + stepW ; ++iChunk)
			{
				for(int jChunk = j ; jChunk < j + stepH ; ++jChunk)
				{
					for(int z = 0 ; z < depth ; ++z)
					{
						rawChunk[ pixelInd++ ] =
								rawImage[ ( iChunk * height * depth ) + ( jChunk  * depth + z ) ];
					}
				}
			}

			chunkIndex = (tableSize - 1 - i/stepW) * tableSize + j/stepH ;
			puzzle[ tableSize - 1 - i/stepW][j/stepH] = PuzzleChunk(rawChunk, stepW, stepH, depth, chunkIndex);

			//chunkIndex = (j/stepH) * tableSize + i/stepW;
//			puzzle[ tableSize - 1 -j/stepH ][ i/stepW ] =
//					PuzzleChunk(rawChunk, stepW, stepH, depth, chunkIndex++);
		}
	}
}

PuzzleChunk* PuzzleTable::getChunkAt(int x, int y)
{
	return &puzzle[x][y];
}

PuzzleChunk* PuzzleTable::getChunkByIndex(int index)
{
	for(int i = 0; i < tableSize ; ++i )
	{
		for(int j = 0; j < tableSize ; ++j)
		{
			if( puzzle[i][j].getIndex() == index )
				return &puzzle[i][j];
		}
	}
	return NULL;
}
