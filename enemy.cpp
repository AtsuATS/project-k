#include "DxLib.h"
#include "grobal.h"
#include "enemy_act.h"
#include "enemyshot.h"
#define _USE_MATH_DEFINES
#include <math.h>

Enemy_status enemy[ENEMYMAX];

int enemy_R, enemy_G, enemy_B;
int score = 0;
int t = 0;
int finish_t = 0;//èIÇÌÇ¡ÇΩéûÇ…ìÆÇ´èoÇ∑

int collision1(Enemy_status enemy[], BaseShot playershot[], int i) {
	float distance_x[ENEMYMAX], distance_y[ENEMYMAX], range[ENEMYMAX];

	for (int j = 0; j < PMAXSHOT; j++) {
		if (playershot[j].flag == 1 && enemy[i].flag == 1) {

			//â~
			distance_x[j] = (playershot[j].x) - (enemy[i].x + 24);
			distance_y[j] = (playershot[j].y) - (enemy[i].y + 30);
			range[j] = sqrt(distance_x[j] * distance_x[j] + distance_y[j] * distance_y[j]);

			//ìñÇΩÇËîªíËÅiâ~Åj
			if (range[j] <= 20) {
				playershot[j].flag = 0;
				enemy[i].hp -= playershot[j].power;
				return 1;
			}
		}
	}
	return 0;
}
//ìGíeÇ∆é©ã@
int collision2(BaseUnit player, Enemy_shot enemyshot[]) {
	float distance_x2[EMAXSHOT], distance_y2[EMAXSHOT], range2[EMAXSHOT];

	for (int j = 0; j < EMAXSHOT; j++) {
		if (enemyshot[j].flag == 1) {
			distance_x2[j] = (player.x) - (enemyshot[j].x + 24);
			if (distance_x2[j] < 0) distance_x2[j] *= -1;
			distance_y2[j] = (player.y) - (enemyshot[j].y + 30);
			if (distance_y2[j] < 0) distance_y2[j] *= -1;
			range2[j] = sqrt(distance_x2[j] * distance_x2[j] + distance_y2[j] * distance_y2[j]);

			if (range2[j] <= 15 && enemyshot[j].type == 1) {
				enemyshot[j].flag = 0;
				return 5;
			}
			else if (range2[j] <= 15 && enemyshot[j].type == 2) {
				enemyshot[j].flag = 0;
				return 3;
			}
			else if (range2[j] <= 15 && enemyshot[j].type == 3) {
				enemyshot[j].flag = 0;
				return 2;
			}
		}
	}
	return 0;
}
//ìGÇ∆é©ã@
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

