#ifndef DEF_KEYBOARD_H//二重include防止
#define DEF_KEYBOARD_H

//キーの入力状況を更新する
void keyboard_Update();

//引数のキーコードのキーの入力状態を返す
int keyboard_Get(int keycode);

#endif