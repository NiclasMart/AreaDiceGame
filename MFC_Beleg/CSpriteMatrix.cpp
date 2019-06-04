#include "stdafx.h"
#include "CSpriteMatrix.h"




CSpriteMatrix::CSpriteMatrix()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			
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
			if (field_buff[i][j] != NULL) {
				field_buff[i][j]->SetAlpha(0.5f);
			}

		}
	}
}

//Setzt beide Puffer zurück
void CSpriteMatrix::ResetBuff() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (field_buff[i][j] != NULL) {
				if (field_buff[i][j]->GetState() == TRUE)
					field_buff[i][j]->SetAlpha(0.0f);
				field_buff[i][j] = NULL;
			}

		}
	}
	ResetFieldBuff();
	pt_field = NULL;
}

//Setzt den Feld Puffer zurück
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


//Puffer wird geladen
void CSpriteMatrix::SetBuff(CFieldSprite *field, int w1, int w2, int player_num, int round) {

	valid_field_pos = TRUE;
	for (int n = 0; n < w1; n++) {														//schreibe die Felder der Würfelzahl entsprechend in eine Puffermatrix
		for (int m = 0; m < w2; m++) {													//Hilfsfunktionen berechnen Werte so, dass zu setzendes Feld nicht aus dem Spielfeld herausragt
			int aux_var1 = helpfunc_1(m, field);
			int aux_var2 = helpfunc_2(n, field);
			CFieldSprite *pt_field = (field + (12 * aux_var2)) - aux_var1;

			if (pt_field->GetState() == TRUE) {											//wenn das entsprechende Feld frei ist, wird es auf den richtigen Spieler eingerichtet und in den Puffer
				pt_field->SetSpriteNumber(0, player_num);								//geschrieben
				field_buff[n][m] = pt_field;
			}
			else valid_field_pos = FALSE;												//wenn nur eines der Felder sich mit einem bereits gesetzten Feld überdeckt, wird die gesammte 
		}																				//Possitionierung als ungültig markiert
	}

	
	if (round < 3) {
		if (round == 1) StartPhaseRule(field, player_num);
		else 
			StartPhaseRule(field_buff[w1-1][w2-1], player_num);
		/*StartPhaseRule(field, player_num);*/
	}
	else RuleCheck(player_num);
	
}

//setzt state für das gesammte spielfeld zurrück
void CSpriteMatrix::ResetState() {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_field[i][j].SetState(TRUE);
		}
	}
}


//Hilfsfunktionen für Vorschauanzeige, damit keine Elemente auserhalb des Vektors addressiert werden
int CSpriteMatrix::helpfunc_1(int m, CFieldSprite* field) {

	int x = field - &m_field[0][0];			//Position des Feldes in Matrix (Differenz erste Adress zu momentaner Adresse)
	x = x % 12;								//Berechnung wie viele Felder noch bis zum Überschreiten der Reihe (bzw. Spalte)
	if (m > x) {							//falls gewürfelte Zahl m größer als maximale Zeilenläge x, wird x zurück gegeben
		valid_field_pos = FALSE;			//an diese Position darf das Feld dann nicht plaziert werden, da es aus der Matrix herausragt
		return x;
	}						
	else return m;
}

int CSpriteMatrix::helpfunc_2(int n, CFieldSprite* field) {

	int x = (field + (12 * n)) - &m_field[11][11];			//Position des Feldes in (negativ wenn in Matrix, Positiv wenn außerhalb der Matrix) 
	if (x > 0) {											//falls Feld außerhalb liegen würde, wird n das letzte zulässige n zurück gegeben
		valid_field_pos = FALSE;							//an diese Position darf das Feld dann nicht plaziert werden, da es aus der Matrix herausragt
		return n - ((x /= 12) + 1);
	}
	else return n;
}


//Controll State von allen Feldern wird zurück gesetzt
void CSpriteMatrix::ResetControlState() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_field[i][j].SetControlState(FALSE);
		}
	}
}


//Überprüft Regeln entsprechend ob an gewünschter Position überhaupt ein Feld gesetzt werden darf
void CSpriteMatrix::RuleCheck(int &player_num){
	bool connection = FALSE;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if ((field_buff[i][j] != NULL) && (field_buff[i][j] >= &m_field[1][0])) {
				CFieldSprite * pt1 = field_buff[i][j] - 12;

				if ((pt1->GetState() == FALSE) && (pt1->GetPlayernum() == player_num)) connection = TRUE;
			}
			if ((field_buff[i][j] != NULL) && (field_buff[i][j] <= &m_field[10][11])) {
				CFieldSprite * pt1 = field_buff[i][j] + 12;

				if ((pt1->GetState() == FALSE) && (pt1->GetPlayernum() == player_num)) connection = TRUE;
			}
			if ((field_buff[i][j] != NULL) && (field_buff[i][j] > (field_buff[i][j] - ((field_buff[i][j] - &m_field[0][0]) % 12)))) {
				CFieldSprite * pt1 = field_buff[i][j] - 1;

				if ((pt1->GetState() == FALSE) && (pt1->GetPlayernum() == player_num)) connection = TRUE;
			}
			if ((field_buff[i][j] != NULL) && (field_buff[i][j] < (field_buff[i][j] + (11 - ((field_buff[i][j] - &m_field[11][11])) % 12)))) {
				CFieldSprite * pt1 = field_buff[i][j] + 1;

				if ((pt1->GetState() == FALSE) && (pt1->GetPlayernum() == player_num)) connection = TRUE;
			}
			

		}
	}

	if (!connection) valid_field_pos = FALSE;
}


//Gesonderte reglung der ersten beiden Runden, da noch kein Feld zum ansetzen existiert
void CSpriteMatrix::StartPhaseRule(CFieldSprite* field, int player_num) {

	if ((player_num == 0) && (!(field == &m_field[0][11]))) valid_field_pos = FALSE;
	if ((player_num == 1) && (!(field == &m_field[11][0]))) 
		valid_field_pos = FALSE;

}

