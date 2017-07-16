#include "DxLib.h"
#include "grobal.h"
#include "enemy.h"
#include "enemy_shot.h"
#define _USE_MATH_DEFINES
#include <math.h>

//追加(敵と自機玉)////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int collision1(Enemy_status enemy[], BaseShot playershot[], int i) {
	/////追加変数(当たり判定用)/////////////////////////////////
	float distance_x[ENEMYMAX], distance_y[ENEMYMAX], range[ENEMYMAX];

	for (int j = 0; j < PMAXSHOT; j++) {
		if (playershot[j].flag == 1) {

			//円
			distance_x[j] = (playershot[j].x) - (enemy[i].x + 24);
			distance_y[j] = (playershot[j].y) - (enemy[i].y + 30);
			range[j] = sqrt(distance_x[j] * distance_x[j] + distance_y[j] * distance_y[j]);

			//当たり判定（円）
			if (range[j] <= 20) {
				playershot[j].flag = 0;
				enemy[i].hp -= playershot[j].power;
				return 1;
			}
		}
	}
	return 0;
}
//敵弾と自機
int collision2(BaseUnit player, Enemy_shot enemyshot[]) {
	float distance_x2[EMAXSHOT], distance_y2[EMAXSHOT], range2[EMAXSHOT];

	for (int j = 0; j < EMAXSHOT; j++) {
		if (enemyshot[j].flag == 1) {
			distance_x2[j] = (player.x) - (enemyshot[j].x + 24);
			if (distance_x2[j] < 0) distance_x2[j] *= -1;
			distance_y2[j] = (player.y) - (enemyshot[j].y + 30);
			if (distance_y2[j] < 0) distance_y2[j] *= -1;
			range2[j] = sqrt(distance_x2[j] * distance_x2[j] + distance_y2[j] * distance_y2[j]);

			if (range2[j] <= 15) {
				enemyshot[j].flag = 0;
				return 1;
			}
		}
	}
	return 0;
}
//敵と自機
int collision3(BaseUnit player, Enemy_status enemy[], int i) {
	float distance_x3[ENEMYMAX], distance_y3[ENEMYMAX], range3[ENEMYMAX];

	for (int j = 0; j < ENEMYMAX; j++) {
		if (enemy[i].flag == 1) {
			distance_x3[j] = (player.x) - (enemy[i].x + 24);
			if (distance_x3[j] < 0) distance_x3[j] *= -1;
			distance_y3[j] = (player.y) - (enemy[i].y + 30);
			if (distance_y3[j] < 0) distance_y3[j] *= -1;
			range3[j] = sqrt(distance_x3[j] * distance_x3[j] + distance_y3[j] * distance_y3[j]);

			if (range3[j] <= 20) {
				return 1;
			}
		}
	}
	return 0;
}

//敵と自機剣
int collision4(BaseSword player, Enemy_status enemy[], int i) {//BaseUnit player を Basesword playerswordに変更
	float distance_x4[ENEMYMAX], distance_y4[ENEMYMAX], range4[ENEMYMAX];

	for (int j = 0; j < ENEMYMAX; j++) {

		if (enemy[i].flag == 1) {  //if(enemy[i].flag == 1 && playersword.flag == 1) に変更
			distance_x4[j] = (player.x + 25) - (enemy[i].x + 24);
			if (distance_x4[j] < 0) distance_x4[j] *= -1;
			distance_y4[j] = (player.y) - (enemy[i].y + 90);
			if (distance_y4[j] < 0) distance_y4[j] *= -1;
			range4[j] = sqrt(distance_x4[j] * distance_x4[j] + distance_y4[j] * distance_y4[j]);

			if (distance_x4[j] < 0)distance_x4[j] *= -1;
			if (distance_y4[j] < 0)distance_y4[j] *= -1;

			if (distance_x4[j] < 35 && distance_y4[j] < 12) {
				enemy[i].hp -= 5;
				return 1;
			}
		}
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











//引数情報
//自機狙いの角度・・・・atan2(player.y - enemy[i].y, player.x - enemy[i].x)
//円状の角度・・・・atan2(enemy[i].y, enemy[i].x)
//ばらまき・・・sqrt(x + y)
//nの引数・・・敵の数　＊　一体の敵の打つ弾の数

void enemy_act0(int i) {
	int t = enemy[i].cnt;
	if (enemy[i].y >= -70 && enemy[i].y <= 820) {
		if (enemy[i].y >= 50 && t % 15 == 0) {
			createEnemyShot(enemy[i].x, enemy[i].y, 100, 2, 4, 2, atan2(player.y - enemy[i].y, player.x - enemy[i].x));
		}
		enemy[i].y += enemy[i].speed;

		//当たり判定処理//////////////////////////////
		if (collision1(enemy, playershot, i) == 1) {
			score++;
		}
		if (collision2(player, enemyshot) == 1) {
			player.hp--;
			hp_g += 6;
		}
		if (collision3(player, enemy, i) == 1) {
			player.hp--;
			hp_g += 6;
		}
		/////////////////////////////////////////////

	}
	return;
}

void enemy_act1(int i) {
	int t = enemy[i].cnt;
	double x = (player.x - enemyshot[i].x) * (player.x - enemyshot[i].x);
	double y = (player.y - enemy[i].y) * (player.y - enemy[i].y);
	if (enemy[i].y >= -70 && enemy[i].y <= 820 && t % 10 == 0) {
		//createEnemyShot(enemy[i].x, enemy[i].y, 100, 1, 5.0, 3, 0);	
		//createEnemyShot(enemy[i].x, enemy[i].y, 10, 4, 3, 2, atan2(player.y - enemy[i].y, player.x - enemy[i].x));
	}
	enemy[i].y += enemy[i].speed;
	//当たり判定処理//////////////////////////////
	if (collision1(enemy, playershot, i) == 1) {
		score++;
	}
	if (collision2(player, enemyshot) == 1) {
		player.hp--;
		hp_g += 6;
	}
	if (collision3(player, enemy, i) == 1) {
		player.hp--;
		hp_g += 6;
	}
	if (collision4(playersword, enemy, i) == 1) {
		score += 100;
	}
	/////////////////////////////////////////////
	return;
}

void enemy_act2(int i) {
	int t = enemy[i].cnt;
	if (enemy[i].y >= -70 && enemy[i].y <= 820) {
		if (enemy[i].y >= 20 && t % 5 == 0) {
			//createEnemyShot(enemy[i].x, enemy[i].y, 500, 4, 3, 1, atan2(enemy[i].y, enemy[i].x));
			//createEnemyShot(enemy[i].x, enemy[i].y, 500, 2, 3, 2, atan2(player.y - enemy[i].y, player.x - enemy[i].x));
			createEnemyShot(enemy[i].x, enemy[i].y, 300, 5, 3, 2, atan2(player.y - enemy[i].y, player.x - enemy[i].x));

		}
		enemy[i].y += enemy[i].speed;


		//当たり判定処理//////////////////////////////
		if (collision1(enemy, playershot, i) == 1) {
			score++;
		}
		if (collision2(player, enemyshot) == 1) {
			player.hp--;
			hp_g += 6;
		}
		if (collision3(player, enemy, i) == 1) {
			player.hp--;
			hp_g += 6;
		}
		/////////////////////////////////////////////
	}
	return;
}

void enemy_act3(int i) {
	return;
}

void enemy_act4(int i) {
	return;
}

void enemy_act5(int i) {
	return;
}

void enemy_act6(int i) {
	return;
}

void enemy_act7(int i) {
	return;
}

void enemy_act8(int i) {
	return;
}
