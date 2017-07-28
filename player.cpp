#include "DxLib.h"
#include "BaseUnit.h"
#include "key.h"
#include "player_sword.h"
#include "playershot.h"
#include "grobal.h"
#define _USE_MATH_DEFINES
#include <math.h>

BaseUnit player;
int player_GF;
static int PShotPushCnt;
static int PSwordPushCut_Z, PSwordPushCut_X;

int hp_g = 775; //HPのゲージ

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
	PSwordPushCut_Z = PSwordPushCut_X = 0;
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
		if (PShotPushCnt % 100 == 0 && player.flag == 1) {
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
		hp_g = 575;
		player.hp = 0;
		player.flag = 0;
		playershot->flag = 0;
	}

	if (keyboard_Get(KEY_INPUT_Z) > 0) {
		PSwordPushCut_Z++;
		if (PSwordPushCut_Z <= 1 && player.flag == 1) {
			createPlayerSword(player.x, player.y, 1);
		}
	}
	else if(PSwordPushCut_Z != 0) {
		PSwordPushCut_Z = 0;
	}
	if (keyboard_Get(KEY_INPUT_X) > 0) {
		PSwordPushCut_X++;
		if (PSwordPushCut_X <= 1 && player.flag == 1) {
			createPlayerSword(player.x, player.y, 2);
		}
	}
	else if (PSwordPushCut_X != 0) {
		PSwordPushCut_X = 0;
	}
	playersword_Update(player.x, player.y);
}


//描画する
void player_Draw() {
	if (player.flag == 1) {
		DrawRotaGraphF(player.x, player.y, 1, 0, player_GF, TRUE);
		//DrawBox(playersword.x, playersword.y, playersword.x + 40 * cos(NOWDIGANGLE * 180 / M_PI), playersword.y + 40 * sin(NOWDIGANGLE * 180 / M_PI), GetColor(222, 41, 0), TRUE);
	}
}

//終了処理をする
void player_Finalize() {
	DeleteGraph(player_GF);
}