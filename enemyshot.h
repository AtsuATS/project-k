#ifndef ENEMYSHOT_H
#define ENEMYSHOT_H

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

