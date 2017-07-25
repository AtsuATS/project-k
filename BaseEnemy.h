#ifndef BASEENEMY_H
#define BASEENEMY_H

typedef struct _BaseEnemy {
	float x;
	float y;
	int hp;
	int type;
	int speed;
	int cnt;
	bool flag;
	bool act[6];
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


