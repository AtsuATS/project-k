#include "DxLib.h"
#include "grobal.h"
#include "enemy_act.h"
#include "enemyshot.h"
#include <math.h>

Enemy_status enemy[ENEMYMAX];

int enemy_R, enemy_G, enemy_B;
int score = 0;
static int t = 0;

/*void createEnemy(float ex, float ey, int n, int s, int t, int hp, int num) { //n‚Í“G‚Ì”,s‚ÍƒXƒs[ƒh,t‚Íƒ^ƒCƒv,hp‚Í‘Ì—Í,num‚Í“G”Ô†
	int a = 0;//À•W‚¸‚ç‚µ‚Ì‚½‚ß‚ÌŠÖ”
	for (int i = num; i < (num + 1) + n ; i++) {
		if (enemy[i].flag == 0) {
			enemy[i].x = ex + a * 100;
			enemy[i].y = ey;
			enemy[i].hp = hp;
			enemy[i].speed = s;
			enemy[i].flag = 1;
			enemy[i].type = t;
			a++;
			return;
		}
	}
}*/


void enemy_Initialize() {

	enemy[0].hp  = 1;  enemy[0].speed  = 2;  enemy[0].x  = 155;  enemy[0].y  = 300;  enemy[0].flag  = 1;   enemy[0].type = 1;
	enemy[1].hp  = 50; enemy[1].speed  = 0;  enemy[1].x  = 255;  enemy[1].y  = 200;  enemy[1].flag  = 1;   enemy[1].type = 2;
	enemy[2].hp  = 5;  enemy[2].speed  = 2;  enemy[2].x  = 355;  enemy[2].y  = -70;  enemy[2].flag  = 1;   enemy[2].type = 3;
	enemy[3].hp  = 1;  enemy[3].speed  = 3;  enemy[3].x  = 155;  enemy[3].y  = -70;  enemy[3].flag  = 0;   enemy[3].type = 1;
	enemy[4].hp  = 3;  enemy[4].speed  = 3;  enemy[4].x  = 255;  enemy[4].y  = -70;  enemy[4].flag  = 0;   enemy[4].type = 2;
	enemy[5].hp  = 5;  enemy[5].speed  = 3;  enemy[5].x  = 355;  enemy[5].y  = -70;  enemy[5].flag  = 0;   enemy[5].type = 3;
	enemy[6].hp  = 1;  enemy[6].speed  = 3;  enemy[6].x  = 155;  enemy[6].y  = -70;  enemy[6].flag  = 0;   enemy[6].type = 1;
	enemy[7].hp  = 3;  enemy[7].speed  = 3;  enemy[7].x  = 255;  enemy[7].y  = -70;  enemy[7].flag  = 0;   enemy[7].type = 2;
	enemy[8].hp  = 5;  enemy[8].speed  = 3;  enemy[8].x  = 355;  enemy[8].y  = -70;  enemy[8].flag  = 0;   enemy[8].type = 3;
	enemy[9].hp  = 1;  enemy[9].speed  = 3;  enemy[9].x  = 155;  enemy[9].y  = -70;  enemy[9].flag  = 0;   enemy[9].type = 1;
	enemy[10].hp = 3;  enemy[10].speed = 3;  enemy[10].x = 255;  enemy[10].y = -70;  enemy[10].flag = 0;  enemy[10].type = 2;
	enemy[11].hp = 5;  enemy[11].speed = 3;  enemy[11].x = 355;  enemy[11].y = -70;  enemy[11].flag = 0;  enemy[11].type = 3;
	enemy[12].hp = 1;  enemy[12].speed = 3;  enemy[12].x = 155;  enemy[12].y = -70;  enemy[12].flag = 0;  enemy[12].type = 1;
	enemy[13].hp = 3;  enemy[13].speed = 3;  enemy[13].x = 255;  enemy[13].y = -70;  enemy[13].flag = 0;  enemy[13].type = 2;
	enemy[14].hp = 5;  enemy[14].speed = 3;  enemy[14].x = 355;  enemy[14].y = -70;  enemy[14].flag = 0;  enemy[14].type = 3;
	enemy[15].hp = 1;  enemy[15].speed = 3;  enemy[15].x = 155;  enemy[15].y = -70;  enemy[15].flag = 0;  enemy[15].type = 1;
	enemy[16].hp = 3;  enemy[16].speed = 3;  enemy[16].x = 255;  enemy[16].y = -70;  enemy[16].flag = 0;  enemy[16].type = 2;
	enemy[17].hp = 5;  enemy[17].speed = 3;  enemy[17].x = 355;  enemy[17].y = -70;  enemy[17].flag = 0;  enemy[17].type = 3;
	enemy[18].hp = 1;  enemy[18].speed = 3;  enemy[18].x = 155;  enemy[18].y = -70;  enemy[18].flag = 0;  enemy[18].type = 1;
	enemy[19].hp = 3;  enemy[19].speed = 3;  enemy[19].x = 255;  enemy[19].y = -70;  enemy[19].flag = 0;  enemy[19].type = 2;
	enemy[20].hp = 5;  enemy[20].speed = 3;  enemy[20].x = 355;  enemy[20].y = -70;  enemy[20].flag = 0;  enemy[20].type = 3;
	
	enemy_R = LoadGraph("sozai\\GF\\“GÔ‰¼.png");
	enemy_G = LoadGraph("sozai\\GF\\“G—Î‰¼.png");
	enemy_B = LoadGraph("sozai\\GF\\“GÂ‰¼.png");

}

