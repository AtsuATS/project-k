#include "DxLib.h"
#include "grobal.h"
#include "enemyshot.h"
#include "enemy_act.h"
#include "BaseUnit.h"
#define _USE_MATH_DEFINES
#include <math.h>

Enemy_shot enemyshot[EMAXSHOT];
int enemyshot_GF1, enemyshot_GF2, enemyshot_GF3;

//ex ey...座標　n...弾の個数　p...パターン　s...スピード　t...弾のタイプ　ang...角度
void createEnemyShot(float ex , float ey, int n, int p, int s, int t, double ang) { 
	static int i = 1, m = 1;//角度を順番に与えるための変数
	int q = 1;
	int num = 0;//何発出したか数える変数
	for (int j = 0; j < EMAXSHOT; j++) {
		if (enemyshot[j].flag == 0) {
			enemyshot[j].x = ex;
			enemyshot[j].y = ey;
			enemyshot[j].speed = s;
			enemyshot[j].flag = 1;
			enemyshot[j].type = t;
			enemyshot[j].pattern = p;
			if (enemyshot[j].pattern == 3)enemyshot[j].ang = ang + j;
			else if (enemyshot[j].pattern == 4) {
				enemyshot[j].ang = (i + 1) / (2 * M_PI);
				i += 5;
				if (i > 360)i = 1;
			}
			else if (enemyshot[j].pattern == 5) {
				enemyshot[j].ang = ((m % 7) * 6) / (2 * M_PI);
				m++;
				if (m > 7)m = 1;
			}
			else if (enemyshot[j].pattern == 6) {
				enemyshot[j].ang = ang + (q	 + 1) / (2 * M_PI);
				q++;
			}
			else if (enemyshot[j].pattern == 7) {
				enemyshot[j].ang = ang + (q + 1) / (2 * M_PI);
				q+=1;
			}
			else if (enemyshot[j].pattern == 8) {
				if (num == 2) enemyshot[j].ang = ang;
				if (num == 0) enemyshot[j].ang = ang + 0.5;
				if (num == 1) enemyshot[j].ang = ang - 0.5;
			}
			else if (enemyshot[j].pattern == 10) {
				enemyshot[j].ang = ang + j + 0.1;

			}
			else if (enemyshot[j].pattern == 11) {
				enemyshot[j].ang = (i + 1) / (2 * M_PI);
				i += 3;
				if (i > 360)i = 1;
			}
			else {
				enemyshot[j].ang = ang;
			}
			num++;

			if (num == n)break;
		}
	}
}

//初期化
void enemyshot_Initialize() {
	enemyshot_GF1 = LoadGraph("GF\\赤玉小.png");
	enemyshot_GF2 = LoadGraph("GF\\緑玉小.png");
	enemyshot_GF3 = LoadGraph("GF\\青玉小.png");

	for (int i = 0; i < EMAXSHOT; i++) {
		enemyshot[i].flag = 0;
	}
}



//動きを計算する
void enemyshot_Update() {
	for (int i = 0; i < EMAXSHOT ; i++) {
		//直進
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 1) {
			enemyshot[i].y += enemyshot[i].speed;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//自機狙い
		if(enemyshot[i].flag == 1 && enemyshot[i].pattern == 2){
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang)-0.3;
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang)-0.2;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		
		//ばらまき弾的な(敵が動くときに可)
		if(enemyshot[i].flag == 1 && enemyshot[i].pattern == 3) {
			double ang = (enemyshot[i].ang * 2 * M_PI / 6);
			enemyshot[i].x += enemyshot[i].speed * cos(ang);
			enemyshot[i].y += enemyshot[i].speed * sin(ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//回転
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 4) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//回転2
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 5) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//３発
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 6) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//２発
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 7) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//自機狙い＋自機外し
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 8) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang) - 0.3;
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang) - 0.2;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}

		//ボス弾幕用
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//高速自機狙い(スピードは普通×２)
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 9) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang) - 0.3;
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang) - 0.2;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				if (enemyshot[i].y < -25 && enemyshot[i].flag != 0)
					for (int j = 0; j < 200; j += 5) createEnemyShot(enemyshot[i].x, enemyshot[i].y + j, 1, 15, 10, 3, 0);
				else if (enemyshot[i].y > 615 && enemyshot[i].flag != 0)
					for (int j = 0; j < 200; j += 5) createEnemyShot(enemyshot[i].x, enemyshot[i].y - j, 1, 12, 10, 3, 0);
				else if (enemyshot[i].x < -15 && enemyshot[i].flag != 0)
					for (int j = 0; j < 200; j += 5)createEnemyShot(enemyshot[i].x + j, enemyshot[i].y, 1, 13, 10, 3, 0);
				else if (enemyshot[i].x > 565 && enemyshot[i].flag != 0)
					for (int j = 0; j < 200; j += 5)createEnemyShot(enemyshot[i].x - j, enemyshot[i].y, 1, 14, 10, 3, 0);
				enemyshot[i].flag = 0;
				createEnemyShot(enemyshot[i].x, enemyshot[i].y, 30, 10, 4, 1, 0);
			}
		}
		//拡散弾幕 攻撃２で使用
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 10) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//回転ボス
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 11) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//上
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 12) {
			enemyshot[i].y -= enemyshot[i].speed;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//右
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 13) {
			enemyshot[i].x += enemyshot[i].speed;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//左
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 14) {
			enemyshot[i].x -= enemyshot[i].speed;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}//下
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 15) {
			enemyshot[i].y += enemyshot[i].speed;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////


	}
}

//描画する
void enemyshot_Draw() {
	for (int i = 0; i < EMAXSHOT; i++) {
		if (enemyshot[i].flag == 1 && enemyshot[i].type == 1) {
			//DrawCircle(enemyshot[i].x + 24, enemyshot[i].y + 30, 5, GetColor(255, 255, 255), TRUE);
			DrawRotaGraph(enemyshot[i].x + 24, enemyshot[i].y + 30, 1, 0, enemyshot_GF1, TRUE);
		}
		if (enemyshot[i].flag == 1 && enemyshot[i].type == 2) {
			DrawRotaGraph(enemyshot[i].x + 24, enemyshot[i].y + 30, 1, 0, enemyshot_GF2, TRUE);
		}
		if (enemyshot[i].flag == 1 && enemyshot[i].type == 3) {
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