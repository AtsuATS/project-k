#include "DxLib.h"
#include "BaseUnit.h"
#include "playershot.h"
#include "define.h"

BaseShot playershot[PMAXSHOT];
int playershot_GF;

void createPlayerShot(float px, float py) {
	for (int i = 0; i < PMAXSHOT; i++) {
		if (playershot[i].flag == 0) {
			playershot[i].x = px;
			playershot[i].y = py;
			playershot[i].speed = 5;
			playershot[i].flag = 1;
			playershot[i].power = 1;
			return;
		}
	}
}

//初期化
void playershot_Initialize() {
	playershot_GF = LoadGraph("GF\\shot.png");
}

//動きを計算する
void playershot_Update() {
	for (int i = 0; i < PMAXSHOT; i++) {
		if (playershot[i].flag == 1) {
			playershot[i].y -= playershot[i].speed;
		}

		if (playershot[i].y <= -10) {
			playershot[i].flag = 0;
		}
	}

}

//描画する
void playershot_Draw() {
	for (int i = 0; i < PMAXSHOT; i++) {
		if (playershot[i].flag == 1) {
			DrawRotaGraph(playershot[i].x, playershot[i].y, 1, 0, playershot_GF, TRUE);
		}
		
	}
}

//終了処理をする
void playershot_Finalize() {
	DeleteGraph(playershot_GF);
}