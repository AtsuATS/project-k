#ifndef  PLAYERSHOT_H
#define PLAYERSHOT_H

//create to PlayerShot
void createPlayerShot(float px, float py);

void playershot_Initialize();

//動きを計算する
void playershot_Update();

//描画する
void playershot_Draw();

//終了処理をする
void playershot_Finalize();
#endif 