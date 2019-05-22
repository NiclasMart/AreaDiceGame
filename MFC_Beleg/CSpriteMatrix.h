#include "spritelib.h"
#include "CFieldSprite.h"
#pragma once
class CSpriteMatrix : public CSprite
{
public:
	
	CSpriteMatrix();
	~CSpriteMatrix();
	
	CFieldSprite m_field[12][12];
	CFieldSprite* pt_field;
	CFieldSprite *preview_buff[6][6], *field_buff[6][6];

	bool valid_field_pos;

	void SetBuff(CFieldSprite *field, int w1, int w2, int player_num);
	void SetFieldState();
	void DrawPrevBuff();
	bool DrawFieldBuff(int player);
	void ResetBuff();
	void ResetFieldBuff();
	void ResetState();
	bool CheckWin();
	void ResetControlState();

	int helpfunc_1(int m, CFieldSprite* field);
	int helpfunc_2(int n, CFieldSprite* field);
	
	


private:
	bool field_state[12][12];
	
};

