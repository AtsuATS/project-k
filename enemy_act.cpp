#include <math.h>
#include "BaseEnemy.h"
#include "calculation.h"
#define R 100

/*直線移動
*始点(x1,y1)
*終点(x2,y2)
*/
void enemy_act0(Enemy_status *enemy, float x1,float y1,float x2,float y2) {

	float A_a, sine, cosine;
	if (enemy->function == 0) {
		enemy->x = x1;
		enemy->y = y1;
		enemy->function = 1;
	}
	A_a = Argument_angle(x1, y1, x2, y2);
	if (x2 - x1 == 0) cosine = 0;
	else cosine = cos(A_a);
	if (y2 - y1 == 0)sine = 0;
	else sine = sin(A_a);
	enemy->x += enemy->speed*cosine;
	enemy->y += enemy->speed*sine;

	return;
}

void enemy_act1(void) {}

void enemy_act2(void) {}

//左から右への移動
void enemy_act3(Enemy_status *enemy) {
	enemy->x += enemy->speed;
	return;
}

//右から左への移動
void enemy_act4(Enemy_status *enemy) {
	enemy->x -= enemy->speed;
	return ;
}

//左から中央で下方向に一回転。のちに右へ消える
void enemy_act5(Enemy_status *enemy) {
	static bool c_flag = 0;
	static float deg = -90;
	//circumference(Enemy_status enemy_circle,float r,float deg,float O_x,float O_y):円運動
	if ((enemy->x > 275&&deg<=270)||c_flag==1) {
		c_flag = 1;
		*enemy = circumference(*enemy, R, deg,275,300);
		deg++;
		if (deg >= 270) {
			c_flag = 0;
		}
	}
	else
	enemy->x +=2;
	return;
}

//右から中央で下方向に一回転。のちに左へ消える
void enemy_act6(Enemy_status *enemy){
	static bool c_flag = 0;
	static float deg = 270;
	//circumference(Enemy_status enemy_circle,float r,float deg,float O_x,float O_y):円運動
	//↑この関数をenemy,cppに移動する予定
	if ((enemy->x < 275 && deg >= -90) || c_flag == 1) {
		c_flag = 1;
		*enemy = circumference(*enemy, R, deg, 275, 300);
		deg--;
		if (deg <= -90) {
			c_flag = 0;
		}
	}
	else
	enemy->x -= 2;
	return ;
}

/*始点から中継点を経由し終点への直線移動
*始点(x1,y1)から画面外から出現
*中継点1個(x2,y2)で方向転換
*終点(x3,y3)で画面外
*/
void enemy_act7(Enemy_status *enemy, float x1, float y1, float x2, float y2, float x3, float y3) {
	/*flag:
	*[0]=中継点を通過したかどうか(0=未通過1=通過)
	*[1]=コマ数の計算をしたかどうか(0=未計算1=計算済み)
	*/
	static bool flag[2] = { 0 };
	static float A_a,frame,sine,cosine,distance_x,distance_y;
	static int frame_times = 0;
	//始点から中継点までの一コマ当たりの移動距離
	if (flag[0] == 0) {
		if (flag[1] == 0) {
			flag[1] = 1;
			enemy->x = x1;
			enemy->y = y1;	//位置の初期化
			frame = number_of_frames(*enemy, x1, y1, x2, y2);	//中継点までのフレーム数の計算
			A_a = Argument_angle(x1, y1, x2, y2);
			if (x2 - x1 == 0) cosine = 0;
			else cosine = cos(A_a);
			if (y2 - y1 == 0)sine = 0;
			else sine = sin(A_a);
			distance_x = enemy->speed*cosine;
			distance_y = enemy->speed*sine;
			enemy->x -= distance_x;
			enemy->y -= distance_y;
		}
		enemy->x += distance_x;
		enemy->y += distance_y;

		if(frame_times>frame){
			flag[0] = 1;
			flag[1] = 0;
		}
	}
	//中継点から終点までの一コマ当たりの移動距離
	else {
		if (flag[1] == 0) {
			flag[1] = 1;
			frame = number_of_frames(*enemy, x2, y2, x3, y3);
			A_a = Argument_angle(x2, y2, x3, y3);
			if (x3 - x2 == 0) cosine = 0;
			else cosine = cos(A_a);
			if (y3 - y2 == 0)sine = 0;
			else sine = sin(A_a);
			distance_x = enemy->speed*cosine;
			distance_y = enemy->speed*sine;
		}
		enemy->x += distance_x;
		enemy->y += distance_y;

		if (frame_times>frame) {
			flag[0] = 1;
			flag[1] = 0;
			frame_times = -1;
		}

	}
	frame_times++;
	return;
}

/*始点から停止点までの直線移動
*※停止後の処理は未完成
*始点(x1,y1)
*停止点(x2,y2)
*/
void enemy_act8(Enemy_status *enemy,float x1,float y1,float x2,float y2) {
	/*flag
	*[0]=停止点に到達したかどうか
	*[1]=最初の処理をしたかどうか
	*/
	static bool flag[2] = { 0 };
	static float frame;
	static float A_a, sine, cosine,distance_x,distance_y;
	static int frame_times=0;
	if (flag[0] == 0) {
		if (flag[1] == 0) {
			flag[1] = 1;
			enemy->x = x1;
			enemy->y = y1;
			frame = number_of_frames(*enemy, x1, y1, x2, y2);
			A_a = Argument_angle(x1, y1, x2, y2);
			if (x2 - x1 == 0) cosine = 0;
			else cosine = cos(A_a);
			if (y2 - y1 == 0)sine = 0;
			else sine = sin(A_a);
			distance_x = enemy->speed*cosine;
			distance_y = enemy->speed*sine;
			enemy->x -= distance_x;
			enemy->y -= distance_y;
		}
		else {
			enemy->x += distance_x;
			enemy->y += distance_y;
		}
		frame_times++;
		if (frame_times > frame) {
			flag[0] = 1;
			frame_times = 0;
		}
	}
	return;
}