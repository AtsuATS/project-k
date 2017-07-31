#include "DxLib.h"
#include "grobal.h"
#include "enemyshot.h"
#include "enemy_act.h"
#include "BaseUnit.h"
#define _USE_MATH_DEFINES
#include <math.h>

Enemy_shot enemyshot[EMAXSHOT];
int enemyshot_GF1, enemyshot_GF2, enemyshot_GF3;


void createEnemyShot(float ex , float ey, int n, int p, int s, int t, double ang) { //n‚Í’e‚Ì”,p‚Íƒpƒ^[ƒ“,s‚ÍƒXƒs[ƒh,ang‚ÍŠp“x
	static int i = 1, m = 1;//Šp“x‚ğ‡”Ô‚É—^‚¦‚é‚½‚ß‚Ì•Ï”
	int q = 1;
	int num = 0;//‰½”­o‚µ‚½‚©”‚¦‚é•Ï”
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
			else {
				enemyshot[j].ang = ang;
			}
			num++;

			if (num == n)break;
		}
	}
}

//‰Šú‰»
void enemyshot_Initialize() {
	enemyshot_GF1 = LoadGraph("GF\\Ô‹Ê¬.png");
	enemyshot_GF2 = LoadGraph("GF\\—Î‹Ê¬.png");
	enemyshot_GF3 = LoadGraph("GF\\Â‹Ê¬.png");

	for (int i = 0; i < EMAXSHOT; i++) {
		enemyshot[i].flag = 0;
	}
}



//“®‚«‚ğŒvZ‚·‚é
void enemyshot_Update() {
	for (int i = 0; i < EMAXSHOT ; i++) {
		//’¼i
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 1) {
			enemyshot[i].y += enemyshot[i].speed;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//©‹@‘_‚¢
		if(enemyshot[i].flag == 1 && enemyshot[i].pattern == 2){
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang)-0.3;
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang)-0.2;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		
		//‚Î‚ç‚Ü‚«’e“I‚È(“G‚ª“®‚­‚Æ‚«‚É‰Â)
		if(enemyshot[i].flag == 1 && enemyshot[i].pattern == 3) {
			double ang = (enemyshot[i].ang * 2 * M_PI / 6);
			enemyshot[i].x += enemyshot[i].speed * cos(ang);
			enemyshot[i].y += enemyshot[i].speed * sin(ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//‰ñ“]
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 4) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//‰ñ“]2
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 5) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//‚R”­
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 6) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//‚Q”­
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 7) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang);
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang);
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
		//©‹@‘_‚¢{©‹@ŠO‚µ
		if (enemyshot[i].flag == 1 && enemyshot[i].pattern == 8) {
			enemyshot[i].x += enemyshot[i].speed * cos(enemyshot[i].ang) - 0.3;
			enemyshot[i].y += enemyshot[i].speed * sin(enemyshot[i].ang) - 0.2;
			if (enemyshot[i].y < -30 || enemyshot[i].y > 620 || enemyshot[i].x < -20 || 570 < enemyshot[i].x) {
				enemyshot[i].flag = 0;
			}
		}
	}
}

//•`‰æ‚·‚é
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



//I—¹ˆ—‚ğ‚·‚é
void enemyshot_Finalize() {
	
	DeleteGraph(enemyshot_GF1);
	DeleteGraph(enemyshot_GF2);
	DeleteGraph(enemyshot_GF3);
}