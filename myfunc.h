#ifndef HEAD_H_
#define HEAD_H_
#define CARD_MAX 52 //山札上限
#define SAFE 0      //手札21以下
#define U_BUST 1    //手札21超え
#define C_BUST -1   //手札21超え
#define USER 1      //ユーザーモード
#define COM 2       //コンピュータモード

//構造体宣言
typedef struct{
	int no;
	char suit;
}card_str;


void game_init();               //ゲーム初期化
void card_input();              //山札定義
void card_shuffle();            //山札を切る
void card_draw(int n,int mode); //カードを配る
void game_cmd();                //ゲーム内行動選択
void hand_output(int mode);     //手札表示
int com_main();                 //敵の行動選択
int hand_check(int mode);       //21以下か確認
void game_judge();              //勝ち負け判定
void result_write(int result);  //ファイルに書き込む
#endif