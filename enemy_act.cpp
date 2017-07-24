#include "DxLib.h"
#include "grobal.h"
#include "enemy.h"
#include "enemyshot.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "calculation.h"



//引数degの方向にenemy->speedで進む
void enemy_act0(Enemy_status *enemy, float deg) {

	float A_a, sine, cosine;

	cosine = cos(to_rad(deg));
	sine = sin(to_rad(deg));

	enemy->x += enemy->speed*cosine;
	enemy->y += enemy->speed*sine;

	return;
}

//プレーヤーの方向に動く最初の一コマで方向を決定
void enemy_act1(Enemy_status *enemy) {
	if (enemy->act[1] == 0) {
		enemy->deg = to_deg(atan2f(enemy->y - player.y, enemy->x - player.x))+180;
		enemy->act[1] = 1;
		enemy_act0(enemy, enemy->deg);
	}

	enemy_act0(enemy,enemy->deg);

	return;
}

//左から現れて中心で下方向に1回転のちに右に消える
void enemy_act2(Enemy_status *enemy) {
	if (enemy->act[2]==0) {
			enemy->x += enemy->speed;
			if (enemy->x >= 275) {
				enemy->deg =0;
				enemy->act[2] = 1;
			}
	}
	else if (enemy->act[2] == 1) {
		if (enemy->deg < 360) {
			enemy_act0(enemy, enemy->deg);
			enemy->deg+=1.5;
		}
		else {
			enemy->x += enemy->speed;
		}
	}
}

