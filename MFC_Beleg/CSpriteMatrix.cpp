#include "stdafx.h"
#include "CSpriteMatrix.h"


CSpriteMatrix::CSpriteMatrix()
{
	matrix_posx = 0;
	matrix_posy = 0;
}


CSpriteMatrix::~CSpriteMatrix()
{
}

void CSpriteMatrix::SetMatrixPos(int x, int y) {

	matrix_posx = x;
	matrix_posy = y;
}
