#include "stdafx.h"
#include "ControllMachine.h"

/*Grundlegende (vereinfachte) Logik des Algorithmus:
	-durchläuft nach jedem Gesetzten Feld die komplette Matrix
	-sobald ein Feld erreicht wird, welches noch nicht besetzt ist, wird ein Zähler (buff_num) um eins erhöht und das Feld wird als kontrolliert markiert
	-dann werden Rekursiv die vier angrenzenden Felder aufgerufen, wenn es sich um ein besetztes Feld handelt, wird vermerkt das dieser Spieler an die freie Fläche angrenzt
	-wenn es sich um ein noch nicht besetztes Feld handelt, wird dieses wieder Markiert und Zähler erhöht ... Rekursiver Aufruf der 4 angrenzenden Felder ...
	-somit wird die Anzahl aller mit dem ersten freien Feld verbundenen freien Felder ermittelt
	-sollte sich herausstellen, dass an die ermittelte Fläche an freien Feldern nur ein Spieler angrenzt, so wird diese Fläche ihm Zahlenmäßig angerechnet, da der andere Spieler die Felder nicht
	 besetzen kann
	-das ganze wird fortgeführt, bis ganze Matrix durchlaufen
	-sollte ein spieler durch addition aller seiner besetzten Felder und der Felder, die nur er besetzen kann über 72 kommen, wird er zum Sieger erklährt*/

ControllMachine::ControllMachine(CFieldSprite* field)
{
	
	player[0] = player[1] = FALSE;
	buff_num = 0;
	field_border[0] = field;
	field_border[1] = field + 143;
	field_number[0] = field_number[1] = 0;

}


ControllMachine::~ControllMachine()
{
}

bool ControllMachine::WinControll(CFieldSprite* field) {

	ResetAll();
													/*verhindert, dass in der ersten Runde bereits Sieg festgestellt wird, da nur eine Farbe auf dem Feld ist
																				es muss von jeder Farbe mindestens ein Spielstein auf dem Feld sein, damit Winermittlung greift*/
	for(int i = 0; i < 144; i++) {

		
		if (field->GetPlayernum() == 1) game_status = TRUE;
		if (field->GetState() == FALSE) {
			field_number[field->GetPlayernum()]++;
			
		}

		if ((field->GetState() == TRUE) && (field->GetControlState() == FALSE)) {
			FieldControll(field);
			AnalyzeBuff();
			ResetBuff();
		}
		field += 1;
	}

	if (!game_status) return FALSE;
	if ((field_number[0] > 72) || (field_number[1] > 72)) return TRUE;
	else return FALSE;


	
}

void ControllMachine::FieldControll(CFieldSprite* field) {

	if (field->GetState() == FALSE) {												//wenn erreichtes Feld ein bereits besetztes Feld ist ...
		player[field->GetPlayernum()] = TRUE;										//wird sich gemerkt, dass ein Feld des entsprechenden Spielers an die freie Fläche angrenzt
		return;
	}

	if (field->GetControlState() == TRUE) return;									//wenn das Feld bereits kontrolliert wurde, kehre zurück

	buff_num++;																		//Zähler für Anzahl der
	field->SetControlState(TRUE);

	//Rekursiver Aufruf mit den 4 Adressen der angrenzendern 4 Felder
	//if Anweisungen verhindern anspringen von Adressen auserhalb des Spielfeldes
	if ((field != field_border[0]) && (field > (field - ((field - field_border[0])) % 12))) FieldControll(field - 1);
	if ((field != field_border[1]) && (field < (field + (12 - ((field - field_border[0])) % 12)))) FieldControll(field + 1);
	if (field >= (field_border[0] + 12)) FieldControll(field - 12); 
	if (field <= (field_border[1] - 12)) FieldControll(field + 12);
		
	return;
}

void ControllMachine::AnalyzeBuff() {

	if ((player[0] == TRUE) && (player[1] == TRUE)) return;					//wenn gefundener Bereich von beiden Spielern belegt werden könnte, kehre zurück
	
	if (player[0]) field_number[0] += buff_num;
	else field_number[1] += buff_num;

}

void ControllMachine::ResetBuff() {

	buff_num = 0;
	player[0] = player[1] = FALSE;
}


void ControllMachine::ResetAll(){
	ResetBuff();
	field_number[0] = field_number[1] = 0;
	game_status = FALSE;
}