#pragma once
#include "CFieldSprite.h"
class ControllMachine
{
public:
	ControllMachine(CFieldSprite* field);
	~ControllMachine();
	bool WinControll(CFieldSprite* field, int &winner);
	int player_points[2];					

protected:
	void FieldControll(CFieldSprite* field);
	void Analyze();
	void ResetSearch();
	void ResetAll();

	bool player[2];							//dokumentiert welche Spieler an einen Block aus freien Feldern angrenzende Felder haben (ob Felder von beiden oder nur von einem Spieler besetzt											werden können)								
	CFieldSprite* field_border[2];			//erstes Element gibt untere Adressgrenze, zweites Element gibt obere Adressgrenze
	bool game_status[2];
	int block_size;							//Zähler für Anzahl der aneinanderliegenden freien Felder
											//gibt an wie viele Felder ein Spieler theoretisch besitzt (alle markierten Felder + alle Felder, die nur von diesem Spieler markiert werden		können
};		



