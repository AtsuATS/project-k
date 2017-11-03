//âòÇ≠ÇƒÇ∑Ç¢Ç‹ÇπÇÒÇÀ
//å„Ç≈èëÇ´íºÇ∑ÇÃÇ≈ç°ÇÕÇ±ÇÍÇ≈óeéÕÇµÇƒ

#include "DxLib.h"
#include <math.h>
#include "BaseUnit.h"
#include "playersword.h"
#include "calculation.h"
#include "grobal.h"
#define R 40


BaseSword playersword;
double NOWDIGANGLE,W_NOWDIGANGLE;
int NOWFLAME;
int playersword_GF;

void createPlayerSword(float px, float py,int pattern) {

	if (pattern == 1||pattern==3) {
		if (playersword.flag == 0) {
			playersword.sdig = -225;
			if(pattern==3)playersword.gdig =45;
			else {
				playersword.gdig = -45;
				playersword.flame = 8;
				playersword.l_or_r = 'r';
				playersword.flag = 1;
			}
			NOWDIGANGLE = playersword.sdig;
			playersword.x = px+R*cos(to_rad(NOWDIGANGLE));
			playersword.y = py+R*sin(to_rad(NOWDIGANGLE));
			playersword.pattern = pattern;
			NOWFLAME = 0;
		}
	}
	else if (pattern == 2) {
		if (playersword.flag == 0) {
			playersword.sdig = 45;
			playersword.gdig = 225;			
			NOWDIGANGLE = playersword.sdig;
			playersword.x = px + R*cos(to_rad(NOWDIGANGLE));
			playersword.y = py + R*sin(to_rad(NOWDIGANGLE));
			playersword.l_or_r = 'l';
			playersword.flame = 8;
			playersword.pattern = pattern;
			playersword.flag = 1;
			NOWFLAME = 0;
		}
	}
	if (pattern == 3) {
		if (playersword.flag == 0) {
			playersword.wsdig = 45;
			playersword.wgdig = 315;
			W_NOWDIGANGLE = playersword.wsdig;
			playersword.wx = px + R*cos(to_rad(W_NOWDIGANGLE));
			playersword.wy = py + R*sin(to_rad(W_NOWDIGANGLE));
			playersword.l_or_r = 'w';
			playersword.wflame = 16;
			playersword.flag = 1;
			player.mp -= 2;
		}
	}
	return;
}

//èâä˙âª
void playersword_Initialize() {
	playersword_GF = LoadGraph("GF\\sword.png");
}

//ìÆÇ´ÇåvéZÇ∑ÇÈ
void playersword_Update(float px, float py) {
	if (playersword.l_or_r == 'w') {
		if (playersword.wflame < NOWFLAME) {
			playersword.flag = 0;
		}
	}
	else if (playersword.flame < NOWFLAME) {
		playersword.flag = 0;
	}
	 if (playersword.flag == 1) {
		if (playersword.l_or_r == 'r' || playersword.l_or_r == 'w') {
			if (playersword.l_or_r == 'r')
				NOWDIGANGLE += (playersword.gdig - playersword.sdig) / playersword.flame;
			else
				NOWDIGANGLE += (playersword.wgdig - playersword.wsdig) / playersword.wflame;

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
		if (playersword.l_or_r == 'w') {
			W_NOWDIGANGLE -= (playersword.wgdig - playersword.wsdig) / playersword.wflame;

			playersword.wx = px + R*cos(to_rad(W_NOWDIGANGLE));
			playersword.wy = py + R*sin(to_rad(W_NOWDIGANGLE));
		}
	}
}

//ï`âÊÇ∑ÇÈ
void playersword_Draw() {
	if (playersword.flag == 1) {
		DrawRotaGraph(playersword.x, playersword.y, 1, to_rad(NOWDIGANGLE + 90), playersword_GF, TRUE);
		if(playersword.pattern==3) DrawRotaGraph(playersword.wx, playersword.wy, 1, to_rad(W_NOWDIGANGLE + 90), playersword_GF, TRUE);
	}
}

//èIóπèàóùÇÇ∑ÇÈ
void playersword_Finalize() {
	DeleteGraph(playersword_GF);
}