#include "DxLib.h"
#include "player.h"
#include "playershot.h"
#include "BaseUnit.h"
#include "background.h"
#include "BaseEnemy.h"
#include "playersword.h"
#include "enemy.h"
#include "enemyshot.h"
#include "grobal.h"
#include "scoreboard.h"
#include "bomb.h"


//初期化
void stage_Initialize() {
	background_Initialize();
	player_Initialize();
	playershot_Initialize();
	playersword_Initialize();
	enemy_Initialize();
	enemyshot_Initialize();
	scoreboard_Initialize();
}

//動きを計算する
void stage_Update() {
	background_Update();
	player_Update();
	playershot_Update();
	enemy_Update();
	enemyshot_Update();
	bomb_Update();
}

//描画する
void stage_Draw() {
	background_Draw();
	player_Draw();
	playershot_Draw();
	playersword_Draw();
	player_Draw();
	enemy_Draw();
	enemyshot_Draw();
	scoreboard_Draw();
}

//終了処理をする
void stage_Finalize() {
	background_Finalize();
	player_Finalize();
	playershot_Finalize();
	playersword_Finalize();
	enemyshot_Finalize();
	enemy_Finalize();
	scoreboard_Finalize();
}
