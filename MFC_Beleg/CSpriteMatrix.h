#include "spritelib.h"
#pragma once
class CSpriteMatrix : public CSprite
{
public:
	
	CSpriteMatrix();
	~CSpriteMatrix();
	void SetMatrixPos(int x, int y);
	

private:
	int matrix_posx, matrix_posy;
	
};

