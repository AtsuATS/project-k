#ifndef BASEUNIT_H
#define BASEUNIT_H

typedef struct _BaseUnit {
	float x;
	float y;
	int hp;
	int mp;
	int type_bomb; //The type of the bomb
	int type;
	float speed;
	bool flag;
}BaseUnit;

typedef struct _BaseShot {
	float x;
	float y;
	int power;//追加
	int type;
	int speed;
	bool flag;
}BaseShot;

typedef struct _BaseSword {
	float x;
	float wx;
	float y;
	float wy;
	float sdig;
	float wsdig;
	float gdig;
	float wgdig;
	int flame;
	int wflame;
	char l_or_r;
	int pattern;
	bool flag;
}BaseSword;


void stage_Initialize();

//動きを計算する
void stage_Update();

//描画する
void stage_Draw();

//終了処理をする
void stage_Finalize();


#endif 