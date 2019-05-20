#include "stdafx.h"
#include "CFieldSprite.h"


CFieldSprite::CFieldSprite()
	:field_state(TRUE), field_playernum(-1), control_state(FALSE)
{
}


CFieldSprite::~CFieldSprite()
{
}

void CFieldSprite::SetState(bool state) {
	field_state = state;
}

bool CFieldSprite::GetState() {
	return field_state;
}

void CFieldSprite::SetPlayernum(int player) {
	field_playernum = player;
}

int CFieldSprite::GetPlayernum() {
	return field_playernum;
}


void CFieldSprite::SetControlState(bool state) {
	control_state = state;
}

bool CFieldSprite::GetControlState() {
	return control_state;
}
