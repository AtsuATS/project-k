//#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "grobal.h"
#include "enemy_act.h"
#include "enemyshot.h"
#include "calculation.h"
#define _USE_MATH_DEFINES
#define SECOND 60
#include <math.h>
#include  <stdio.h>

Enemy_status enemy[ENEMYMAX];

int enemy_R, enemy_G, enemy_B, pointer;
int score = 0;
int t = 0;
int Boss_t = 0;//Boss戦開始で動き出す
int finish_t = 0;//終わった時に動き出す
int GP_flag[3] = { {0} }; //汎用フラグ
int bombcnt[2]; //ボム３が起動したときのカウントを記憶
int p_invi[2];
int se;
int p_x, p_y,e_x,e_y;
int first = 150;
int second = first + 150;
int ret_rand ;
int waittime;
int theta = 0;

FILE *fp;
char *fname = "enemystatus.csv";

int collision1(Enemy_status enemy[], BaseShot playershot[], int i) {
	float distance_x[ENEMYMAX], distance_y[ENEMYMAX], range[ENEMYMAX];

	for (int j = 0; j < PMAXSHOT; j++) {
		if (playershot[j].flag == 1 && enemy[i].flag == 1) {

			//円
			distance_x[j] = (playershot[j].x) - (enemy[i].x + 24);
			distance_y[j] = (playershot[j].y) - (enemy[i].y + 30);
			range[j] = sqrt(distance_x[j] * distance_x[j] + distance_y[j] * distance_y[j]);

			//当たり判定（円）
			if (range[j] <= 20) {
				playershot[j].flag = 0;
				enemy[i].hp -= playershot[j].power*bombmagnification;
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

			if (range2[j] <= 15 && enemyshot[j].type == 1) {
				enemyshot[j].flag = 0;
				return (int)(5.0* (1.0 / bombmagnification));
			}
			else if (range2[j] <= 15 && enemyshot[j].type == 2) {
				enemyshot[j].flag = 0;
				return (int)(3.0* (1.0 / bombmagnification));
			}
			else if (range2[j] <= 15 && enemyshot[j].type == 3) {
				enemyshot[j].flag = 0;
				return (int)(2.0*(1.0 / bombmagnification));
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
int collision4(BaseSword playersword, Enemy_status enemy[], int i) {//BaseUnit player を Basesword playerswordに変更
	float distance_x4[ENEMYMAX], distance_y4[ENEMYMAX];
	float psx = playersword.x + 40 * cos(NOWDIGANGLE * 180 / M_PI);
	float psy = playersword.y + 40 * sin(NOWDIGANGLE * 180 / M_PI);

	for (int j = 0; j < ENEMYMAX; j++) {
		if (enemy[i].flag == 1 && playersword.flag == 1) {  //if(enemy[i].flag == 1 && playersword.flag == 1) に変更
			distance_x4[j] = (psx) - (enemy[i].x + 24);
			if (distance_x4[j] < 0) distance_x4[j] *= -1;
			distance_y4[j] = (psy + 5) - (enemy[i].y + 30);
			if (distance_y4[j] < 0) distance_y4[j] *= -1;

			if (psx > 530 || psx < 20 || psy > 590 || psy < 10)
				return 0;

			if (distance_x4[j] < 40 && distance_y4[j] < 15) {
				PlaySoundMem(se, DX_PLAYTYPE_BACK);
				return 1;
			}
		}
	}
	return 0;
}

//ボム１の当たり判定関数
int bomb_collision1(BaseSword playersword, Enemy_status enemy[], Enemy_shot enemyshot[], int i) {
	float distance_x4[ENEMYMAX], distance_y4[ENEMYMAX];
	float distance_x5[EMAXSHOT], distance_y5[EMAXSHOT];
	float psx = playersword.x + 40 * cos(NOWDIGANGLE * 180 / M_PI);
	float psy = playersword.y + 40 * sin(NOWDIGANGLE * 180 / M_PI);

	for (int k = 0; k < EMAXSHOT; k++) {
		if (enemyshot[k].flag == 1) {
			distance_x5[k] = (psx)-(enemyshot[k].x + 24);
			if (distance_x5[k] < 0) distance_x5[k] *= -1;
			distance_y5[k] = (psy + 5) - (enemyshot[k].y + 30);
			if (distance_y5[k] < 0) distance_y5[k] *= -1;

			if (distance_x5[k] < 40 && distance_y5[k] < 15) {
				enemyshot[k].flag = 0;
			}
		}
	}

	for (int j = 0; j < ENEMYMAX; j++) {
		if (enemy[i].flag == 1 && playersword.flag == 1) {
			distance_x4[j] = (psx)-(enemy[i].x + 24);
			if (distance_x4[j] < 0) distance_x4[j] *= -1;
			distance_y4[j] = (psy + 5) - (enemy[i].y + 30);
			if (distance_y4[j] < 0) distance_y4[j] *= -1;

			if (psx > 530 || psx < 20 || psy > 590 || psy < 10)
				return 0;

			if (distance_x4[j] < 40 && distance_y4[j] < 15) {
				PlaySoundMem(se, DX_PLAYTYPE_BACK);
				return 1;
			}
		}
	}
	return 0;
}

//ボム３の当たり判定関数
int bomb_collision2(Enemy_status enemy[], Enemy_shot enemyshot[], int i) {
	for (int j = 0; j < EMAXSHOT; j++) {
		if (enemyshot[j].flag == 1) {
			enemyshot[j].flag = 0;
		}
	}
	
	if ((enemy[i].x >= 50 && enemy[i].x < 530) && (enemy[i].y >= 20 && enemy[i].y < 590)) {
		return 1;
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void enemy_Initialize() {
	srand((unsigned)time(NULL));

	if ((fp = fopen(fname, "r")) == NULL) {
		exit(1);
	}

	while (fgetc(fp) != '\n');

	for (int i = 0; i <= ENEMYMAX; i++) {
		fscanf(fp, "%*d,%d,%d,%f,%f,%d,%d\n",&(enemy[i].hp),&(enemy[i].speed),&(enemy[i].x),&(enemy[i].y),&(enemy[i].flag),&(enemy[i].type) );
	}
	fclose(fp);
	enemy_R = LoadGraph("GF\\敵赤仮.png");
	enemy_G = LoadGraph("GF\\敵緑仮.png");
	enemy_B = LoadGraph("GF\\敵青仮.png");
	pointer = LoadGraph("GF\\point.png");

	se = LoadSoundMem("BGM\\tekikougeki.wav");

	for (int i = 0; i < 3; i++) {
		GP_flag[i] = 0;
	}
	for (int i = 0;i < ENEMYMAX; i++) {
		for (int j = 0; j < 8; j++) {
			enemy[i].act[j]=0;
		}
	}

}

void enemy_Update() {

	//引数情報
	//３発　１．１１　２発　１．２１
	//自機狙いの角度・・・・atan2(player.y - enemy[i].y, player.x - enemy[i].x)
	//円状の角度・・・・atan2(enemy[i].y, enemy[i].x)
	//ばらまき・・・sqrt(x + y)
	//nの引数・・・敵の数　＊　一体の敵の打つ弾の数
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//行動
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
	if (t == 2410)enemy[27].act[3] = 0;
	if (t == 2410)enemy[28].act[3] = 0;
	if (t == 2410)enemy[29].act[3] = 0;
	if (t == 2410)enemy[30].act[3] = 0;
	if (t == 2410)enemy[31].act[3] = 0;

	if (t == 2410)enemy[32].act[3] = 0;
	if (t == 2410)enemy[33].act[3] = 0;
	if (t == 2410)enemy[34].act[3] = 0;
	if (t == 2410)enemy[35].act[3] = 0;
	if (t == 2410)enemy[36].act[3] = 0;

	if (t >= 2410 && enemy[27].flag == 1) enemy_act3(&enemy[27], 'l');
	if (t >= 2410 && enemy[32].flag == 1) enemy_act3(&enemy[32], 'r');
	if (t >= 2425 && enemy[28].flag == 1) enemy_act3(&enemy[28], 'l');
	if (t >= 2425 && enemy[33].flag == 1) enemy_act3(&enemy[33], 'r');
	if (t >= 2440 && enemy[29].flag == 1) enemy_act3(&enemy[29], 'l');
	if (t >= 2440 && enemy[34].flag == 1) enemy_act3(&enemy[34], 'r');
	if (t >= 2455 && enemy[30].flag == 1) enemy_act3(&enemy[30], 'l');
	if (t >= 2455 && enemy[35].flag == 1) enemy_act3(&enemy[35], 'r');
	if (t >= 2470 && enemy[31].flag == 1) enemy_act3(&enemy[31], 'l');
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

	//ボス前の敵の全滅を確認
	if (enemy[46].flag == 0 && enemy[47].flag == 0 &&
		enemy[48].flag == 0 && enemy[49].flag == 0 &&
		enemy[50].flag == 0 && enemy[51].flag == 0 &&
		enemy[52].flag == 0 &&enemy[53].flag==0&&Boss_t==0) {
		enemy[53].flag = 1;
		Boss_t -= 300;
	}

	//Boss戦
	//第1
	if (enemy[53].flag == 1) {
		if (/*(0<=Boss_t&&Boss_t <= first * SECOND)||*/enemy[53].hp>150 && Boss_t >= 0) {
			if (GP_flag[0] == 0) {
			     enemy_act5(&enemy[53]);
				 if (enemy[53].y >= 150)GP_flag[0] = 1;
			}
			else {
				if (GP_flag[0] == 1) {
					waittime = 0;
					ret_rand = nrandom(SECOND * 8);
					if (ret_rand == 1) GP_flag[0] = 2;
					//else if (GP_flag[0] == 2);
					else enemy_act8(&enemy[53]);
				}
				else if (GP_flag[0] == 2) {
					GP_flag[0] = 3;
				}
				else if (GP_flag[0] == 3) {
					waittime++;
					if (waittime == SECOND * 2) {
						GP_flag[0] = 1;
					}
				}
			}
		}

		//第2
		else if (/*(first * SECOND < Boss_t&&Boss_t < second * SECOND)||*/enemy[53].hp<=150 && Boss_t >= 0) {
			if(GP_flag[2]!=3) enemy_act7(&enemy[53]);
			if (GP_flag[2] == 0) {
				waittime = 0;
				ret_rand = nrandom(SECOND * 1);
				if (ret_rand == 1) {
					GP_flag[2] = 1;
					p_x = player.x;
					p_y = player.y;
				}

				//攻撃(2)
				ret_rand = nrandom(SECOND * 4);
				if (ret_rand == 1) {
					GP_flag[2] = 3;
					e_x = enemy[53].x;
					e_y = enemy[53].y;
				}
			}
			else if (GP_flag[2] == 1) {
				waittime++;
				if (waittime == SECOND * 1) 
					GP_flag[2] = 2;
			}
			else if (GP_flag[2] == 2) 
				GP_flag[2] = 0;
			else if (GP_flag[2] == 3) {
				//左右の移動の選択
				if(e_x<225){//右
					if (enemy[53].x < 490) {
						enemy[53].x += enemy[53].speed*1.41;
						if ((Boss_t % 12)==0&&waittime<8) {
							waittime++;
							createEnemyShot(enemy[53].x, enemy[53].y, 1, 9, 6, 2, atan2(player.y - enemy[53].y, player.x - enemy[53].x));
						}
					}
					else GP_flag[2] = 0;
				}
				else if (e_x >= 225) {//左
					if (enemy[53].x > 60) {
						enemy[53].x -= enemy[53].speed*1.41;
						if ((Boss_t % 12) == 0&& waittime<8) {
							waittime++;
							createEnemyShot(enemy[53].x, enemy[53].y, 1, 9, 6, 2, atan2(player.y - enemy[53].y, player.x - enemy[53].x));
						}
					}
					else GP_flag[2] = 0;
				}
			}
		}
		else if (Boss_t <= second * SECOND) {

		}
		Boss_t++;
		boss_hp = 120+enemy[53].hp*1.2666666;
	}


	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//敵ショット////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	//同じこともう２回

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

	//ボスバトル
	/*if (Boss_t >= 0) {
		if (enemy[53].flag == 1) {
			//createEnemyShot関数入れる
		}
	}*/

	//参考
	//ex ey...座標　n...弾の個数　p...パターン　s...スピード　t...弾のタイプ　ang...角度
	
	//レーザー弾　攻撃(1),(2)
	//if (t >= 200 && t < 270 && enemy[53].flag == 1) enemy_act0(&enemy[53], 90);
	if (GP_flag[0]==2&&enemy[53].flag==1) {
		//if (enemy[53].flag == 1)
		createEnemyShot(enemy[53].x, enemy[53].y, 1, 9, 6, 2, atan2(player.y - enemy[53].y, player.x - enemy[53].x));
	}

	//自機狙いからの回転弾幕　　攻撃１
	if (/*0 <= Boss_t&&Boss_t <= first * SECOND*/enemy[53].hp>150 && Boss_t >= 0) {
		if (GP_flag[1] == 0) {
			if (GP_flag[0] == 1 && Boss_t % 3 == 0 && enemy[53].flag == 1) {
				createEnemyShot(enemy[53].x, enemy[53].y, 1, 11, 6, 1, 1.11);
			}
			if (Boss_t % (SECOND * 5) == 0) GP_flag[1] = 1;
		}
		else if (GP_flag[1] == 1) {
			if (GP_flag[0] == 1 && Boss_t % 5 == 0 && enemy[53].flag == 1) 
				createEnemyShot(enemy[53].x, enemy[53].y, 1, 2, 6, 3, atan2(player.y - enemy[53].y, player.x - enemy[53].x));
			
			if (Boss_t % (SECOND * 2) == 0) GP_flag[1] = 0;
		}
	}
	//if (t == 950) t = 340;

	//ポインタからの拡散弾幕　　攻撃2
	if (/*first * SECOND < Boss_t&&Boss_t < second * SECOND*/enemy[53].hp <= 150 && Boss_t >= 0) {
		if (GP_flag[2] == 2) 
			createEnemyShot(p_x-25, p_y-31, 20, 10, 6, 3, 1);
	}

	//当たり判定やフラグの管理等
	for (int i = 0; i < ENEMYMAX; i++) {
		if ((enemy[i].x < -200 || 800 < enemy[i].x || enemy[i].y < -100 || 650 < enemy[i].y)&&enemy[i].flag==1)
			enemy[i].flag = 0;
		if (enemy[i].hp <= 0&&enemy[i].flag==1) 
			enemy[i].flag = 0;

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
		if(player.flag == 1 && p_invi[1] != 1)player.hp -= collision2(player, enemyshot);
		

		//collision3
		if (enemy[53].flag != 1) {
			if (collision3(player, enemy, i) == 1) {
				if (player.hp >= 1 && p_invi[1] != 1) player.hp -= 1 * (1 / bombmagnification);
			}
		}

		//collision4
		if (collision4(playersword, enemy, i) == 1 && enemy[i].cnt == 0) {
			enemy[i].cnt = t;
			enemy[i].hp -= 5*bombmagnification;
			if (t < bombcnt[0] + 30 && bomb_collision1(playersword, enemy, enemyshot, i) == 1) {
				score += 50;
			}
			else {
				score += 100;
			}
		}
		if (t == enemy[i].cnt + 10)enemy[i].cnt = 0;



		//ボム１の処理
		if (player.type_bomb == 1) {
			if (t < bombcnt[0] + 30 && bomb_collision1(playersword, enemy, enemyshot, i) == 1) {

			}
		}
		if (t == bombcnt[0] + 30) {
			bombcnt[0] = 0;
		}

		//ボム３の処理
		if (bombflag[1] == 1) {
			if (bomb_collision2(enemy, enemyshot, i) == 1 && bombcnt[1] >= t) {
				enemy[i].hp -= 5 * bombmagnification;
				if (enemy[i].hp <= 0) score += 100;
			}
			if (bomb_collision2(enemy, enemyshot, i) == 1) {

			}	
		}
		if (t == bombcnt[1] + 420) {
			bombcnt[1] = 0;
			bombflag[1] = 0;
		}
		if (t == p_invi[0] + 480) {
			p_invi[0] = 0;
			p_invi[1] = 0;
		}

		//hp_gの更新
		if(player.hp >= 0) hp_g = 575 + player.hp * 2;


	}
}

void enemy_Draw() {
	//敵の描画

	for (int i = 0; i < ENEMYMAX; i++) {
		if (enemy[i].flag == 1 && enemy[i].type == 1) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_R, TRUE);
		}
		if (enemy[i].flag == 1 && enemy[i].type == 2) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_G, TRUE);
		}
		if (enemy[i].flag == 1 && enemy[i].type == 3) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_B, TRUE);
		}
	}


	//Boss戦手前の表示
	if (-200<=Boss_t&&Boss_t<0&&enemy[53].flag==1) {
		DrawFormatString(245, 300, GetColor(255, 0, 0), "BOSS BATTLE!!");
	}

	//boss戦のポインターの描画
	if (GP_flag[2] == 1) {
		DrawRotaGraph(p_x ,p_y, 1, 0, pointer, TRUE);
	}

	//終了時の処理 最後の敵が消える又は自機体力が０になった時
	if (player.hp <= 0||enemy[53].hp<=0){
		finish_t++;
	/*if (enemy[46].flag == 0 && enemy[47].flag == 0 &&
		enemy[48].flag == 0 && enemy[49].flag == 0 &&
		enemy[50].flag == 0 && enemy[51].flag == 0 && enemy[52].flag == 0 || player.hp <= 0) {*/
	}
	if (finish_t >= 100) {
		DrawFormatString(225, 300, GetColor(0, 255, 0), "YOUR SCORE %d", score);
		if (player.flag == 0)	DrawFormatString(240, 250, GetColor(255, 0, 0), "GAME OVER");
		if (player.flag == 1)	DrawFormatString(240, 250, GetColor(255, 165, 0), "GAME CLEAR");

	}
	if (finish_t >= 200 && (hp_g > 575||mp_g>575)) {
		if (hp_g > 575) {
			player.hp -= 1;
			score += 20;
			hp_g = 575 + player.hp * 2;
		}
		else if (hp_g <= 575) {
			if (finish_t % 3 == 0) {
				player.mp -= 1;
				mp_g = 575 + player.mp*6.67;
				score += 200;
			}
		}
		else;
	}
	if (finish_t >= 400) DrawFormatString(225, 350, GetColor(0, 255, 0), "YOUR RANK ");

	if (finish_t >= 450) {
		if (score >17000)DrawFormatString(330, 350, GetColor(255, 255, 255), "S");
		if (score <=17000 && score >15000)DrawFormatString(330, 350, GetColor(255, 255, 255), "A");
		if (score <=15000 && score >13000)DrawFormatString(330, 350, GetColor(255, 255, 255), "B");
		if (score <=13000 && score >11000)DrawFormatString(330, 350, GetColor(255, 255, 255), "C");
		if (score <=11000 && score >9000)DrawFormatString(330, 350, GetColor(255, 255, 255), "D");
		if (score <= 9000 && score >= 0)DrawFormatString(330, 350, GetColor(255, 255, 255), "E");

	}
	if (finish_t >= 500) {
		DrawFormatString(190, 400, GetColor(255, 255, 255), "RESTART: START   EXIT: SELECT");

	}

	t++;

}

void enemy_Finalize() {
	DeleteGraph(enemy_R);
	DeleteGraph(enemy_G);
	DeleteGraph(enemy_B);
	DeleteSoundMem(se);

}

