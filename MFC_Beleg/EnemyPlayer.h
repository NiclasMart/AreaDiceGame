#pragma once
#include "CFieldSprite.h"
#include "CSpriteMatrix.h"
#include <time.h>

class EnemyPlayer
{
public:
	EnemyPlayer();
	~EnemyPlayer();
	void EnemyTurn(CFieldSprite* field, CSpriteMatrix &Matrix, int round, int player_num, int w1, int w2);
	void ResetBuff();
	bool SearchPos();
	void SetField(CSpriteMatrix &Matrix, int round, int player_num, int w1, int w2);

protected:
	CFieldSprite* buff[144];
	int buff_num;
};

