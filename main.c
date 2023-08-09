#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"myfunc.h"

//定数定義
#define CARD_MAX 52 //山札上限
#define SAFE 0      //手札21以下
#define U_BUST 1    //手札21超え
#define C_BUST -1   //手札21超え
#define USER 1      //ユーザーモード
#define COM 2       //コンピュータモード

//構造体宣言
//typedef struct{
//	int no;
//	char suit;
//}card_str;

//card_str card[CARD_MAX]; //山札配列
//card_str hand[CARD_MAX]; //手札配列
//card_str com[CARD_MAX]; //敵手札配列

//グローバル変数宣言
int card_state;     //山札の先頭
int hand_count;     //手札の枚数
int com_count;      //敵手札の枚数
int user_sum;       //自分の手札の合計
int com_sum;        //敵の手札の合計


//プロトタイプ宣言
//void game_init();               //ゲーム初期化
//void card_input();              //山札定義
//void card_shuffle();            //山札を切る
//void card_draw(int n,int mode); //カードを配る
//void game_cmd();                //ゲーム内行動選択
//void hand_output(int mode);     //手札表示
//int com_main();                 //敵の行動選択
//int hand_check(int mode);       //21以下か確認
//void game_judge();              //勝ち負け判定
//void result_write(int result);  //ファイルに書き込む



//山札定義
void card_input(){
	int i;
	int tmp;
	for(i=0;i<CARD_MAX;i++){

		//数字を代入
		card[i].no=i%13+1;

		//マークを代入
		tmp=i/13;
		if(tmp == 0) card[i].suit='s';
		if(tmp == 1) card[i].suit='q';
		if(tmp == 2) card[i].suit='h';
		if(tmp == 3) card[i].suit='d';
	}
	//定義した山札をシャッフル
	card_shuffle();
}

//山札シャッフル
void card_shuffle(){
	//一時変数
	int i;
	int r;
	int tmp_n;
	char tmp_s;

	//乱数の種に時間を設定
	srand((unsigned int)time(NULL));

	for(i=0;i<CARD_MAX;i++){
		r=rand()%CARD_MAX;		//乱数取得

		//数値入れ替え
		tmp_n=card[i].no;
		card[i].no=card[r].no;
		card[r].no=tmp_n;

		//マーク入れ替え
		tmp_s=card[i].suit;
		card[i].suit=card[r].suit;
		card[r].suit=tmp_s;
	}
}

//行動選択
void game_cmd(){
	int flag; 	//21以下チェックフラグ
	char cmd; 	//コマンド用変数

	//初期手札表示
	card_draw(2,USER);
	hand_output(USER);

	com_main(0);		//乱数取得

	while(1){

		//行動選択
		printf("行動を選択(h:ヒット/s:スタンド):");
		scanf("%c",&cmd);
		switch( cmd ){
			case 'h':
			card_draw(1,USER);
			hand_output(USER);
			flag=hand_check(USER);
			if(flag == U_BUST){
				hand_check(USER);
				hand_check(COM);
				printf("あなたの負けです。\n");
				result_write(0);
			}
			break;

			case 's':
			flag=com_main(1);
			if(flag == C_BUST){
				hand_check(USER);
				hand_check(COM);
				printf("あなたの勝ちです。\n");
				result_write(1);
			}
			else  game_judge();
			flag=1;
			break;

			default:
			printf("エラーが発生しました。もう一度入力してください。\n");
			break;
		}
		if(flag == U_BUST || flag == C_BUST ) break;
	}
}


//敵の行動選択
int com_main(int count){
	int i,sum;

	if(count == 0){
		card_draw(2,COM);
		hand_output(COM);
	}

	if(count == 1){
		do{
			card_draw(1,COM);
			sum=hand_check(COM);
			hand_output(COM);
		}while(sum < 17);
		if(sum > 21) return C_BUST;
		else		 return SAFE;
	}
	return 0;
}

