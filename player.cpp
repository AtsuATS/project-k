#include "DxLib.h"
#include "BaseUnit.h"
#include "key.h"
#include "playersword.h"
#include "playershot.h"
#include "grobal.h"
#include <math.h>

BaseUnit player;
int player_GF;
static int PShotPushCnt;
static int PSwordPushCut;

int hp_g = 0; //HPのゲージ

static int player_flag[4];//斜めかどうかを判断するためのフラグ

static float calx, caly;

//初期化
void player_Initialize() {
	player_GF = LoadGraph("sozai\\GF\\自機.png");
	player.flag = 1;
	player.hp = 100;
	player.x = 275;
	player.y = 500;
	player.speed = 5;

	calx = caly = 0;

	PShotPushCnt = 0;
	PSwordPushCut = 0;
}

//動きを計算する
void player_Update() {

	for (int i = 0; i < 4; i++) {
		player_flag[i] = 0;

	if (keyboard_Get(KEY_INPUT_UP) > 0) {
		player_flag[0] = -player.speed;
		if (keyboard_Get(KEY_INPUT_LSHIFT) > 0 || keyboard_Get(KEY_INPUT_RSHIFT) > 0)
			player_flag[0] += 2;
	}
	if (keyboard_Get(KEY_INPUT_DOWN) > 0) {
		player_flag[2] = player.speed;
		if (keyboard_Get(KEY_INPUT_LSHIFT) > 0 || keyboard_Get(KEY_INPUT_RSHIFT) > 0)
			player_flag[2] -= 2;
	}
	if (keyboard_Get(KEY_INPUT_RIGHT) > 0) {
		player_flag[3] = player.speed;
		if (keyboard_Get(KEY_INPUT_LSHIFT) > 0 || keyboard_Get(KEY_INPUT_RSHIFT) > 0)
			player_flag[3] -= 2;
	}
	if (keyboard_Get(KEY_INPUT_LEFT) > 0) {
		player_flag[1] = -player.speed;
		if (keyboard_Get(KEY_INPUT_LSHIFT) > 0 || keyboard_Get(KEY_INPUT_RSHIFT) > 0)
			player_flag[1] += 2;
	}
}
	//斜め移動の時
	if ((player_flag[0] != 0 || player_flag[2] != 0) && (player_flag[1] != 0 || player_flag[3] != 0)) 
	{
		for (int i = 0; i <= 2; i += 2) {
			caly +=  (float)player_flag[i] /(float)sqrt(2.0);
			calx +=  (float)player_flag[i + 1] /(float)sqrt(2.0);
		}
	}
	else {
		for (int i = 0; i <= 2; i += 2) {
			caly += (float)player_flag[i];
			calx += (float)player_flag[i + 1];
		}
	}

	if (!((player.x + calx) < 0 || (player.x + calx) > 550 || (player.y + caly) < 0 || (player.y + caly) > 600)) {
		player.x += calx;
		player.y += caly;
	}
	if (calx != 0 || caly != 0) {
		calx = 0;
		caly = 0;
	}

	if (keyboard_Get(KEY_INPUT_SPACE) > 0) {
		if (PShotPushCnt % 100 == 0) {
			createPlayerShot(player.x, player.y);
		}
		PShotPushCnt++;
	}
	else {
		if (PShotPushCnt != 0) {
			PShotPushCnt = 0;
		}
	}

	//追加(やられたときの処理)
	if (player.hp <= 0) {
		player.flag = 0;
		player.flag = 1;
		player.hp = 100;
		hp_g = 0;
		player.x = 275;
		player.y = 500;
		
	}

	if (keyboard_Get(KEY_INPUT_Z) > 0) {
		if (PSwordPushCut % 10000 == 0) {
			createPlayerSword(player.x, player.y, 1);
		}
		PSwordPushCut++;
	}
	else if (keyboard_Get(KEY_INPUT_X) > 0) {
		if (PSwordPushCut % 10000 == 0) {
			createPlayerSword(player.x, player.y, 2);
		}
		PSwordPushCut++;
	}
	else {
		if (PSwordPushCut != 0) {
			PSwordPushCut = 0;
		}
	}
	playersword_Update(player.x, player.y);
}


//描画する
void player_Draw() {
	if (player.flag == 1) {
		DrawCircle(player.x, player.y, 10, GetColor(255, 255, 255), TRUE);
		DrawRotaGraphF(player.x, player.y, 1, 0, player_GF, TRUE);
		DrawFormatString(650, 90, GetColor(0, 255, 0), "HP %d", player.hp);
		DrawBox(550, hp_g, 600, 600, GetColor(200, 0, 0), TRUE);
		DrawBox(player.x, player.y -2, player.x + 50, player.y + 2 , GetColor(200, 0, 0), TRUE);
		
	}
}

//終了処理をする
void player_Finalize() {
	DeleteGraph(player_GF);
}