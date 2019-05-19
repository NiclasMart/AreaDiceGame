#pragma once
#include "spritelib.h"
class CFieldSprite :public CSprite
{
public:
	CFieldSprite();
	~CFieldSprite();
	
	void SetState(bool state);
	bool GetState();
	void SetPlayernum(int player);
	int GetPlayernum();

protected:
	bool field_state;
	int field_playernum;
};

