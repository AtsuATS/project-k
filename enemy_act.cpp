#include "DxLib.h"
#include "grobal.h"
#include "enemy.h"
#include "enemy_shot.h"
#define _USE_MATH_DEFINES
#include <math.h>



void enemy_act0(Enemy_status *enemy, float deg) {

	float A_a, sine, cosine;

	cosine = cos(to_rad(deg));
	sine = sin(to_rad(deg));

	enemy->x += enemy->speed*cosine;
	enemy->y += enemy->speed*sine;

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
	//“–‚½‚è”»’èˆ—//////////////////////////////
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


		//“–‚½‚è”»’èˆ—//////////////////////////////
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
