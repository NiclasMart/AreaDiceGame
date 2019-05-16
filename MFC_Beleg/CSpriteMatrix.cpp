#include "stdafx.h"
#include "CSpriteMatrix.h"




CSpriteMatrix::CSpriteMatrix()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			preview_buff[i][j] = NULL;
			field_buff[i][j] = NULL;	
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

//Setzt den Status aller sich im Field Puffer befindlichen Felder auf FALS
void CSpriteMatrix::SetFieldState() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			field_buff[i][j]->state = FALSE;
		}
	}
	
}

//Zeichnet alle sich im Preview Puffer befindenden Felder
void CSpriteMatrix::DrawPrevBuff() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (preview_buff[i][j] != NULL) {
				preview_buff[i][j]->SetAlpha(0.5f);
			}

		}
	}
}

//Setzt beide Puffer zurück
void CSpriteMatrix::ResetBuff() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (preview_buff[i][j] != NULL) {
				if (preview_buff[i][j]->state == TRUE)
					preview_buff[i][j]->SetAlpha(0.0f);
				preview_buff[i][j] = NULL;
			}

		}
	}
	ResetFieldBuff();
	pt_field = NULL;
}

void CSpriteMatrix::ResetFieldBuff() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			field_buff[i][j] = NULL;
		}
	}
}


//Zeichnet den Feld Puffer
bool CSpriteMatrix::DrawFieldBuff() {

	bool success = FALSE;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (field_buff[i][j] != NULL) {
				field_buff[i][j]->SetAlpha(1.0f);
				field_buff[i][j]->state = FALSE;
				success = TRUE;
			}
		}
	}
	return success;

}

//Beide Puffer werden geladen
void CSpriteMatrix::SetBuff(CFieldSprite *field, int w1, int w2, int player_num) {

	bool valid_field_pos = TRUE;
	for (int n = 0; n < w1; n++) {							//schreibe die Felder der Würfelzahl entsprechend in eine Puffermatrix
		for (int m = 0; m < w2; m++) {
			int aux_var = helpfunc_1(m, field);
			if (((field + (12 * n)) - aux_var)->state == TRUE) {
				((field + (12 * n)) - aux_var)->SetSpriteNumber(0, player_num);
				preview_buff[n][m] = field_buff[n][m] = ((field + (12 * n)) - aux_var); 
			}
			else valid_field_pos = FALSE;
		}
	}
	if (!valid_field_pos) ResetFieldBuff();
}


void CSpriteMatrix::ResetState() {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_field[i][j].ResetState();
		}
	}
}


//Hilfsfunktionen für Vorschauanzeige, damit keine Elemente auserhalb des Vektors addressiert werden

int CSpriteMatrix::helpfunc_1(int n, CFieldSprite* field) {

	int x = field - &m_field[0][0];
	x = x % 12;
	if (n > x) return x;
	else return n;
}

