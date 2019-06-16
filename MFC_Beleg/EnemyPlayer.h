#pragma once
#include "CFieldSprite.h"
#include "CSpriteMatrix.h"
#include "spritelib.h"
#include <time.h>

class EnemyPlayer
{
public:
	EnemyPlayer();
	~EnemyPlayer();
	void EnemyTurn(CFieldSprite* field, CSpriteMatrix &Matrix, int round, int player_num, int w1, int w2, CClientDC* dc, CSpriteList &list);
	void ResetBuff();
	bool SearchPos();
	void SetField(CSpriteMatrix &Matrix, int round, int player_num, int w1, int w2);
	

	/*void Test(CClientDC* dc, CSpriteList &list);*/
protected:
	CFieldSprite* buff[144];
	int buff_num;
};

