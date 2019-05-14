#include "stdafx.h"
#include "CSpriteMatrix.h"




CSpriteMatrix::CSpriteMatrix()
{

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			/*field_state[i][j] = FALSE;*/

			/*if ((i < 6) && (j < 6)) {*/
				preview_buff[i][j] = NULL;
				field_buff[i][j] = NULL;
			/*}*/
		}
	}
	pt_field = NULL;
}


CSpriteMatrix::~CSpriteMatrix()
{
}


//bool CSpriteMatrix::GetFieldState(CFieldSprite* Sprite) {
//
//	//for (int i = 0; i < 12; i++) {
//	//	for (int j = 0; j < 12; j++) {
//	//		if (Sprite == &m_field[i][j]) {
//	//			return field_state[i][j];
//	//		}
//	//	}
//	//}
//}

void CSpriteMatrix::SetFieldState() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			field_buff[i][j]->state = FALSE;
		}
	}
	
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
				if (preview_buff[i][j]->state == TRUE)
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
				field_buff[i][j]->state = FALSE;
			}
		}
	}

}

void CSpriteMatrix::SetBuff(CFieldSprite *field, int w1, int w2, int player_num) {

	for (int n = 0; n < w1; n++) {							//schreibe die Felder der Würfelzahl entsprechend in eine Puffermatrix
		for (int m = 0; m < w2; m++) {
			if (((field + (12 * n)) - m)->state == TRUE) {
				((field + (12 * n)) - m)->SetSpriteNumber(0, player_num);
				preview_buff[n][m] = field_buff[n][m] = ((field + (12 * n)) - m);
				 
			}
		}
	}
}

