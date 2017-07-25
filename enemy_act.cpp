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
//新たに引数を設ければ回転の方向を指定可能
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
			enemy->deg+=5;
		}
		else {
			enemy->x += enemy->speed;
		}
	}
	return;
}

//下から現れて(この場合は)y座標100を切った時点で回転、下に消える。
//引数を設ければ折り返しの座標や、方向が指定可能になる
void enemy_act3(Enemy_status *enemy) {
	if (enemy->act[3] == 0) {
		enemy->y -= enemy->speed;
		if (enemy->y < 100) {
			enemy->deg = 270;
			enemy->act[3] = 1;
		}
	}
	else if (enemy->act[3] == 1) {
		if (enemy->deg > 90) {
			enemy_act0(enemy, enemy->deg);
			enemy->deg -= 2;
		}
		else {
			enemy->y += enemy->speed;
		}
	}
	return;
}


//くねくね(改良予定)
void enemy_act4(Enemy_status *enemy) {
	if (enemy->act[4] == 0) {
		enemy_act0(enemy, enemy->deg);
		enemy->deg += 5;
		if (enemy->deg >= 180){
			enemy->act[4] = 1;
		}
	}
	else if (enemy->act[4] == 1) {
		enemy_act0(enemy, enemy->deg);
		enemy->deg -= 5;
		if (enemy->deg <= 0) {
			enemy->act[4] = 0;
		}
	}
	return;
}

//止まる
void enemy_act5(Enemy_status *enemy) {
	if (enemy->act[5] == 0) {
		enemy->y += enemy->speed;
		if (enemy->y >= 200)enemy->act[5] = 1;
	}
	return;
}