//カードをドロー
void card_draw(int n,int mode){
	int i;
	//ユーザーが引く
	if(mode == USER){
		for(i=hand_count;i<hand_count+n;i++){
			hand[i].no=card[card_state].no;
			hand[i].suit=card[card_state].suit;
			card_state--;
		}
		hand_count+=n;		//カードを引いた枚数を加算
	}
	//コンピュータが引く
	if(mode == COM){
		for(i=com_count;i<com_count+n;i++){
			com[i].no=card[card_state].no;
			com[i].suit=card[card_state].suit;
			card_state--;
		}
		com_count+=n;		//カードを引いた枚数を加算
	}
}

//手札を表示
void hand_output(int mode){
	int i;
	//ユーザーの手札を表示
	if(mode == USER){
		printf("USER: ");
		for(i=0;i<hand_count;i++){
			printf("%c:%d ",hand[i].suit,hand[i].no);
		}
	}
	//敵の手札を表示
	if(mode == COM){
		printf("COM: ");
		for(i=0;i<com_count;i++){
			printf("%c:%d ",com[i].suit,com[i].no);
		}
	}
	printf("\n");
}

//手札の数字が21以下かチェック
int hand_check(int mode){
	int i,sum=0,tmp;
	//ユーザーの手札チェック
	if(mode == USER){
		for(i=0;i<hand_count;i++){
			//10以上の数字は全て10とする
			if(hand[i].no > 10){
				sum+=10;
			}

			//Aは 1 か 11 のどちらかより選択
			else if(hand[i].no == 1){
				printf("Aを1、11どちらでカウントしますか？(1/11):");
				scanf("%d",&tmp);
				if(tmp == 1 ) sum+=1;
				if(tmp == 11) sum+=11;
			}else{
				sum+=hand[i].no;
			}
		}
		user_sum=sum;
		if(sum > 21) return U_BUST;
	}

	//敵の手札チェック
	if(mode == COM){
		for(i=0;i<com_count;i++){
			//10以上の数字は全て10とする
			if(com[i].no > 10) sum+=10;
			else 				 sum+=com[i].no;
		}
		com_sum=sum;
		return sum;
	}
	return SAFE;
}
//勝ち負け判定
void game_judge(){
	if(user_sum > com_sum){
        printf("あなたの勝ちです。\n");
        result_write(1);
    }
	if(com_sum > user_sum) {
        printf("あなたの負けです。\n");
        result_write(0);
    }
	if(com_sum == user_sum){
		if(com_count > hand_count) {
            printf("あなたの勝ちです。\n");
        	result_write(1);
        }
		if(hand_count > com_count) {
            printf("あなたの負けです。\n");
	        result_write(0);
        }
	}
}

void result_write(int result){
    time_t timer;        // 時刻を取り出す
    struct tm *local;    // tm構造体

    // 年月日と時分秒保存用
    int year, month, day, hour, minute, second;

    timer = time(NULL);        //現在時刻を取得
    local = localtime(&timer);    // 地方時に変換

    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    day = local->tm_mday;
    hour = local->tm_hour;
    minute = local->tm_min;
    second = local->tm_sec;

	//ファイル書き込み
	FILE *fp;
	printf("結果をresult.txtに保存します。\n");
 	if((fp=fopen("result.txt","w"))==NULL){
 	  	printf("リザルトを保存できませんでした\n原因:ファイルをオープンできない\n");
 	}else{
	fp = fopen("result.txt", "w");
	if(result == 1){
	    fprintf(fp,"win (user_sum:%d,com_sum:%d)  %d/%d/%d %d:%d:%d\n",user_sum,com_sum,year, month, day, hour, minute, second);
	}
	else if(result == 0){
	    fprintf(fp,"lose (user_sum:%d,com_sum:%d)  %d/%d/%d %d:%d:%d\n",user_sum,com_sum,year, month, day, hour, minute, second);
	}else{
		printf("エラーが発生しました。\n");
	}
	printf("結果をresult.txtに保存しました。\n");
 	}
  fclose(fp);
}

void main(){
	char cmd; //コマンド用変数
	printf("ゲームを開始しますか?(y:yes/n:no):"); scanf("%c",&cmd);
	switch(cmd){
		case 'y':
		game_init();
		game_cmd();
		break;

		case 'n':
		exit(0);
		break;

		default:
		printf("エラーが発生しました。終了します。\n");
		break;
	}
}
