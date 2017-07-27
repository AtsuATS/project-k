#ifndef BASEENEMY_H
#define BASEENEMY_H

typedef struct _BaseEnemy {
	float x;
	float y;
	int hp;
	int type;
	int speed;
	int act[6];
	int cnt = 0;
	bool flag;
	float deg;
}Enemy_status;

typedef struct _BaseEnemy_shot {
	float x;
	float y;
	int hp;//�U����
	int speed;
	int cnt;
	int type;//�ǉ�
	int pattern;//�ǉ�
	int wait;//�ǉ�
	double ang;//�ǉ�
	bool flag;
}Enemy_shot;

#endif 


