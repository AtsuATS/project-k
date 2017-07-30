//‰˜‚­‚Ä‚·‚¢‚Ü‚¹‚ñ‚Ë
//Œã‚Å‘‚«’¼‚·‚Ì‚Å¡‚Í‚±‚ê‚Å—eÍ‚µ‚Ä

#include "DxLib.h"
#include <math.h>
#include "BaseUnit.h"
#include "playersword.h"
#include "calculation.h"
#include "grobal.h"
#define R 40


BaseSword playersword;
double NOWDIGANGLE;
int NOWFLAME;
int playersword_GF;

void createPlayerSword(float px, float py,int pattern) {

	if (pattern == 1) {
		if (playersword.flag == 0) {
			playersword.sdig = -135-90;
			playersword.gdig =45-90;	
			NOWDIGANGLE = playersword.sdig;
			playersword.x = px+R*cos(to_rad(NOWDIGANGLE));
			playersword.y = py+R*sin(to_rad(NOWDIGANGLE));
			playersword.l_or_r = 'r';
			playersword.pattern = pattern;
			playersword.flame = 8;
			playersword.flag = 1;
			NOWFLAME = 0;
		}
	}
	else if (pattern == 2) {
		if (playersword.flag == 0) {
			playersword.sdig = -45+90;
			playersword.gdig = 135+90;			
			NOWDIGANGLE = playersword.sdig;
			playersword.x = px + R*cos(to_rad(playersword.sdig));
			playersword.y = py + R*sin(to_rad(playersword.sdig));
			playersword.l_or_r = 'l';
			playersword.flame = 8;
			playersword.pattern = pattern;
			playersword.flag = 1;
			NOWFLAME = 0;
		}
	}
	return;
}

//‰Šú‰»
void playersword_Initialize() {
	playersword_GF = LoadGraph("sozai\\GF\\sword.png");
}

//“®‚«‚ğŒvZ‚·‚é
void playersword_Update(float px, float py) {
	if (playersword.flame < NOWFLAME) {
		playersword.flag = 0;
	}
	else if (playersword.l_or_r == 'r') {
		NOWDIGANGLE += (playersword.gdig - playersword.sdig) / playersword.flame;

		playersword.x = px + R*cos(to_rad(NOWDIGANGLE));
		playersword.y = py + R*sin(to_rad(NOWDIGANGLE));
		NOWFLAME++;
	}
	else if (playersword.l_or_r == 'l') {
		NOWDIGANGLE -= (playersword.gdig - playersword.sdig) / playersword.flame;

		playersword.x = px + R*cos(to_rad(NOWDIGANGLE));
		playersword.y = py + R*sin(to_rad(NOWDIGANGLE));
		NOWFLAME++;
	}
}

//•`‰æ‚·‚é
void playersword_Draw() {
	if (playersword.flag == 1) {
		DrawRotaGraph(playersword.x, playersword.y, 1, to_rad(NOWDIGANGLE + 90), playersword_GF, TRUE);
	}
}

//I—¹ˆ—‚ğ‚·‚é
void playersword_Finalize() {
	DeleteGraph(playersword_GF);
}