//ìGÇ∆é©ã@åï
int collision4(BaseSword playersword, Enemy_status enemy[], int i) {//BaseUnit player Ç Basesword playerswordÇ…ïœçX
	float distance_x4[ENEMYMAX], distance_y4[ENEMYMAX];
	float psx = playersword.x + 40 * cos(NOWDIGANGLE * 180 / M_PI);
	float psy = playersword.y + 40 * sin(NOWDIGANGLE * 180 / M_PI);

	for (int j = 0; j < ENEMYMAX; j++) {
		if (enemy[i].flag == 1 && playersword.flag == 1) {  //if(enemy[i].flag == 1 && playersword.flag == 1) Ç…ïœçX
			distance_x4[j] = (psx) - (enemy[i].x + 24);
			if (distance_x4[j] < 0) distance_x4[j] *= -1;
			distance_y4[j] = (psy) - (enemy[i].y + 30);
			if (distance_y4[j] < 0) distance_y4[j] *= -1;

			if (psx > 530 || psx < 20 || psy > 590 || psy < 10)
				return 0;

			if (distance_x4[j] < 40 && distance_y4[j] < 13) {
				return 1;
			}
		}
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void enemy_Initialize() {

	//1
	enemy[0].hp  = 5;  enemy[0].speed  = 2;  enemy[0].x  = 202;  enemy[0].y  = -70;  enemy[0].flag  = 1;   enemy[0].type = 3;
	enemy[1].hp  = 5;  enemy[1].speed  = 2;  enemy[1].x  = 302;  enemy[1].y  = -70;  enemy[1].flag  = 1;   enemy[1].type = 3;
	enemy[2].hp  = 5;  enemy[2].speed  = 2;  enemy[2].x  = 402;  enemy[2].y  = -60;  enemy[2].flag  = 1;   enemy[2].type = 3;
	enemy[3].hp  = 5;  enemy[3].speed  = 2;  enemy[3].x  = 102;  enemy[3].y  = -60;  enemy[3].flag  = 1;   enemy[3].type = 3;
	enemy[4].hp  = 5;  enemy[4].speed  = 2;  enemy[4].x  = 570;  enemy[4].y  = 180;  enemy[4].flag  = 1;   enemy[4].type = 3;
	enemy[5].hp  = 5;  enemy[5].speed  = 2;  enemy[5].x  = -70;  enemy[5].y  = 180;  enemy[5].flag  = 1;   enemy[5].type = 3;

	//2
	enemy[6].hp  = 5;  enemy[6].speed  = 3;  enemy[6].x  = -50;  enemy[6].y  = 140;  enemy[6].flag  = 1;   enemy[6].type = 3;
	enemy[7].hp  = 5;  enemy[7].speed  = 3;  enemy[7].x  = -100; enemy[7].y  = 140;  enemy[7].flag  = 1;   enemy[7].type = 3;
	enemy[8].hp  = 5;  enemy[8].speed  = 3;  enemy[8].x  = -150; enemy[8].y  = 140;  enemy[8].flag  = 1;   enemy[8].type = 3;

	enemy[9].hp  = 5;  enemy[9].speed  = 3;  enemy[9].x  = 550;  enemy[9].y  = 240;  enemy[9].flag  = 1;   enemy[9].type = 3;
	enemy[10].hp = 5;  enemy[10].speed = 3;  enemy[10].x = 600;  enemy[10].y = 240;  enemy[10].flag = 1;  enemy[10].type = 3;
	enemy[11].hp = 5;  enemy[11].speed = 3;  enemy[11].x = 650;  enemy[11].y = 240;  enemy[11].flag = 1;  enemy[11].type = 3;

	enemy[12].hp = 5;  enemy[12].speed = 3;  enemy[12].x = -50;  enemy[12].y = 440;  enemy[12].flag = 1;  enemy[12].type = 3;
	enemy[13].hp = 5;  enemy[13].speed = 3;  enemy[13].x = -100; enemy[13].y = 440;  enemy[13].flag = 1;  enemy[13].type = 3;
	enemy[14].hp = 5;  enemy[14].speed = 3;  enemy[14].x = -150; enemy[14].y = 440;  enemy[14].flag = 1;  enemy[14].type = 3;

	enemy[15].hp = 5;  enemy[15].speed = 3;  enemy[15].x = 550;  enemy[15].y = 340;  enemy[15].flag = 1;  enemy[15].type = 3;
	enemy[16].hp = 5;  enemy[16].speed = 3;  enemy[16].x = 600;  enemy[16].y = 340;  enemy[16].flag = 1;  enemy[16].type = 3;
	enemy[17].hp = 5;  enemy[17].speed = 3;  enemy[17].x = 650;  enemy[17].y = 340;  enemy[17].flag = 1;  enemy[17].type = 3;

	//3
	enemy[18].hp = 15;  enemy[18].speed = 3;  enemy[18].x = 2;   enemy[18].y = -70;  enemy[18].flag = 1;  enemy[18].type = 2;
	enemy[19].hp = 15;  enemy[19].speed = 3;  enemy[19].x = 252;  enemy[19].y = -70;  enemy[19].flag = 1;  enemy[19].type = 2;
	enemy[20].hp = 15;  enemy[20].speed = 3;  enemy[20].x = 502;  enemy[20].y = -70;  enemy[20].flag = 1;  enemy[20].type = 2;

	//4
	enemy[21].hp = 5;  enemy[21].speed = 3;  enemy[21].x = -50;  enemy[21].y = -70;  enemy[21].flag = 1;  enemy[21].type = 3;
	enemy[22].hp = 5;  enemy[22].speed = 3;  enemy[22].x = -70;  enemy[22].y = -70;  enemy[22].flag = 1;  enemy[22].type = 3;
	enemy[23].hp = 5;  enemy[23].speed = 3;  enemy[23].x = -90;  enemy[23].y = -70;  enemy[23].flag = 1;  enemy[23].type = 3;

	enemy[24].hp = 5;  enemy[24].speed = 3;  enemy[24].x = 590;  enemy[24].y = -70;  enemy[24].flag = 1;  enemy[24].type = 3;
	enemy[25].hp = 5;  enemy[25].speed = 3;  enemy[25].x = 570;  enemy[25].y = -70;  enemy[25].flag = 1;  enemy[25].type = 3;
	enemy[26].hp = 5;  enemy[26].speed = 3;  enemy[26].x = 550;  enemy[26].y = -70;  enemy[26].flag = 1;  enemy[26].type = 3;

	//5 â∫Ç©ÇÁè„Ç™Ç¡ÇƒâÒì]
	enemy[27].hp = 5;  enemy[27].speed = 3;  enemy[27].x = 172;  enemy[27].y = 620;  enemy[27].flag = 1;  enemy[27].type = 3;
	enemy[28].hp = 5;  enemy[28].speed = 3;  enemy[28].x = 172;  enemy[28].y = 620;  enemy[28].flag = 1;  enemy[28].type = 3;
	enemy[29].hp = 5;  enemy[29].speed = 3;  enemy[29].x = 172;  enemy[29].y = 620;  enemy[29].flag = 1;  enemy[29].type = 3;
	enemy[30].hp = 5;  enemy[30].speed = 3;  enemy[30].x = 172;  enemy[30].y = 620;  enemy[30].flag = 1;  enemy[30].type = 3;
	enemy[31].hp = 5;  enemy[31].speed = 3;  enemy[31].x = 172;  enemy[31].y = 620;  enemy[31].flag = 1;  enemy[31].type = 3;

	enemy[32].hp = 5;  enemy[32].speed = 3;  enemy[32].x = 352;  enemy[32].y = 620;  enemy[32].flag = 1;  enemy[32].type = 3;
	enemy[33].hp = 5;  enemy[33].speed = 3;  enemy[33].x = 352;  enemy[33].y = 620;  enemy[33].flag = 1;  enemy[33].type = 3;
	enemy[34].hp = 5;  enemy[34].speed = 3;  enemy[34].x = 352;  enemy[34].y = 620;  enemy[34].flag = 1;  enemy[34].type = 3;
	enemy[35].hp = 5;  enemy[35].speed = 3;  enemy[35].x = 352;  enemy[35].y = 620;  enemy[35].flag = 1;  enemy[35].type = 3;
	enemy[36].hp = 5;  enemy[36].speed = 3;  enemy[36].x = 352;  enemy[36].y = 620;  enemy[36].flag = 1;  enemy[36].type = 3;

	//6.1
	enemy[37].hp = 5;  enemy[37].speed = 3;  enemy[37].x = -50;  enemy[37].y = 500;  enemy[37].flag = 1;  enemy[37].type = 3;
	enemy[38].hp = 5;  enemy[38].speed = 3;  enemy[38].x = -50;  enemy[38].y = 500;  enemy[38].flag = 1;  enemy[38].type = 3;
	enemy[39].hp = 5;  enemy[39].speed = 3;  enemy[39].x = -50;  enemy[39].y = 500;  enemy[39].flag = 1;  enemy[39].type = 3;

	enemy[40].hp = 5;  enemy[40].speed = 3;  enemy[40].x = 550;  enemy[40].y = 500;  enemy[40].flag = 1;  enemy[40].type = 3;
	enemy[41].hp = 5;  enemy[41].speed = 3;  enemy[41].x = 550;  enemy[41].y = 500;  enemy[41].flag = 1;  enemy[41].type = 3;
	enemy[42].hp = 5;  enemy[42].speed = 3;  enemy[42].x = 550;  enemy[42].y = 500;  enemy[42].flag = 1;  enemy[42].type = 3;

	//6.2
	enemy[43].hp = 15;  enemy[43].speed = 4;  enemy[43].x = 2;   enemy[43].y = -90;  enemy[43].flag = 1;  enemy[43].type = 2;
	enemy[44].hp = 15;  enemy[44].speed = 4;  enemy[44].x = 252;  enemy[44].y = -90;  enemy[44].flag = 1;  enemy[44].type = 2;
	enemy[45].hp = 15;  enemy[45].speed = 4;  enemy[45].x = 502;  enemy[45].y = -90;  enemy[45].flag = 1;  enemy[45].type = 2;

	//7
	enemy[46].hp = 5;  enemy[46].speed = 3;  enemy[46].x = 2;  enemy[46].y = -70;  enemy[46].flag = 1;  enemy[46].type = 3;
	enemy[47].hp = 5;  enemy[47].speed = 3;  enemy[47].x = 102;  enemy[47].y = -70;  enemy[47].flag = 1;  enemy[47].type = 3;
	enemy[48].hp = 5;  enemy[48].speed = 3;  enemy[48].x = 202;  enemy[48].y = -70;  enemy[48].flag = 1;  enemy[48].type = 3;
	enemy[49].hp = 50;  enemy[49].speed = 3;  enemy[49].x = 252;  enemy[49].y = -70;  enemy[49].flag = 1;  enemy[49].type = 1;
	enemy[50].hp = 5;  enemy[50].speed = 3;  enemy[50].x = 302;  enemy[50].y = -70;  enemy[50].flag = 1;  enemy[50].type = 3;
	enemy[51].hp = 5;  enemy[51].speed = 3;  enemy[51].x = 402;  enemy[51].y = -70;  enemy[51].flag = 1;  enemy[51].type = 3;
	enemy[52].hp = 5;  enemy[52].speed = 3;  enemy[52].x = 502;  enemy[52].y = -70;  enemy[52].flag = 1;  enemy[52].type = 3;


	//8(ñ¢íË)
	enemy[53].hp = 5;  enemy[53].speed = 3;  enemy[53].x = 355;  enemy[53].y = -70;  enemy[53].flag = 0;  enemy[53].type = 3;
	enemy[54].hp = 5;  enemy[54].speed = 3;  enemy[54].x = 355;  enemy[54].y = -70;  enemy[54].flag = 0;  enemy[54].type = 3;
	enemy[55].hp = 5;  enemy[55].speed = 3;  enemy[55].x = 355;  enemy[55].y = -70;  enemy[55].flag = 0;  enemy[55].type = 3;
	enemy[56].hp = 5;  enemy[56].speed = 3;  enemy[56].x = 355;  enemy[56].y = -70;  enemy[56].flag = 0;  enemy[56].type = 3;
	enemy[57].hp = 5;  enemy[57].speed = 3;  enemy[57].x = 355;  enemy[57].y = -70;  enemy[57].flag = 0;  enemy[57].type = 3;
	enemy[58].hp = 5;  enemy[58].speed = 3;  enemy[58].x = 355;  enemy[58].y = -70;  enemy[58].flag = 0;  enemy[58].type = 3;
	enemy[59].hp = 5;  enemy[59].speed = 3;  enemy[59].x = 355;  enemy[59].y = -70;  enemy[59].flag = 0;  enemy[59].type = 3;

	
	enemy_R = LoadGraph("sozai\\GF\\ìGê‘âº.png");
	enemy_G = LoadGraph("sozai\\GF\\ìGóŒâº.png");
	enemy_B = LoadGraph("sozai\\GF\\ìGê¬âº.png");

}

void enemy_Update() {

	//à¯êîèÓïÒ
	//ÇRî≠Å@ÇPÅDÇPÇPÅ@ÇQî≠Å@ÇPÅDÇQÇP
	//é©ã@ë_Ç¢ÇÃäpìxÅEÅEÅEÅEatan2(player.y - enemy[i].y, player.x - enemy[i].x)
	//â~èÛÇÃäpìxÅEÅEÅEÅEatan2(enemy[i].y, enemy[i].x)
	//ÇŒÇÁÇ‹Ç´ÅEÅEÅEsqrt(x + y)
	//nÇÃà¯êîÅEÅEÅEìGÇÃêîÅ@ÅñÅ@àÍëÃÇÃìGÇÃë≈Ç¬íeÇÃêî

	double distance_x[ENEMYMAX], distance_y[ENEMYMAX], sq_distance[ENEMYMAX];
	double angle;
	for (int j = 0; j < ENEMYMAX; j++) {
		distance_x[j] = (player.x) - (enemy[j].x + 24);
		distance_y[j] = (player.y) - (enemy[j].y + 30);
		if (distance_x[j] < 0) distance_x[j] *= -1;
		if (distance_y[j] < 0) distance_y[j] *= -1;
		sq_distance[j] = sqrt(distance_x[j] * distance_x[j] + distance_y[j] * distance_y[j]);
		
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//çsìÆ
	//1
	if (t >= 200 && t < 300 && enemy[0].flag == 1) enemy_act0(&enemy[0], 90);
	if (t >= 200 && t < 300 && enemy[1].flag == 1) enemy_act0(&enemy[1], 90);
	if (t >= 200 && t < 300 && enemy[2].flag == 1) enemy_act0(&enemy[2], 95);
	if (t >= 200 && t < 300 && enemy[3].flag == 1) enemy_act0(&enemy[3], 85);
	if (t >= 240 && t < 300 && enemy[4].flag == 1) enemy_act0(&enemy[4], 180);
	if (t >= 240 && t < 300 && enemy[5].flag == 1) enemy_act0(&enemy[5], 0);

	if (t >= 400 && enemy[0].flag == 1) enemy_act0(&enemy[0], 90);
	if (t >= 400 && enemy[1].flag == 1) enemy_act0(&enemy[1], 90);
	if (t >= 400 && enemy[2].flag == 1) enemy_act0(&enemy[2], 90);
	if (t >= 400 && enemy[3].flag == 1) enemy_act0(&enemy[3], 90);
	if (t >= 400 && enemy[4].flag == 1) enemy_act0(&enemy[4], 90);
	if (t >= 400 && enemy[5].flag == 1) enemy_act0(&enemy[5], 90);

	//2
	if (t >= 700 && enemy[6].flag == 1) enemy_act0(&enemy[6], 0);
	if (t >= 700 && enemy[7].flag == 1) enemy_act0(&enemy[7], 0);
	if (t >= 700 && enemy[8].flag == 1) enemy_act0(&enemy[8], 0);

	if (t >= 800 && enemy[9].flag == 1) enemy_act0(&enemy[9], 180);
	if (t >= 800 && enemy[10].flag == 1) enemy_act0(&enemy[10], 180);
	if (t >= 800 && enemy[11].flag == 1) enemy_act0(&enemy[11], 180);

	if (t >= 900 && enemy[12].flag == 1) enemy_act0(&enemy[12], 0);
	if (t >= 900 && enemy[13].flag == 1) enemy_act0(&enemy[13], 0);
	if (t >= 900 && enemy[14].flag == 1) enemy_act0(&enemy[14], 0);

	if (t >= 1000 && enemy[15].flag == 1) enemy_act0(&enemy[15], 180);
	if (t >= 1000 && enemy[16].flag == 1) enemy_act0(&enemy[16], 180);
	if (t >= 1000 && enemy[17].flag == 1) enemy_act0(&enemy[17], 180);
	
	//3 //1500
	if (t >= 1250 && t < 1320 && enemy[18].flag == 1) enemy_act0(&enemy[18], 70);
	if (t >= 1250 && t < 1320 && enemy[19].flag == 1) enemy_act0(&enemy[19], 90);
	if (t >= 1250 && t < 1320 && enemy[20].flag == 1) enemy_act0(&enemy[20], 110);

	if (t >= 1820 && enemy[18].flag == 1) enemy_act0(&enemy[18], 90);
	if (t >= 1820 && enemy[19].flag == 1) enemy_act0(&enemy[19], 90);
	if (t >= 1820 && enemy[20].flag == 1) enemy_act0(&enemy[20], 90);
	
	//4 s1600 e1 e2 1800
	if (t >= 1920 && t < 2020 && enemy[21].flag == 1) enemy_act0(&enemy[21], 30);
	if (t >= 1920 && t < 2020 && enemy[22].flag == 1) enemy_act0(&enemy[22], 40);
	if (t >= 1920 && t < 2020 && enemy[23].flag == 1) enemy_act0(&enemy[23], 50);

	if (t >= 1920 && t < 2020 && enemy[24].flag == 1) enemy_act0(&enemy[24], 130);
	if (t >= 1920 && t < 2020 && enemy[25].flag == 1) enemy_act0(&enemy[25], 140);
	if (t >= 1920 && t < 2020 && enemy[26].flag == 1) enemy_act0(&enemy[26], 150);


	if (t >= 2260 && enemy[21].flag == 1) enemy_act0(&enemy[21], 90);
	if (t >= 2260 && enemy[22].flag == 1) enemy_act0(&enemy[22], 90);
	if (t >= 2260 && enemy[23].flag == 1) enemy_act0(&enemy[23], 90);
	if (t >= 2260 && enemy[24].flag == 1) enemy_act0(&enemy[24], 90);
	if (t >= 2260 && enemy[25].flag == 1) enemy_act0(&enemy[25], 90);
	if (t >= 2260 && enemy[26].flag == 1) enemy_act0(&enemy[26], 90);
	
	//5 1950 e2010
	if (t >= 2410 && enemy[27].flag == 1) enemy_act3(&enemy[27], 'l');
	if (t >= 2425 && enemy[28].flag == 1) enemy_act3(&enemy[28], 'l');
	if (t >= 2440 && enemy[29].flag == 1) enemy_act3(&enemy[29], 'l');
	if (t >= 2455 && enemy[30].flag == 1) enemy_act3(&enemy[30], 'l');
	if (t >= 2470 && enemy[31].flag == 1) enemy_act3(&enemy[31], 'l');

	if (t >= 2410 && enemy[32].flag == 1) enemy_act3(&enemy[32], 'r');
	if (t >= 2425 && enemy[33].flag == 1) enemy_act3(&enemy[33], 'r');
	if (t >= 2440 && enemy[34].flag == 1) enemy_act3(&enemy[34], 'r');
	if (t >= 2455 && enemy[35].flag == 1) enemy_act3(&enemy[35], 'r');
	if (t >= 2470 && enemy[36].flag == 1) enemy_act3(&enemy[36], 'r');
	

	//6.1 s2450 e2490
	if (t >= 2910 && enemy[37].flag == 1) enemy_act0(&enemy[37], 330);
	if (t >= 2930 && enemy[38].flag == 1) enemy_act0(&enemy[38], 330);
	if (t >= 2950 && enemy[39].flag == 1) enemy_act0(&enemy[39], 330);

	if (t >= 2910 && enemy[40].flag == 1) enemy_act0(&enemy[40], 210);
	if (t >= 2930 && enemy[41].flag == 1) enemy_act0(&enemy[41], 210);
	if (t >= 2950 && enemy[42].flag == 1) enemy_act0(&enemy[42], 210);


	//6.2 s2450 e2620
	if (t >= 2910 && t < 2950 && enemy[43].flag == 1) enemy_act0(&enemy[43], 70);
	if (t >= 2910 && t < 2950 && enemy[44].flag == 1) enemy_act0(&enemy[44], 90);
	if (t >= 2910 && t < 2950 && enemy[45].flag == 1) enemy_act0(&enemy[45], 110);

	if (t >= 3080 && enemy[43].flag == 1) enemy_act0(&enemy[43], 90);
	if (t >= 3080 && enemy[44].flag == 1) enemy_act0(&enemy[44], 90);
	if (t >= 3080 && enemy[45].flag == 1) enemy_act0(&enemy[45], 90);


	//7 s2800 s2 2850or2870
	if (t >= 3180 && t < 3230 && enemy[46].flag == 1) enemy_act0(&enemy[46], 70);
	if (t >= 3180 && t < 3230 && enemy[47].flag == 1) enemy_act0(&enemy[47], 80);
	if (t >= 3180 && t < 3230 && enemy[48].flag == 1) enemy_act0(&enemy[48], 90);

	if (t >= 3180 && t < 3250 && enemy[49].flag == 1) enemy_act0(&enemy[49], 90);

	if (t >= 3180 && t < 3230 && enemy[50].flag == 1) enemy_act0(&enemy[50], 90);
	if (t >= 3180 && t < 3230 && enemy[51].flag == 1) enemy_act0(&enemy[51], 100);
	if (t >= 3180 && t < 3230 && enemy[52].flag == 1) enemy_act0(&enemy[52], 110);


	//8 (ñ¢íË)
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//ìGÉVÉáÉbÉg////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//1
	if (t >= 300 && t < 360 && t % 20 == 0) {
		if (enemy[0].flag == 1)createEnemyShot(enemy[0].x, enemy[0].y, 1, 1, 3, 3, 0);
		if (enemy[1].flag == 1)createEnemyShot(enemy[1].x, enemy[1].y, 1, 1, 3, 3, 0);
		if (enemy[2].flag == 1)createEnemyShot(enemy[2].x, enemy[2].y, 1, 1, 3, 3, 0);
		if (enemy[3].flag == 1)createEnemyShot(enemy[3].x, enemy[3].y, 1, 1, 3, 3, 0);
		if (enemy[4].flag == 1)createEnemyShot(enemy[4].x, enemy[4].y, 1, 1, 3, 3, 0);
		if (enemy[5].flag == 1)createEnemyShot(enemy[5].x, enemy[5].y, 1, 1, 3, 3, 0);
	}
	//2
	if (t >= 750 && t < 870 && t % 40 == 0) {
		if (enemy[6].flag == 1)createEnemyShot(enemy[6].x, enemy[6].y, 1, 2, 3, 3, atan2(player.y - enemy[6].y, player.x - enemy[6].x));
		if (enemy[7].flag == 1)createEnemyShot(enemy[7].x, enemy[7].y, 1, 2, 3, 3, atan2(player.y - enemy[7].y, player.x - enemy[7].x));
		if (enemy[8].flag == 1)createEnemyShot(enemy[8].x, enemy[8].y, 1, 2, 3, 3, atan2(player.y - enemy[8].y, player.x - enemy[8].x));

	}
	if (t >= 850 && t < 970 && t % 40 == 0) {
		if (enemy[9].flag == 1)createEnemyShot(enemy[9].x, enemy[9].y, 1, 2, 3, 3, atan2(player.y - enemy[9].y, player.x - enemy[9].x));
		if (enemy[10].flag == 1)createEnemyShot(enemy[10].x, enemy[10].y, 1, 2, 3, 3, atan2(player.y - enemy[10].y, player.x - enemy[10].x));
		if (enemy[11].flag == 1)createEnemyShot(enemy[11].x, enemy[11].y, 1, 2, 3, 3, atan2(player.y - enemy[11].y, player.x - enemy[11].x));
	}
	if (t >= 950 && t < 1070 && t % 40 == 0) {
		if (enemy[12].flag == 1)createEnemyShot(enemy[12].x, enemy[12].y, 1, 2, 3, 3, atan2(player.y - enemy[12].y, player.x - enemy[12].x));
		if (enemy[13].flag == 1)createEnemyShot(enemy[13].x, enemy[13].y, 1, 2, 3, 3, atan2(player.y - enemy[13].y, player.x - enemy[13].x));
		if (enemy[14].flag == 1)createEnemyShot(enemy[14].x, enemy[14].y, 1, 2, 3, 3, atan2(player.y - enemy[14].y, player.x - enemy[14].x));
	}
	if (t >= 1050 && t < 1170 && t % 40 == 0) {
		if (enemy[15].flag == 1)createEnemyShot(enemy[15].x, enemy[15].y, 1, 2, 3, 3, atan2(player.y - enemy[15].y, player.x - enemy[15].x));
		if (enemy[16].flag == 1)createEnemyShot(enemy[16].x, enemy[16].y, 1, 2, 3, 3, atan2(player.y - enemy[16].y, player.x - enemy[16].x));
		if (enemy[17].flag == 1)createEnemyShot(enemy[17].x, enemy[17].y, 1, 2, 3, 3, atan2(player.y - enemy[17].y, player.x - enemy[17].x));
	}

	//3 e1460
	if (t >= 1350 && t < 1380 && t % 30 == 0) {
		if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 3, 8, 3, 2, atan2(player.y - enemy[18].y, player.x - enemy[18].x));
		if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 3, 8, 3, 2, atan2(player.y - enemy[19].y, player.x - enemy[19].x));
		if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y, 3, 8, 3, 2, atan2(player.y - enemy[10].y, player.x - enemy[20].x));

	}

	if (t >= 1430 && t < 1460 && t % 30 == 0) {
		if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 2, 8, 3, 2, atan2(player.y - enemy[18].y, player.x - enemy[18].x));
		if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 2, 8, 3, 2, atan2(player.y - enemy[19].y, player.x - enemy[19].x));
		if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y, 2, 8, 3, 2, atan2(player.y - enemy[10].y, player.x - enemy[20].x));

	}
	if (t >= 1510 && t < 1540 && t % 30 == 0) {
		if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 3, 8, 3, 2, atan2(player.y - enemy[18].y, player.x - enemy[18].x));
		if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 3, 8, 3, 2, atan2(player.y - enemy[19].y, player.x - enemy[19].x));
		if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y, 3, 8, 3, 2, atan2(player.y - enemy[10].y, player.x - enemy[20].x));

	}

	if (t >= 1590 && t < 1620 && t % 30 == 0) {
		if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 2, 8, 3, 2, atan2(player.y - enemy[18].y, player.x - enemy[18].x));
		if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 2, 8, 3, 2, atan2(player.y - enemy[19].y, player.x - enemy[19].x));
		if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y, 2, 8, 3, 2, atan2(player.y - enemy[10].y, player.x - enemy[20].x));

	}
	if (t >= 1670 && t < 1700 && t % 30 == 0) {
		//if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 3, 6, 3, 2, 1.11);
		//if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 3, 6, 3, 2, 1.11);
		//if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y, 3, 6, 3, 2, 1.11);
		if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 3, 8, 3, 2, atan2(player.y - enemy[18].y, player.x - enemy[18].x));
		if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 3, 8, 3, 2, atan2(player.y - enemy[19].y, player.x - enemy[19].x));
		if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y, 3, 8, 3, 2, atan2(player.y - enemy[10].y, player.x - enemy[20].x));

	}

	if (t >= 1750 && t < 1780 && t % 30 == 0) {
		//if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 2, 6, 3, 2, 1.21);
		//if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 2, 6, 3, 2, 1.21);
		//if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y. 2, 6, 3, 2, 1.21);
		if (enemy[18].flag == 1)createEnemyShot(enemy[18].x, enemy[18].y, 2, 8, 3, 2, atan2(player.y - enemy[18].y, player.x - enemy[18].x));
		if (enemy[19].flag == 1)createEnemyShot(enemy[19].x, enemy[19].y, 2, 8, 3, 2, atan2(player.y - enemy[19].y, player.x - enemy[19].x));
		if (enemy[20].flag == 1)createEnemyShot(enemy[20].x, enemy[20].y, 2, 8, 3, 2, atan2(player.y - enemy[10].y, player.x - enemy[20].x));

	}
	
	//4		s 1700 end 1790
	if (t >= 2020 && t < 2110 && t % 30 == 0) {
		if (enemy[21].flag == 1)createEnemyShot(enemy[21].x, enemy[21].y, 1, 4, 3, 3, atan2(enemy[21].y, enemy[21].x));
		if (enemy[22].flag == 1)createEnemyShot(enemy[22].x, enemy[22].y, 1, 4, 3, 3, atan2(enemy[22].y, enemy[22].x));
		if (enemy[23].flag == 1)createEnemyShot(enemy[23].x, enemy[23].y, 1, 4, 3, 3, atan2(enemy[23].y, enemy[23].x));

		if (enemy[24].flag == 1)createEnemyShot(enemy[24].x, enemy[24].y, 1, 4, 3, 3, atan2(enemy[24].y, enemy[24].x));
		if (enemy[25].flag == 1)createEnemyShot(enemy[25].x, enemy[25].y, 1, 4, 3, 3, atan2(enemy[25].y, enemy[25].x));
		if (enemy[26].flag == 1)createEnemyShot(enemy[26].x, enemy[26].y, 1, 4, 3, 3, atan2(enemy[26].y, enemy[26].x));
	}
	if (t >= 2160 && t < 2250 && t % 30 == 0) {
		if (enemy[21].flag == 1)createEnemyShot(enemy[21].x, enemy[21].y, 1, 4, 3, 3, atan2(enemy[21].y, enemy[21].x));
		if (enemy[22].flag == 1)createEnemyShot(enemy[22].x, enemy[22].y, 1, 4, 3, 3, atan2(enemy[22].y, enemy[22].x));
		if (enemy[23].flag == 1)createEnemyShot(enemy[23].x, enemy[23].y, 1, 4, 3, 3, atan2(enemy[23].y, enemy[23].x));

		if (enemy[24].flag == 1)createEnemyShot(enemy[24].x, enemy[24].y, 1, 4, 3, 3, atan2(enemy[24].y, enemy[24].x));
		if (enemy[25].flag == 1)createEnemyShot(enemy[25].x, enemy[25].y, 1, 4, 3, 3, atan2(enemy[25].y, enemy[25].x));
		if (enemy[26].flag == 1)createEnemyShot(enemy[26].x, enemy[26].y, 1, 4, 3, 3, atan2(enemy[26].y, enemy[26].x));
	}
	//ìØÇ∂Ç±Ç∆Ç‡Ç§ÇQâÒ

	//5 end2810
	if (t >= 2560 && t < 2810 && t % 60 == 0) {
		if (enemy[27].flag == 1)createEnemyShot(enemy[27].x, enemy[27].y, 1, 2, 3, 3, atan2(player.y - enemy[27].y, player.x - enemy[27].x));
		if (enemy[28].flag == 1)createEnemyShot(enemy[28].x, enemy[28].y, 1, 2, 3, 3, atan2(player.y - enemy[28].y, player.x - enemy[28].x));
		if (enemy[29].flag == 1)createEnemyShot(enemy[29].x, enemy[29].y, 1, 2, 3, 3, atan2(player.y - enemy[29].y, player.x - enemy[29].x));
		if (enemy[30].flag == 1)createEnemyShot(enemy[30].x, enemy[30].y, 1, 2, 3, 3, atan2(player.y - enemy[30].y, player.x - enemy[30].x));
		if (enemy[31].flag == 1)createEnemyShot(enemy[31].x, enemy[31].y, 1, 2, 3, 3, atan2(player.y - enemy[31].y, player.x - enemy[31].x));
		if (enemy[32].flag == 1)createEnemyShot(enemy[32].x, enemy[32].y, 1, 2, 3, 3, atan2(player.y - enemy[32].y, player.x - enemy[32].x));
		if (enemy[33].flag == 1)createEnemyShot(enemy[33].x, enemy[33].y, 1, 2, 3, 3, atan2(player.y - enemy[33].y, player.x - enemy[33].x));
		if (enemy[34].flag == 1)createEnemyShot(enemy[34].x, enemy[34].y, 1, 2, 3, 3, atan2(player.y - enemy[34].y, player.x - enemy[34].x));
		if (enemy[35].flag == 1)createEnemyShot(enemy[35].x, enemy[35].y, 1, 2, 3, 3, atan2(player.y - enemy[35].y, player.x - enemy[35].x));
		if (enemy[36].flag == 1)createEnemyShot(enemy[36].x, enemy[36].y, 1, 2, 3, 3, atan2(player.y - enemy[36].y, player.x - enemy[36].x));
	}

	//6.1
	if (t >= 2910 && t < 3090 && t % 30 == 0) {
		if (enemy[37].flag == 1)createEnemyShot(enemy[37].x, enemy[37].y, 1, 2, 3, 3, atan2(player.y - enemy[37].y, player.x - enemy[37].x));
		if (enemy[38].flag == 1)createEnemyShot(enemy[38].x, enemy[38].y, 1, 2, 3, 3, atan2(player.y - enemy[38].y, player.x - enemy[38].x));
		if (enemy[39].flag == 1)createEnemyShot(enemy[39].x, enemy[39].y, 1, 2, 3, 3, atan2(player.y - enemy[39].y, player.x - enemy[39].x));

		if (enemy[40].flag == 1)createEnemyShot(enemy[40].x, enemy[40].y, 1, 2, 3, 3, atan2(player.y - enemy[40].y, player.x - enemy[40].x));
		if (enemy[41].flag == 1)createEnemyShot(enemy[41].x, enemy[41].y, 1, 2, 3, 3, atan2(player.y - enemy[41].y, player.x - enemy[41].x));
		if (enemy[42].flag == 1)createEnemyShot(enemy[42].x, enemy[42].y, 1, 2, 3, 3, atan2(player.y - enemy[42].y, player.x - enemy[42].x));
	}
	//6.2
	if (t >= 2910 && t < 3090 && t % 30 == 0) {
		if (enemy[43].flag == 1)createEnemyShot(enemy[43].x, enemy[43].y, 2, 6, 3, 2, 1.21);
		if (enemy[44].flag == 1)createEnemyShot(enemy[44].x, enemy[44].y, 2, 6, 3, 2, 1.21);
		if (enemy[45].flag == 1)createEnemyShot(enemy[45].x, enemy[45].y, 2, 6, 3, 2, 1.21);
	}

	//7
	if (t >= 3310 && t % 60 == 0) {
		if (enemy[46].flag == 1)createEnemyShot(enemy[46].x, enemy[46].y, 3, 6, 3, 3, 1.11);
		if (enemy[47].flag == 1)createEnemyShot(enemy[47].x, enemy[47].y, 3, 6, 3, 3, 1.11);
		if (enemy[48].flag == 1)createEnemyShot(enemy[48].x, enemy[48].y, 3, 6, 3, 3, 1.11);
		if (enemy[50].flag == 1)createEnemyShot(enemy[50].x, enemy[50].y, 3, 6, 3, 3, 1.11);
		if (enemy[51].flag == 1)createEnemyShot(enemy[51].x, enemy[51].y, 3, 6, 3, 3, 1.11);
		if (enemy[52].flag == 1)createEnemyShot(enemy[52].x, enemy[52].y, 3, 6, 3, 3, 1.11);
	}
	if (t >= 3310 && t % 7 == 0) {
		if (enemy[49].flag == 1)createEnemyShot(enemy[49].x, enemy[49].y, 1, 4, 3, 1, 1.11);
	}

	//8(ñ¢íË)

	//ìñÇΩÇËîªíËÇ‚ÉtÉâÉOÇÃä«óùìô
	for (int i = 0; i < ENEMYMAX; i++) {
		if (enemy[i].x < -200 || 800 < enemy[i].x || enemy[i].y < -100 || 650 < enemy[i].y) enemy[i].flag = 0;
		if (enemy[i].hp <= 0) enemy[i].flag = 0;

		//collision1
		if (collision1(enemy, playershot, i) == 1) {
			score++;
		}
		/*
		if (collision2(player, enemyshot) == 1) {
			if (enemyshot->type == 1) {
				if (player.hp > 4) {
					player.hp -= 4;
					hp_g -= 8;
				}
				else {
					player.hp = 0;
				}
			}
			if (enemyshot->type == 2) {
				if (player.hp > 2) {
					player.hp -= 2;
					hp_g -= 4;
				}
				else {
					player.hp = 0;
				}
			}
			if (enemyshot->type == 3) {
				if (player.hp > 1) {
					player.hp --;
					hp_g -= 2;
				}
				else {
					player.hp = 0;
				}
			}
		}
		*/

		//collision2
		if(player.flag == 1)player.hp -= collision2(player, enemyshot);
		

		//collision3
		if (collision3(player, enemy, i) == 1) {
			if (player.hp >= 1) player.hp--;
		}

		//collision4
		if (collision4(playersword, enemy, i) == 1 && enemy[i].cnt == 0) {
			enemy[i].cnt = t;
			enemy[i].hp -= 5;
			score += 100;
		}
		if (t == enemy[i].cnt + 20)enemy[i].cnt = 0;


		//hp_gÇÃçXêV
		if(player.hp >= 0) hp_g = 575 + player.hp * 2;
	}
}

