#include "spritelib.h"
#include "CFieldSprite.h"
#pragma once
class CSpriteMatrix : public CSprite
{
public:
	
	CSpriteMatrix();
	~CSpriteMatrix();
	CFieldSprite m_field[12][12]/*, transparent_field[12][12]*/;
	CFieldSprite* pt_field;
	CFieldSprite *preview_buff[6][6], *field_buff[6][6];

	/*bool GetFieldState(CFieldSprite* Sprite);*/
	void SetBuff(CFieldSprite *field, int w1, int w2, int player_num);
	/*CSprite* SearchField(CSpriteList *list, int mouse_x, int mouse_y, int &feld_x, int &feld_y);
	bool TestArea(int feld_x, int feld_y, int wuerfel_breite, int wuerfel_hoehe, int spieler);*/
	void SetFieldState();
	void DrawPrevBuff();
	void DrawFieldBuff();
	void ResetBuff();
	
	


private:
	bool field_state[12][12];
	
};

