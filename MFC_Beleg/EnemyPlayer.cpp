#include "stdafx.h"
#include "EnemyPlayer.h"


EnemyPlayer::EnemyPlayer()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 144; i++) {
		buff[i] = NULL;
	}
	buff_num = 0;
}


EnemyPlayer::~EnemyPlayer()
{
}

void EnemyPlayer::ResetBuff() {
	for (int i = 0; i < 144; i++) {
		buff[i] = NULL;
	}
	buff_num = 0;
}


void EnemyPlayer::EnemyTurn(CFieldSprite* field, CSpriteMatrix &Matrix, int round, int player_num, int w1, int w2) {

	ResetBuff();
	

	for (int i = 0; i < 144; i++) {
		field += i;

		Matrix.ResetBuff();													
		Matrix.pt_field = field;												
		Matrix.SetBuff(field, w1, w2, player_num, round);
		if (!Matrix.valid_field_pos) Matrix.SetBuff(field, w2, w1, player_num, round);

		if (buff[1] != NULL) {

		}
		if (Matrix.valid_field_pos) {
			buff[buff_num++] = field;
		}
	}

	Matrix.ResetBuff();
	if (buff_num) SetField(Matrix, round, player_num, w1, w2);
}



void EnemyPlayer::SetField(CSpriteMatrix &Matrix, int round, int player_num, int w1, int w2) {

	int number = rand() % buff_num;
	int rand_rotation = rand() % 2;

	if (rand_rotation) {
		Matrix.SetBuff(buff[number], w1, w2, player_num, round);
		if (!Matrix.valid_field_pos) Matrix.SetBuff(buff[number], w2, w1, player_num, round);
	}
	else {
		Matrix.SetBuff(buff[number], w2, w1, player_num, round);
		if (!Matrix.valid_field_pos) Matrix.SetBuff(buff[number], w2, w1, player_num, round);
	}

	Matrix.DrawFieldBuff(player_num);
}
