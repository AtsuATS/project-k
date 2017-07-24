#include "DxLib.h"
#include "grobal.h"
#include "enemy.h"
#include "enemyshot.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "calculation.h"



void enemy_act0(Enemy_status *enemy, float deg) {

	float A_a, sine, cosine;

	cosine = cos(to_rad(deg));
	sine = sin(to_rad(deg));

	enemy->x += enemy->speed*cosine;
	enemy->y += enemy->speed*sine;

	return;
}

void enemy_act1(Enemy_status *enemy) {
	if (enemy->act[1] == 0) {
		enemy->deg = to_deg(atan2f(enemy->y - player.y, enemy->x - player.x))+180;
		enemy->act[1] = 1;
		enemy_act0(enemy, enemy->deg);
	}

	enemy_act0(enemy,enemy->deg);

	return;
}