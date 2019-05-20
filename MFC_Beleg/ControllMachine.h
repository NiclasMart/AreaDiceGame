#pragma once
#include "CFieldSprite.h"
class ControllMachine
{
public:
	ControllMachine(CFieldSprite* field);
	~ControllMachine();
	bool WinControll(CFieldSprite* field);

protected:
	void FieldControll(CFieldSprite* field);
	void AnalyzeBuff();
	void ResetBuff();
	void ResetAll();

	bool player[2];									//dokumentiert welche Spieler an einen Block aus freien Feldern angrenzende Felder haben (ob Felder von beiden oder nur von einem Spieler besetzt werden können)
	int field_number[2];							//gibt an wie viele Felder ein Spieler Theoretisch beseitzt (alle markierten Felder + alle Felder, die nur von diesem Spieler markiert werden können
	CFieldSprite* field_border[2];					//erstes Element gibt untere Adressgrenze, zweites Element gibt obere Adressgrenze
	/*CFieldSprite* control_buff[144];*/
	int buff_num;
};


