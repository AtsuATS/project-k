#include "DxLib.h"

int key[256]; // キーが押されているフレーム数を格納する

//キーの入力状況更新
void keyboard_Update(){
	char tmpkey[256];//現在のキー入力状況を格納する
	GetHitKeyStateAll(tmpkey);//すべてのキーの入力状況を得る
	for (int i = 0; i < 256; i++){
		if (tmpkey[i] != 0) {//i番目のキーが押されているとき
			key[i]++;//加算
		}
		else//キーが押されてない時
		{
			key[i] = 0;//0にする
		}
	}
}

//KeyBoardのキーの入力状況を習得する
int keyboard_Get(int keyCode){
	return key[keyCode];//KeyCodeの入力状態を返す
}