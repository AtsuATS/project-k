#ifndef ENEMY_SHOT_H
#define ENEMY_SHOT_H

//create to EnemyShot
void createEnemyShot(float , float , int, int, int, int, double);

void enemyshot_Initialize();

//動きを計算する
void enemyshot_Update();

//描画する
void enemyshot_Draw();

//終了処理をする
void enemyshot_Finalize();


#endif 

