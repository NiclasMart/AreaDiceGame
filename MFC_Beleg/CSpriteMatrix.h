#include "spritelib.h"
#pragma once
class CSpriteMatrix : public CSprite
{
public:
	
	CSpriteMatrix();
	~CSpriteMatrix();
	CSprite m_field[12][12];
	bool SearchField(CSprite* Sprite);
	void SetFieldState(CSprite* Sprite, bool state);


private:
	bool field_state[12][12];
	
};

