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
	valid_field_pos = FALSE;
}


CSpriteMatrix::~CSpriteMatrix()
{
}


//Setzt den Status aller sich im Field Puffer befindlichen Felder auf FALSE
void CSpriteMatrix::SetFieldState() {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			field_buff[i][j]->SetState(FALSE);
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

//Setzt beide Puffer zur�ck
void CSpriteMatrix::ResetBuff() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (preview_buff[i][j] != NULL) {
				if (preview_buff[i][j]->GetState() == TRUE)
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
bool CSpriteMatrix::DrawFieldBuff(int player) {

	if (valid_field_pos) {								//wenn Position erlaubt, kann das Feld gesetzt werden
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (field_buff[i][j] != NULL) {
					field_buff[i][j]->SetAlpha(1.0f);
					field_buff[i][j]->SetState(FALSE);
					field_buff[i][j]->SetPlayernum(player);
				}
			}
		}
	}
	return valid_field_pos;

}


//Beide Puffer werden geladen
void CSpriteMatrix::SetBuff(CFieldSprite *field, int w1, int w2, int player_num) {

	valid_field_pos = TRUE;
	for (int n = 0; n < w1; n++) {														//schreibe die Felder der W�rfelzahl entsprechend in eine Puffermatrix
		for (int m = 0; m < w2; m++) {													//Hilfsfunktionen berechnen Werte so, dass zu setzendes Feld nicht aus dem Spielfeld herausragt
			int aux_var1 = helpfunc_1(m, field);
			int aux_var2 = helpfunc_2(n, field);
			if (((field + (12 * aux_var2)) - aux_var1)->GetState() == TRUE) {
				((field + (12 * aux_var2)) - aux_var1)->SetSpriteNumber(0, player_num);
				preview_buff[n][m] = field_buff[n][m] = ((field + (12 * aux_var2)) - aux_var1); 
			}
			else valid_field_pos = FALSE;
		}
	}
}

//setzt state f�r das gesammte spielfeld zurr�ck
void CSpriteMatrix::ResetState() {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_field[i][j].SetState(TRUE);
		}
	}
}


//Hilfsfunktionen f�r Vorschauanzeige, damit keine Elemente auserhalb des Vektors addressiert werden
int CSpriteMatrix::helpfunc_1(int m, CFieldSprite* field) {

	int x = field - &m_field[0][0];			//Position des Feldes in Matrix (Differenz erste Adress zu momentaner Adresse)
	x = x % 12;								//Berechnung wie viele Felder noch bis zum �berschreiten der Reihe (bzw. Spalte)
	if (m > x) {							//falls gew�rfelte Zahl m gr��er als maximale Zeilenl�ge x, wird x zur�ck gegeben
		valid_field_pos = FALSE;			//an diese Position darf das Feld dann nicht plaziert werden, da es aus der Matrix herausragt
		return x;
	}						
	else return m;
}

int CSpriteMatrix::helpfunc_2(int n, CFieldSprite* field) {

	int x = (field + (12 * n)) - &m_field[11][11];			//Position des Feldes in (negativ wenn in Matrix, Positiv wenn au�erhalb der Matrix) 
	if (x > 0) {											//falls Feld au�erhalb liegen w�rde, wird n das letzte zul�ssige n zur�ck gegeben
		valid_field_pos = FALSE;						//an diese Position darf das Feld dann nicht plaziert werden, da es aus der Matrix herausragt
		return n - ((x /= 12) + 1);
	}
	else return n;
}


//Kontrolliert ob ein Spieler gewonnen hat -> hat ein Spieler mehr als die H�lfte aller Felder, hat er gewonnen
bool CSpriteMatrix::CheckWin() {

	int punkte[2] = { 0 };
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (m_field[i][j].GetState() == FALSE) {					//wenn dasentsprechende Feld belegt ist, wird die punkteanzahl des Spielers dem das Feld geh�rt um 1 erh�ht
				punkte[m_field[i][j].GetPlayernum()]++;
			}
			if ((punkte[0] > 72) || (punkte[1] > 72)) return TRUE;
		}
	}
	return FALSE;
}