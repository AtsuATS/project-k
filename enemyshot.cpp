#include "DxLib.h"
#include "grobal.h"
#include "enemy_shot.h"
#include "enemy_act.h"
#include "BaseUnit.h"
#define _USE_MATH_DEFINES
#include <math.h>

Enemy_shot enemyshot[EMAXSHOT];
int enemyshot_GF1, enemyshot_GF2, enemyshot_GF3;

void createEnemyShot(float ex , float ey, int n, int p, int s, int t, double ang) { //nは弾の数,pはパターン,sはスピード,angは角度
	static int i = 1, m = 1;//角度を順番に与えるための変数
	for (int j = 0; j < n; j++) {
		if (enemyshot[j].flag == 0) {
			enemyshot[j].x = ex;
			enemyshot[j].y = ey;
			enemyshot[j].speed = s;
			enemyshot[j].flag = 1;
			enemyshot[j].type = t;
			enemyshot[j].pattern = p;
			if (enemyshot[j].pattern == 3)enemyshot[j].ang = ang + j; 
			else if (enemyshot[j].pattern == 4)enemyshot[j].ang = (i + 1) / (2 * M_PI);
			else if (enemyshot[j].pattern == 5)enemyshot[j].ang = ((m % 7) * 6) / (2 * M_PI);
			else enemyshot[j].ang = ang;
			i+=5;
			m++;
			if (i > 360)i = 1;
			if (m > 7)m = 1;
			return;
		}
	}
}

//初期化
void enemyshot_Initialize() {
	enemyshot_GF1 = LoadGraph("sozai\\GF\\青玉小.png");
	enemyshot_GF2 = LoadGraph("sozai\\GF\\赤玉小.png");
	enemyshot_GF3 = LoadGraph("sozai\\GF\\緑玉小.png");
}



//動きを計算する
void enemyshot_Update() {
	for (int i = 0; i < EMAXSHOT; i++) {
		//直進
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 1) {
			enemyshot[i].y += enemyshot[i].speed;
			if (enemyshot[i].y < -80 || enemyshot[i].y > 800 || enemyshot[i].x < -80 || 800 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//自機狙い
		if(enemyshot[i].flag == 1 && enemyshot[i].pattern == 2){
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang) -0.3;
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -80 || enemyshot[i].y > 800 ||enemyshot[i].x < -80 || 800 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//ばらまき弾的な(敵が動くときに可)
		if(enemyshot[i].flag == 1 && enemyshot[i].pattern == 3) {
			double ang = (enemyshot[i].ang * 2 * M_PI / 6);
			enemyshot[i].x += enemyshot[i].speed * cos(ang);
			enemyshot[i].y += enemyshot[i].speed * sin(ang);
			if (enemyshot[i].y < -80 || enemyshot[i].y > 800 || enemyshot[i].x < -80 || 800 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//回転
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 4) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -80 || enemyshot[i].y > 800 || enemyshot[i].x < -80 || 800 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//回転2
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 5) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -80 || enemyshot[i].y > 800 || enemyshot[i].x < -80 || 800 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		
		
	}
}



//描画する
void enemyshot_Draw() {
	for (int i = 0; i < EMAXSHOT; i++) {
		if (enemyshot[i].flag == 1 && enemyshot[i].type == 1) {
			DrawCircle(enemyshot[i].x + 24, enemyshot[i].y + 30, 5, GetColor(255, 255, 255), TRUE);
			DrawRotaGraph(enemyshot[i].x + 24, enemyshot[i].y + 30, 1, 0, enemyshot_GF1, TRUE);
		}
		if (enemyshot[i].flag == 1 && enemyshot[i].type == 2) {
			DrawCircle(enemyshot[i].x + 24, enemyshot[i].y + 30, 5, GetColor(255, 255, 255), TRUE);
			DrawRotaGraph(enemyshot[i].x + 24, enemyshot[i].y + 30, 1, 0, enemyshot_GF2, TRUE);
		}
		if (enemyshot[i].flag == 1 && enemyshot[i].type == 3) {
			DrawCircle(enemyshot[i].x + 24, enemyshot[i].y + 30, 5, GetColor(255, 255, 255), TRUE);
			DrawRotaGraph(enemyshot[i].x + 24, enemyshot[i].y + 30, 1, 0, enemyshot_GF3, TRUE);
		}
	}
}



//終了処理をする
void enemyshot_Finalize() {
	DeleteGraph(enemyshot_GF1);
	DeleteGraph(enemyshot_GF2);
	DeleteGraph(enemyshot_GF3);
}