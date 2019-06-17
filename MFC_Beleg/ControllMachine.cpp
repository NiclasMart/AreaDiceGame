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
	game_status[0] = game_status[1] = FALSE;
	block_size = 0;
	field_border[0] = field;
	field_border[1] = field + 143;
	player_points[0] = player_points[1] = 0;

}

ControllMachine::~ControllMachine()
{
}

//wird nach jedem gesetzten Feld gerufen, durchläuft gesammtes Spielfeld und gibt nach analyse Gewinner zurück oder FALSE wenn niemand gewonnen hat
bool ControllMachine::WinControll(CFieldSprite* field, int &winner) {

	ResetAll();
													
	for(int i = 0; i < 144; i++) {

		if (field->GetPlayernum() == 0) game_status[0] = TRUE;		//verhindert, dass in der ersten Runde bereits Sieger festgestellt wird, da nur eine Farbe auf dem Feld ist
		if (field->GetPlayernum() == 1) game_status[1] = TRUE;		//es muss von jeder Farbe mindestens ein Spielstein auf dem Feld sein, damit Winermittlung greift
		if (field->GetState() == FALSE) {							//wenn ein besetztes Feld gefunden wird, wird die Punktzahl des Spielers dem das Feld gehört um 1 erhöht
			player_points[field->GetPlayernum()]++;
		}

		if ((field->GetState() == TRUE) && (field->GetControlState() == FALSE)) {		//wenn das Feld frei ist, und noch nicht kontrolliert wurde, werden folgende Aktionen ausgeführt
			FieldControll(field);
			Analyze();
			ResetSearch();
		}
		field += 1;
	}

	if ((!game_status[0]) || (!game_status[1])) return FALSE;
	if ((player_points[0] > 72) || (player_points[1] > 72) || ((player_points[0] == 72) && (player_points[1] == 72))) {
		if (player_points[0] > 72) winner = 0;
		else if (player_points[1] > 72) winner = 1;
		else winner = 2;
		return TRUE;
	}

	else return FALSE;


	
}

//von einem gefundenen freien Feld werden rekursiv alle 4 angrenzenden Felder angesprungen, diese rufen wieder jeweils 4 Felder ...
void ControllMachine::FieldControll(CFieldSprite* field) {					


	if (field->GetState() == FALSE) {					//wenn erreichtes Feld ein bereits besetztes Feld ist ...
		player[field->GetPlayernum()] = TRUE;			//wird sich gemerkt, dass ein Feld des entsprechenden Spielers an die freie Fläche angrenzt
		return;
	}

	if (field->GetControlState() == TRUE) return;		//wenn das Feld bereits kontrolliert wurde, kehre zurück

	block_size++;										
	field->SetControlState(TRUE);						//Feld fird als kontrolliert markiert



	//Rekursiver Aufruf mit den 4 Adressen der angrenzendern 4 Felder
	//if Anweisungen verhindern anspringen von Adressen auserhalb des Spielfeldes und das Überspringen einer Spaltengrenze zur nächsten Spalte, obwohl nur eine Adresse erhöht wird
	if ((field != field_border[0]) && (field > (field - ((field - field_border[0]) % 12)))) FieldControll(field - 1);
	if ((field != field_border[1]) && (field < (field + (11 - ((field - field_border[0] )) % 12)))) FieldControll(field + 1);
	if (field >= (field_border[0] + 12)) FieldControll(field - 12); 
	if (field <= (field_border[1] - 12)) FieldControll(field + 12);
		
	return;
}



void ControllMachine::Analyze() {

	if ((player[0] == TRUE) && (player[1] == TRUE)) return;					//wenn gefundener Bereich von beiden Spielern belegt werden könnte, kehre zurück (Bereich wird verworfen)
	
	if (player[0]) player_points[0] += block_size;							//wenn nur ein Spieler an den Bereich angrenz gehören die Felder theoretisch bereits ihm und werden zu seinen Punkten
	else player_points[1] += block_size;									//hinzugerechnet

}

void ControllMachine::ResetSearch() {

	block_size = 0;
	player[0] = player[1] = FALSE;
}


void ControllMachine::ResetAll(){
	ResetSearch();
	player_points[0] = player_points[1] = 0;
	game_status[0] = game_status[1] = FALSE;
}