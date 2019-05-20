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
	void SetControlState(bool state);
	bool GetControlState();

protected:
	bool field_state;
	int field_playernum;
	bool control_state;
};