void enemy_Update() {

	if (t>=100&&enemy[0].flag==1) {
		if(t<200)enemy_act0(&enemy[0], 0);
		else if(t<300)enemy_act0(&enemy[0], 270);
		else if (t < 400)enemy_act0(&enemy[0], 180);
		else enemy_act0(&enemy[0], t);
	}

	for (int i = 0; i < ENEMYMAX; i++) {
		if (enemy[i].x < -80 || 800 < enemy[i].x || enemy[i].y < -80 || 600 < enemy[i].y) enemy[i].flag = 0;
		if (enemy[i].hp <= 0) enemy[i].flag = 0;
	}

	
}

void enemy_Draw() {
	//“G‚Ì•`‰æ

	for (int i = 0; i < ENEMYMAX; i++) {
		if (enemy[i].flag == 1 && enemy[i].type == 1) {
			DrawCircle(enemy[i].x + 24, enemy[i].y + 30, 10, GetColor(0, 0, 255), TRUE);
			DrawGraph(enemy[i].x, enemy[i].y, enemy_R, TRUE);

		}
		if (enemy[i].flag == 1 && enemy[i].type == 2) {
			DrawCircle(enemy[i].x + 24, enemy[i].y + 30, 10, GetColor(0, 0, 255), TRUE);
			DrawGraph(enemy[i].x, enemy[i].y, enemy_G, TRUE);
			//DrawBox(enemy[i].x + 19, enemy[i].y + 25, enemy[i].x + 29, enemy[i].y + 35, GetColor(0, 0, 255), TRUE);
			

		}
		if (enemy[i].flag == 1 && enemy[i].type == 3) {
			DrawCircle(enemy[i].x + 24, enemy[i].y + 30, 10, GetColor(0, 0, 255), TRUE);
			DrawGraph(enemy[i].x, enemy[i].y, enemy_B, TRUE);
			

		}
		

	}

	DrawFormatString(650, 10, GetColor(255, 255, 255), "time %d", t);
	DrawFormatString(650, 50, GetColor(0, 0, 255), "score %d", score);

	t++;
	

}

void enemy_Finalize() {
	DeleteGraph(enemy_R);
	DeleteGraph(enemy_G);
	DeleteGraph(enemy_B);
}

