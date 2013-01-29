//�͂��߂̂�����
//include�錾
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�v���O�����I������
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

//�v���C���[�̃^�[������ق��@ 0�͉����Ȃ��A1�́��A2�́~�@��������ɂ����p
#define null 0
#define circle 1
#define cross 2 

//�v���g�^�C�v�錾
void Graph_func (void) ;
int Player_Set_func (void) ;
void First_func (void) ;
int Set_Check_func (int gyou , int retsu);
void Turn_Str_func (void) ;
int Win_Check_func (void) ;
int End_Check_func (int Win_flag) ;


//�O���[�o���ϐ��錾
int first_flag = 1 ;
int field[4][5] ;
int turn ;
char turn_str[8] ;
int gyou , retsu ;
//�����܂� 


//main�֐�      
int main (void){
	int set_error_flag;
	int Win_flag ;
	int End_flag ;
	
	//����N���̂Ƃ�
	if (first_flag == 1)    {
		First_func();
	}
	
	//���݂̐}��\��
	Graph_func();
	
	//�v���C���[�ɓ��͂�����֐��Ɉړ�
	set_error_flag = Player_Set_func();
	if (set_error_flag == 1)    {
		main();
	}        
	
	//�ǂ��炪�����������A�܂��͂ǂ�����������Ă��Ȃ�����WinCheck�Ŕ���(Win_flag=[circle/cross/null])
	Win_flag = Win_Check_func();
	
	//Win_flag�̕ԋp�l��Ending�ɗ^���ďI�������邩�ǂ����𔻒�,�����I���Ȃ�G���f�B���O(End_flag=[1/0])
	End_flag = End_Check_func(Win_flag) ;
	//�ǂ�����������Ȃ�������(End_flag==0�Ȃ�)�^�[���ύX���ă��[�v
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

//����N���̂Ƃ��̐���
void First_func (void){
	for (gyou = 1 ; gyou < 4 ; gyou++)       {
		for (retsu = 1 ; retsu < 4 ; retsu++)            {
			field[gyou][retsu] = 0;
		}
	}
	turn = circle ;
	first_flag = 0;
}

//���݂̐}�̐���
void Graph_func (void){
	printf("|�_|�P|�Q|�R|\n");
	printf("|--|--+--+--+\n");
	for (gyou = 1 ; gyou < 4 ; gyou++)       {
		switch (gyou)           {
		case 1:             printf("|�P|");
			break;
		case 2:             printf("|�Q|");
			break;
		case 3:             printf("|�R|");
			break;
		}
		for (retsu = 1 ; retsu < 4 ; retsu++)            {
			switch(field[gyou][retsu])              {
			case 1:                 printf("��");
				break;
			case cross:                 printf("�~");
				break;
			case null:                  printf("�@");
				break;
			}
			printf("|");
		}
		printf("\n");
		printf("|--|--+--+--+\n");
	}
}

//�v���C���[�ɓ��͂�����֐�
int Player_Set_func (void){
	int Check_flag ;
	Turn_Str_func();
	printf("���:���@���:�~\n");
	printf("���݁A[%s]�̃^�[���ł�\n\n", turn_str);
	printf("[�s,��]�̏��ɃR���}��؂�łQ���͂��Ă�������(��:[2,3]):");
	scanf("%d,%d", &gyou, &retsu);
	
	//��ʃN���A 
	system("cls");
	
	//���͂��ꂽ�l��Set_Check_func�ɔ�΂�
	Check_flag = Set_Check_func(gyou , retsu);
	if (Check_flag == 1)    {
		return 1;
	}
	return 0;
}

//���͒l�̔���
int Set_Check_func (int gyou , int retsu){
	if (gyou > 3 || retsu > 3)    {
		printf("�G���[:�s���Ȓl�����͂���܂���\n") ;
		return 1;
	}
	else if (field[gyou][retsu] != null )   {
		printf("�G���[:���ɒu����Ă��܂�\n");
		return 1;
	}else    
		//�u����Ă��Ȃ�������u
	{
		field[gyou][retsu] = turn ;
		//gyou,retsu�������� 
		//  gyou = 0, retsu = 0;
	}
	return 0;
}

//�^�[���ɂ���ĕ\�������镶���̕ύX
void Turn_Str_func (void){
	switch(turn)    {
	case circle:        strcpy (turn_str , "���:��");
		break;
	case cross:     strcpy (turn_str , "���:�~");
		break;
	}
}

//��������,�ǂ��炪���������܂��͏��������Ă��Ȃ���
int Win_Check_func (void){
	int set_cnt = 0;
	//���R
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
	//�^�e     
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
	//�i�i�� 
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
	//�S�Ẵ}�X�������ꂽ��\���N���A������ 

	
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
	//�����܂�
	return null;
}
//�I������,������������ŏ������m�肵���̂Ȃ�΃G���f�B���O��\��������1��Ԃ�,�����łȂ����0��Ԃ�
int End_Check_func (int Win_flag){
	if (Win_flag == null)   {
		return 0;
	}else    {
		Graph_func();
		printf("[%s]�̏����ł�\n", turn_str);
		scanf("%d", &gyou);
		return 1;
	}
}




 
