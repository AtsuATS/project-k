#include "DxLib.h"
#include "grobal.h"
#include "enemy.h"
#include "enemyshot.h"
#define _USE_MATH_DEFINES
#define STOPPOINT_X 275 //ボス用定義
#define STOPPOINT_Y 150 //ボス用定義
#include <math.h>
#include "calculation.h"

//act[]の初期化を忘れないこと

//引数degの方向にenemy->speedで進む
void enemy_act0(Enemy_status *enemy, float deg) {

	float sine, cosine;

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
void enemy_act3(Enemy_status *enemy, char c) {
	if (enemy->act[3] == 0) {
		enemy->y -= enemy->speed;
		if (enemy->y < 100) {
			if (c == 'l') enemy->deg = 270;
			if (c == 'r') enemy->deg = -90;

			enemy->act[3] = 1;
		}
	}
	else if (enemy->act[3] == 1 && c == 'l') {
		if (enemy->deg > 90) {
			enemy_act0(enemy, enemy->deg);
			enemy->deg -= 4;
		}
		else {
			enemy->y += enemy->speed;
		}
	}
	else if (enemy->act[3] == 1 && c == 'r') {
		if (enemy->deg < 90) {
			enemy_act0(enemy, enemy->deg);
			enemy->deg += 4;
		}
		else {
			enemy->y += enemy->speed;
		}
	}
	return;
}


//くねくね(改良予定)
void enemy_act4(Enemy_status *enemy) {
	static int theta = 0;
	
	enemy->x += enemy->speed*sin(to_rad(theta));
	enemy->y += enemy->speed;
	theta += enemy->speed;

	if (theta >= 720) {
		//enemy->act[7] = 1;
		theta = 0;
	}
	
	/*if (enemy->act[4] == 0) {
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
	}*/
	return;
}

//止まる
void enemy_act5(Enemy_status *enemy) {
	if (enemy->act[5] == 0) {
		enemy->y += enemy->speed;
		if (enemy->y >= STOPPOINT_Y)enemy->act[5] = 1;
	}
	return;
}

//ボスの動き
void enemy_act6(Enemy_status *enemy) {
	
	static int dx = -1;
	
	if (enemy->act[6] == 0) {
		enemy->x += enemy->speed;
		if (enemy->y <= 50) dx = 1;
		enemy->y += enemy->speed*dx;

		if (enemy->y >= STOPPOINT_Y) {
			enemy->act[6] = 1;
		}
	}
	else if (enemy->act[6] == 1) {
		enemy->x -= enemy->speed;
		if (enemy->y >= 250) dx = -1;
		enemy->y += enemy->speed*dx;

		if (enemy->y <= STOPPOINT_Y) {
			enemy->act[6] = 2;
		}
	}

	else if (enemy->act[6] == 2) {
		enemy->x -= enemy->speed;
		if (enemy->y <= 50) dx = 1;
		enemy->y += enemy->speed*dx;

		if (enemy->y >= STOPPOINT_Y) {
			enemy->act[6] = 3;
		}
	}

	else if (enemy->act[6] == 3) {
		enemy->x += enemy->speed;
		if (enemy->y >= 250) dx = -1;
		enemy->y += enemy->speed*dx;

		if (enemy->y <= STOPPOINT_Y) {
			enemy->act[6] = 0;
		}
	}
}

void enemy_act7(Enemy_status *enemy) {
	static int dx = 1, dy = 1;
	int rand_p = 0;
	//if (rand_p == 1 || rand_p == 2) rand_p += 5;
	//else 
	rand_p = nrandom(120);
	enemy->x += enemy->speed*dx;
	enemy->y += enemy->speed*dy;
	//if (rand_p == 1)dx *= -1;
	//if (rand_p == 2)dy *= -1;
	if (enemy->x <= 50 || enemy->x >= 500 || rand_p == 1) dx *= -1;
	if (enemy->y <= 50 || enemy->y >= 250 || rand_p == 2) dy *= -1;
}

void enemy_act8(Enemy_status *enemy) {
	//enemy->x += enemy->speed;
	enemy->x = STOPPOINT_X + 215 * sin(0.5*to_rad(theta));
	enemy->y =STOPPOINT_Y- 50*sin(to_rad(theta));
	theta+=enemy->speed;

	if (theta>=720) {
		//enemy->act[7] = 1;
		theta = 0;
	}
	
	return;
}