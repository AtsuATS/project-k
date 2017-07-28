#include "Dxlib.h"
#include "grobal.h"

int score_board;
int Red = GetColor(222, 41, 0);
int Green = GetColor(3, 142, 55);
int Yellow = GetColor(228, 228, 76);

//スコアボード初期化
void scoreboard_Initialize(void) {
	score_board = LoadGraph("sozai\\GF\\score_board.png");
}

//スコアボード描画
void scoreboard_Draw(void) {
	

	DrawGraph(550, 0, score_board, TRUE);
	if (player.hp > 50) DrawBox(575, 150, hp_g, 175, Green, TRUE);
	if (player.hp <= 50 && player.hp > 20) DrawBox(575, 150, hp_g, 175, Yellow, TRUE);
	if (player.hp <= 20) DrawBox(575, 150, hp_g, 175, Red, TRUE);

	DrawFormatString(650, 10, GetColor(255, 255, 255), "TIME %d", t);
	DrawFormatString(650, 50, GetColor(0, 0, 255), "SCORE %d", score);
	DrawFormatString(650, 90, GetColor(0, 255, 0), "HP %d", player.hp);
}

//解放
void scoreboard_Finalize(void) {
	DeleteGraph(score_board);
}