#include "Dxlib.h"
#include "grobal.h"

int score_board;
int Red = GetColor(222, 41, 0);
int Green = GetColor(3, 142, 55);
int Yellow = GetColor(228, 228, 76);

//スコアボード初期化
void scoreboard_Initialize(void) {
	score_board = LoadGraph("GF\\score_board.png");
}

//スコアボード描画
void scoreboard_Draw(void) {
	

	DrawGraph(550, 0, score_board, TRUE);
	if (player.hp > 50) DrawBox(575, 110, hp_g, 135, Green, TRUE);
	if (player.hp <= 50 && player.hp > 20) DrawBox(575, 110, hp_g, 135, Yellow, TRUE);
	if (player.hp <= 20) DrawBox(575, 110, hp_g, 135, Red, TRUE);
	DrawBox(575, 185, mp_g, 205, Green, TRUE);
	DrawBox(640, 260, 775, 275, Red, TRUE);
	DrawBox(640, 260, bomb2_g, 275, Green, TRUE);

	if (enemy[53].flag == 1) {
		DrawFormatString(20, 0, GetColor(255, 255, 255), "BOSS-HP:%d", enemy[53].hp);
		DrawBox(120, 0, boss_hp, 15, Red, TRUE);
	}

	DrawFormatString(580, 40, GetColor(0, 0, 255), "SCORE %d", score);
	DrawFormatString(580, 80, GetColor(0, 255, 0), "HP %d", player.hp);
	DrawFormatString(580, 160, GetColor(255, 255, 255), "MP %d", player.mp);
	DrawFormatString(580, 215, GetColor(255, 255, 255), "Bomb type");
	DrawFormatString(580, 550, GetColor(255, 255, 255), "bombmagnification:%d", bombmagnification);

	if(player.type_bomb==1)DrawFormatString(580, 240, GetColor(255, 0, 0), "Bomb 1", player.mp);
	else DrawFormatString(580, 240, GetColor(255, 255,255), "Bomb 1", player.mp);
	if(player.type_bomb==2)DrawFormatString(580, 260, GetColor(255, 0, 0), "Bomb 2", player.mp);
	else DrawFormatString(580, 260, GetColor(255, 255, 255), "Bomb 2", player.mp);
	if(player.type_bomb==3)DrawFormatString(580, 280, GetColor(255, 0, 0), "Bomb 3", player.mp);
	else DrawFormatString(580, 280, GetColor(255, 255, 255), "Bomb 3", player.mp);

	if (bombflag[0] == 2) 
		DrawFormatString(650, 260, GetColor(255, 255, 255), "now filling...");

}

//解放
void scoreboard_Finalize(void) {
	DeleteGraph(score_board);
}