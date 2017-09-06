#include "DxLib.h"
#include "BaseUnit.h"
#include "key.h"
#include "playersword.h"
#include "playershot.h"
#include "bomb.h"
#include "grobal.h"
#define _USE_MATH_DEFINES
#include <math.h>

BaseUnit player;
int player_GF;
static int PShotPushCnt;
static int PSwordPushCut_Z, PSwordPushCut_X;
static int BombtypePushCut;
static int BombPushCut;
float countflame;
int hp_g;
int mp_g;
int bomb2_g;
int bombmagnification; //ボムの倍率(通常時は1倍)
int bombflag[4]; //ボムが発動中かどうかを判断(ボム1は例外)
                 //[2],[3]はボム3の座標記録用
static int player_flag[4];//斜めかどうかを判断するためのフラグ

static float calx, caly;

//初期化
void player_Initialize() {
	player_GF = LoadGraph("GF\\自機.png");
	player.flag = 1;
	player.hp = 100;
	player.mp = 30;
	player.x = 275;
	player.y = 500;
	player.speed = 6.5;
	hp_g = 575 + player.hp * 2; //HPのゲージ
	mp_g = 575 + player.mp * 6.67;//MPのゲージ	
	countflame = 900;
	bomb2_g = bomb2_g = 640 + countflame*0.15; //ボム2のゲージ
	player.type_bomb = 1;
	bombmagnification = 1;

	for(int i=0;i<2;i++) bombflag[i] = 0;

	calx = caly = 0;

	PShotPushCnt = 0;
	PSwordPushCut_Z = PSwordPushCut_X = 0;
	BombtypePushCut = 0;
	BombPushCut = 0;
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

	if (keyboard_Get(KEY_INPUT_LSHIFT) > 0 || keyboard_Get(KEY_INPUT_RSHIFT) > 0) {
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
	if (enemy[46].flag == 1 || enemy[47].flag == 1 ||
		enemy[48].flag == 1 || enemy[49].flag == 1 ||
		enemy[50].flag == 1 || enemy[51].flag == 1 || enemy[52].flag == 1){
		if (player.hp <= 0) {
			player.hp = 0;
			player.flag = 0;
			playershot->flag = 0;
		}
	}
	if (enemy[46].flag == 0 && enemy[47].flag == 0 &&
		enemy[48].flag == 0 && enemy[49].flag == 0 &&
		enemy[50].flag == 0 && enemy[51].flag == 0 && enemy[52].flag == 0) {
		player.flag = 1;
		playershot->flag = 0;
	}

	//ボムの機能選択
	if (keyboard_Get(KEY_INPUT_V) > 0) {
		BombtypePushCut++;
		if (BombtypePushCut <= 1) {
			if (player.type_bomb == 3) player.type_bomb = 1;
			else player.type_bomb++;
		}
	}
	else if(BombtypePushCut != 0) BombtypePushCut = 0;

	//ボム
	if (keyboard_Get(KEY_INPUT_C) > 0 && player.mp > 0) {
		BombPushCut++;
		if (BombPushCut <= 1 && player.flag == 1) {

			if (player.type_bomb == 1&&player.mp-2>=0) {
				bombcnt[0] = t;
				createPlayerSword(player.x, player.y, 3);
			}
			else if (player.type_bomb == 2&& player.mp - 5 >= 0 &&bombflag[0]==0) {
				player.mp -= 5;
				bombflag[0] = 1;
				bombmagnification = 3;
			}
			else if (player.type_bomb == 3&& player.mp - 20 >= 0 &&bombflag[1]==0) {
				p_invi[0] = t;
				p_invi[1] = 1;
				bombcnt[1] = t;
				player.mp -= 20;
				bombflag[1] = 1;
				bombflag[2] = player.x;
				bombflag[3] = player.y;
			}
		}
		//mp_gの更新
		mp_g = 575 + player.mp * 6.67;
	}
	else if (BombPushCut != 0) BombPushCut = 0;
	
	//bomb2_gの更新
	if(bombflag[0]==1||bombflag[0]==2) bomb2_g=640+countflame*0.15;


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