void enemy_Draw() {
	//ìGÇÃï`âÊ

	for (int i = 0; i < ENEMYMAX; i++) {
		if (enemy[i].flag == 1 && enemy[i].type == 1) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_R, TRUE);
		}
		if (enemy[i].flag == 1 && enemy[i].type == 2) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_G, TRUE);
			//DrawBox(enemy[i].x + 19, enemy[i].y + 25, enemy[i].x + 29, enemy[i].y + 35, GetColor(0, 0, 255), TRUE);	
		}
		if (enemy[i].flag == 1 && enemy[i].type == 3) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_B, TRUE);
		}
	}


	//èIóπéûÇÃèàóù ç≈å„ÇÃìGÇ™è¡Ç¶ÇÈñîÇÕé©ã@ëÃóÕÇ™ÇOÇ…Ç»Ç¡ÇΩéû
	if (enemy[46].flag == 0 && enemy[47].flag == 0 &&
		enemy[48].flag == 0 && enemy[49].flag == 0 &&
		enemy[50].flag == 0 && enemy[51].flag == 0 && enemy[52].flag == 0 || player.hp <= 0) {
		finish_t++;;
	}
	if (finish_t >= 100) {
		DrawFormatString(225, 300, GetColor(0, 255, 0), "YOUR SCORE %d", score);
		if (player.flag == 0)	DrawFormatString(235, 250, GetColor(255, 0, 0), "GAME OVER");
		if (player.flag == 1)	DrawFormatString(235, 250, GetColor(255, 165, 0), "GAME CLEAR");

	}
	if (finish_t >= 200 && hp_g > 575) {
		player.hp -= 1;
		score += 20;
		hp_g = 575 + player.hp * 2;
	}
	if (finish_t >= 400) DrawFormatString(225, 350, GetColor(0, 255, 0), "YOUR RANK ");

	if (finish_t >= 450) {
		if (score >= 7800)DrawFormatString(330, 350, GetColor(255, 255, 255), "S");
		if (score < 7800 && score >= 7200)DrawFormatString(330, 350, GetColor(255, 255, 255), "A");
		if (score < 7200 && score >= 6700)DrawFormatString(330, 350, GetColor(255, 255, 255), "B");
		if (score < 6700 && score >= 6300)DrawFormatString(330, 350, GetColor(255, 255, 255), "C");
		if (score < 6300 && score >= 6000)DrawFormatString(330, 350, GetColor(255, 255, 255), "D");
		if (score < 6000 && score >= 0)DrawFormatString(330, 350, GetColor(255, 255, 255), "E");

	}
	if (finish_t >= 500) {
		DrawFormatString(180, 400, GetColor(255, 255, 255), "RESTART: Z   EXIT: X");

	}

	t++;

}

void enemy_Finalize() {
	DeleteGraph(enemy_R);
	DeleteGraph(enemy_G);
	DeleteGraph(enemy_B);
}

