#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myfunc.h"

//グローバル変数宣言
int card_state;     //山札の先頭
int hand_count;     //手札の枚数
int com_count;      //敵手札の枚数
int user_sum;       //自分の手札の合計
int com_sum;        //敵の手札の合計

//ゲームの初期化
void game_init(){
	//グローバル変数初期化
	card_state=CARD_MAX-1;
	hand_count=0;
	com_count=0;
	user_sum=0;
	com_sum=0;

	//山札定義 & シャッフル
	card_input();
}
