#ifndef BASEENEMY_H
#define BASEENEMY_H

typedef struct _BaseEnemy {
	float x;
	float y;
	int hp;
	int type;
	int speed;
	int act[8];
	int cnt = 0;//無敵の間のカウント
	bool flag;
	float deg;
}Enemy_status;

typedef struct _BaseEnemy_shot {
	float x;
	float y;
	int hp;//攻撃力
	int speed;
	int cnt;
	int type;//追加
	int pattern;//追加
	int wait;//追加
	double ang;//追加
	bool flag;
}Enemy_shot;

#endif 


