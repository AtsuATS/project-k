#include "DxLib.h"
#include "player.h"
#include "playershot.h"
#include "BaseUnit.h"
#include "background.h"
#include "BaseEnemy.h"
#include "enemy.h"
#include "enemy_shot.h"
#include "grobal.h"

//初期化
void stage_Initialize() {
	background_Initialize();
	player_Initialize();
	playershot_Initialize();
	enemy_Initialize();
	enemyshot_Initialize();
}

//動きを計算する
void stage_Update() {
	background_Update();
	player_Update();
	playershot_Update();
	enemy_Update();
	enemyshot_Update();
}

//描画する
void stage_Draw() {
	background_Draw();
	playershot_Draw();
	player_Draw();
	enemy_Draw();
	enemyshot_Draw();
}

//終了処理をする
void stage_Finalize() {
	enemyshot_Finalize();
	background_Finalize();
	player_Finalize();
	playershot_Finalize();
	enemy_Finalize();
	enemyshot_Finalize();

}
