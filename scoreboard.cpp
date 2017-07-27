#include "Dxlib.h"
#include "grobal.h"

int score_board;

//スコアボード初期化
void scoreboard_Initialize(void) {
	score_board = LoadGraph("sozai\\GF\\score_board.png");
}

//スコアボード描画
void scoreboard_Draw(void) {
	DrawGraph(550, 0, score_board, TRUE);
	DrawBox(550, hp_g, 600, 600, GetColor(228, 228, 76), TRUE);
	DrawFormatString(650, 10, GetColor(255, 255, 255), "TIME %d", t);
	DrawFormatString(650, 50, GetColor(0, 0, 255), "SCORE %d", score);
	DrawFormatString(650, 90, GetColor(0, 255, 0), "HP %d", player.hp);
}

//解放
void scoreboard_Finalize(void) {
	DeleteGraph(score_board);
}