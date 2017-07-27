#include "DxLib.h"
#include "player.h"
#include "playershot.h"
#include "BaseUnit.h"
#include "background.h"
#include "BaseEnemy.h"
#include "player_sword.h"
#include "enemy.h"
#include "enemy_shot.h"
#include "grobal.h"
#include "scoreboard.h"


//������
void stage_Initialize() {
	PlaySoundFile("sozai\\BGM\\testBGM.wav", DX_PLAYTYPE_LOOP);
	background_Initialize();
	player_Initialize();
	playershot_Initialize();
	playersword_Initialize();
	enemy_Initialize();
	enemyshot_Initialize();
	scoreboard_Initialize();
}

//�������v�Z����
void stage_Update() {
	background_Update();
	player_Update();
	playershot_Update();
	enemy_Update();
	enemyshot_Update();
}

//�`�悷��
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

//�I������������
void stage_Finalize() {
	StopSoundFile();
	enemyshot_Finalize();
	background_Finalize();
	player_Finalize();
	playershot_Finalize();
	playersword_Finalize();
	enemy_Finalize();
	enemyshot_Finalize();
	scoreboard_Finalize();
}
