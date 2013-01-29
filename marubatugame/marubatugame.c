//はじめのじゅんび
//include宣言
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//プログラム終了判定
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

//プレイヤーのターン制御ほか　 0は何もなし、1は○、2は×　勝利判定にも利用
#define null 0
#define circle 1
#define cross 2 

//プロトタイプ宣言
void Graph_func (void) ;
int Player_Set_func (void) ;
void First_func (void) ;
int Set_Check_func (int gyou , int retsu);
void Turn_Str_func (void) ;
int Win_Check_func (void) ;
int End_Check_func (int Win_flag) ;


//グローバル変数宣言
int first_flag = 1 ;
int field[4][5] ;
int turn ;
char turn_str[8] ;
int gyou , retsu ;
//ここまで 


//main関数      
int main (void){
	int set_error_flag;
	int Win_flag ;
	int End_flag ;
	
	//初回起動のとき
	if (first_flag == 1)    {
		First_func();
	}
	
	//現在の図を表示
	Graph_func();
	
	//プレイヤーに入力させる関数に移動
	set_error_flag = Player_Set_func();
	if (set_error_flag == 1)    {
		main();
	}        
	
	//どちらが勝利したか、またはどちらも勝利していないかをWinCheckで判定(Win_flag=[circle/cross/null])
	Win_flag = Win_Check_func();
	
	//Win_flagの返却値をEndingに与えて終了させるかどうかを判定,もし終了ならエンディング(End_flag=[1/0])
	End_flag = End_Check_func(Win_flag) ;
	//どちらも勝利しなかったら(End_flag==0なら)ターン変更してループ
	if( End_flag == 0 ) {
		if (turn == circle)     {
			turn = cross;
		}       else        {
			turn = circle;
		}
		main();
	}
	return EXIT_SUCCESS;
}

//初回起動のときの制御
void First_func (void){
	for (gyou = 1 ; gyou < 4 ; gyou++)       {
		for (retsu = 1 ; retsu < 4 ; retsu++)            {
			field[gyou][retsu] = 0;
		}
	}
	turn = circle ;
	first_flag = 0;
}

//現在の図の制御
void Graph_func (void){
	printf("|＼|１|２|３|\n");
	printf("|--|--+--+--+\n");
	for (gyou = 1 ; gyou < 4 ; gyou++)       {
		switch (gyou)           {
		case 1:             printf("|１|");
			break;
		case 2:             printf("|２|");
			break;
		case 3:             printf("|３|");
			break;
		}
		for (retsu = 1 ; retsu < 4 ; retsu++)            {
			switch(field[gyou][retsu])              {
			case 1:                 printf("○");
				break;
			case cross:                 printf("×");
				break;
			case null:                  printf("　");
				break;
			}
			printf("|");
		}
		printf("\n");
		printf("|--|--+--+--+\n");
	}
}

//プレイヤーに入力させる関数
int Player_Set_func (void){
	int Check_flag ;
	Turn_Str_func();
	printf("先手:○　後手:×\n");
	printf("現在、[%s]のターンです\n\n", turn_str);
	printf("[行,列]の順にコンマ区切りで２つ入力してください(例:[2,3]):");
	scanf("%d,%d", &gyou, &retsu);
	
	//画面クリア 
	system("cls");
	
	//入力された値をSet_Check_funcに飛ばす
	Check_flag = Set_Check_func(gyou , retsu);
	if (Check_flag == 1)    {
		return 1;
	}
	return 0;
}

//入力値の判定
int Set_Check_func (int gyou , int retsu){
	if (gyou > 3 || retsu > 3)    {
		printf("エラー:不正な値が入力されました\n") ;
		return 1;
	}
	else if (field[gyou][retsu] != null )   {
		printf("エラー:既に置かれています\n");
		return 1;
	}else    
		//置かれていなかったら置
	{
		field[gyou][retsu] = turn ;
		//gyou,retsuを初期化 
		//  gyou = 0, retsu = 0;
	}
	return 0;
}

//ターンによって表示させる文字の変更
void Turn_Str_func (void){
	switch(turn)    {
	case circle:        strcpy (turn_str , "先手:○");
		break;
	case cross:     strcpy (turn_str , "後手:×");
		break;
	}
}

//勝利判定,どちらが勝ったかまたは勝負がついていないか
int Win_Check_func (void){
	int set_cnt = 0;
	//ヨコ
	if(field[1][1] != 0 && field[1][2] != 0 && field[1][3]  != 0)   {
		if(field[1][1] == field[1][2] && field[1][2] == field[1][3] )       {
			return turn;
		}
	}
	if(field[2][1] != 0 && field[2][2] != 0 && field[2][3]  != 0)   {
		if(field[2][1] == field[2][2] && field[2][2] == field[2][3] )       {
			return turn;
		}
	}
	if(field[3][1] != 0 && field[3][2] != 0 && field[3][3]  != 0)   {
		if(field[3][1] == field[3][2] && field[3][2] == field[3][3] )       {
			return turn;
		}
	}
	//タテ     
	if(field[1][1] != 0 && field[2][1] != 0 && field[3][1]  != 0)   {
		if(field[1][1] == field[2][1] && field[2][1] == field[3][1] )       {
			return turn;
		}
	}
	if(field[1][2] != 0 && field[2][2] != 0 && field[3][2]  != 0)   {
		if(field[1][2] == field[2][2] && field[2][2] == field[3][2] )       {
			return turn;
		}
	}
	if(field[1][3] != 0 && field[2][3] != 0 && field[3][3]  != 0)   {
		if(field[1][3] == field[2][3] && field[2][3] == field[3][3] )       {
			return turn;
		}
	}
	//ナナメ 
	if(field[1][1] != 0 && field[2][2] != 0 && field[3][3]  != 0)   {
		if(field[1][1] == field[2][2] && field[2][2] == field[3][3] )       {
			return turn;
		}
	}
	if(field[1][1] != 0 && field[2][2] != 0 && field[3][1]  != 0)   {
		if(field[1][3] == field[2][2] && field[2][2] == field[3][1] )       {
			return turn;
		}
	}
	//全てのマスがおかれたら表をクリアさせる 

	
	for (gyou = 1 ; gyou < 4 ; gyou++)       {
		for (retsu = 1 ; retsu < 4 ; retsu++)            {
			if(field[gyou][retsu] != 0)             {
				set_cnt ++ ;
			}
		}
	}

	if (set_cnt == 9)   {
		for (gyou = 1 ; gyou < 4 ; gyou++)       {
			for (retsu = 1 ; retsu < 4 ; retsu++)            {
				field[gyou][retsu] = 0;
			}
		}
	}
	//ここまで
	return null;
}
//終了判定,もし勝利判定で勝利が確定したのならばエンディングを表示させて1を返し,そうでなければ0を返す
int End_Check_func (int Win_flag){
	if (Win_flag == null)   {
		return 0;
	}else    {
		Graph_func();
		printf("[%s]の勝利です\n", turn_str);
		scanf("%d", &gyou);
		return 1;
	}
}




 
