#include "stdafx.h"
#include "CSpriteMatrix.h"


CSpriteMatrix::CSpriteMatrix()
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			field_state[i][j] = FALSE;

			if ((i < 6) && (j < 6)) {
				preview_buff[i][j] = NULL;
				field_buff[i][j] = NULL;
			}
		}
	}
	pt_field = NULL;
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

void CSpriteMatrix::DrawPrevBuff() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (preview_buff[i][j] != NULL) {
				preview_buff[i][j]->SetAlpha(0.5f);
			}

		}
	}
}

void CSpriteMatrix::ResetBuff() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (preview_buff[i][j] != NULL) {
				preview_buff[i][j]->SetAlpha(0.0f);
				preview_buff[i][j] = NULL;
				field_buff[i][j] = NULL;
			}

		}
	}
	pt_field = NULL;
}


void CSpriteMatrix::DrawFieldBuff() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (field_buff[i][j] != NULL) {
				field_buff[i][j]->SetAlpha(1.0f);
			}
		}
	}

}

