#include "spritelib.h"
#pragma once
class CSpriteMatrix : public CSprite
{
public:
	
	CSpriteMatrix();
	~CSpriteMatrix();
	CSprite m_field[12][12], transparent_field[12][12];
	CSprite* pt_field;
	CSprite *preview_buff[6][6], *field_buff[6][6];

	bool SearchField(CSprite* Sprite);
	void SetFieldState(CSprite* Sprite, bool state);
	void DrawPrevBuff();
	void DrawFieldBuff();
	void ResetBuff();
	

	struct {
		CSprite* Sprit;
	
	};


private:
	bool field_state[12][12];
	
};

