#include "stdafx.h"
#include "CSpriteMatrix.h"


CSpriteMatrix::CSpriteMatrix()
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			field_state[i][j] = FALSE;
		}
	}

}


CSpriteMatrix::~CSpriteMatrix()
{
}


bool CSpriteMatrix::SearchField(CSprite* Sprite) {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (Sprite == &m_field[i][j]) {
				return field_state[i][j];
			}
		}
	}
}

void CSpriteMatrix::SetFieldState(CSprite* Sprite, bool state) {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (Sprite == &m_field[i][j]) {
				field_state[i][j] = state;
				return;
			}
		}
	}
	return;
}


