#ifndef PLAYERSWORD_H
#define PLAYERSWORD_H

//create to Playersword
void createPlayerSword(float px, float py,int pattern);

void playersword_Initialize();

//動きを計算する
void playersword_Update(float px, float py);

//描画する
void playersword_Draw();

//終了処理をする
void playersword_Finalize();
#endif 