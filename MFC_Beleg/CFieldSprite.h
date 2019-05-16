#pragma once
#include "spritelib.h"
class CFieldSprite :public CSprite
{
public:
	CFieldSprite();
	~CFieldSprite();
	bool state;
	void ResetState();

protected:
	
};

