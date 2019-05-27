#include "stdafx.h"
#include "CFieldSprite.h"


CFieldSprite::CFieldSprite()
	:field_state(TRUE), field_playernum(-1), control_state(FALSE)
{
}


CFieldSprite::~CFieldSprite()
{
}

//Setzt Status des Feldes (bereits gesetzt oder noch nicht)
void CFieldSprite::SetState(bool state) {
	field_state = state;
}

bool CFieldSprite::GetState() {
	return field_state;
}

//Setzt die Spielernummer des Feldes (welchem Spieler das Feld gehört)
void CFieldSprite::SetPlayernum(int player) {
	field_playernum = player;
}

int CFieldSprite::GetPlayernum() {
	return field_playernum;
}

//Setzt Kontrollstatus (ob Feld bereits kontrolliert wurde)
void CFieldSprite::SetControlState(bool state) {
	control_state = state;
}

bool CFieldSprite::GetControlState() {
	return control_state;
}
