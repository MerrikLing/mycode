#include"mine clearance.h"
//ע���������¶����һ��
//��ʼ��չʾ������
void ini(char board_show[][COL + 2])
{
	int i = 1;
	int j = 1;
	for (i = 1;i <= ROW;i++)
	{
		for (j = 1;j <= COL;j++)
			board_show[i][j] = '*';
	}
}
//���������
void set_mine(int board[][COL + 2], int x, int y)
{
	srand((unsigned)time(NULL));
	//�����������׵�����������꣩
	int i = 0;
	for (i = 1;i <= mine;i++)
	{
		int x = rand() % ROW + 1;
		int y = rand() % COL + 1;
		//��ֹ�ظ����ף���ѭ����
		while (board[x][y] == 1)
		{
			x = rand() % ROW + 1;
			y = rand() % COL + 1;
		}
		board[x][y] = 1;
	}
}
//չʾ
void display(char board_show[][COL + 2])
{
	int i = 0;
	int j = 0;
	//��ӡ�Ϻ���
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ",i);
	printf("\n");
	//��ӡ�Ϻ���
	printf("  |");
	for (i = 1;i <= COL;i++)
		printf("---|");
	printf("\n");
	//��ӡ���
	for (i = 1;i <= ROW;i++)
	{
		printf("%2d|", i);
		for (j = 1;j <= COL;j++)
		{
			if (board_show[i][j] == '!')
			{
				printf("\033[40;31m * \033[0m");//��ӡ��ɫ*
				printf("|");
			}
			else if (board_show[i][j] == 0)
			{
				printf("   ");//��ӡ�հ�
				printf("|");
			}
			else if (board_show[i][j] != '*')
			{
				printf("\033[40;32m %d \033[0m", board_show[i][j]);//��ӡ��ɫ�����֣�����Ŀ
				printf("|");
			}
			else
				printf(" %c |", board_show[i][j]);
		}
		printf("%d\n  |",i);
		for (j = 1;j <= COL;j++)
		{
			printf("---|");
		}
		printf("\n");
	}

	//�º���
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ", i);
	printf("\n");
}

//��Ҳ���
int operation(char board_show[][COL + 2], int x, int y, int board[][COL + 2])
{
	//�ж������Ƿ���硢�ظ�
	while (x<1 || x>COL || y<1 || y>ROW|| board[y][x] == 2)
	{
		int c = 0;
		while((c=getchar())!='\n')
		{ }
		printf("��������������������꣨�Ⱥ���ݣ��õ��.��������  ");
		scanf("%d.%d", &x, &y);
	}
	//�Ƿ�ʧ�ܡ�������1
	if (board[y][x] == 1)
		return 1;
	//��������
	board[y][x] = 2;
	//�Ƿ�ʤ����������0
	int i = 0;
	int j = 0;
	int number = 0;
	for (i = 1;i <= ROW;i++)
	{
		for (j = 1;j <= COL;j++)
		{
			if (board[i][j] == 0)
				goto con;
		}
	}
	return 0;
	//��Ϸ����,չʾ��Χ������,����2
con:
	for (i = y - 1;i <= y + 1;i++)
	{
		for (j = x - 1;j <= x + 1;j++)
		{
			if (board[i][j] == 1)
				number++;
		}
	}
	board_show[y][x] = number;
	return 2;//�˴�Ҳ�����⣬�����ļ��й�
}

//��Χû����ʱ������Χ���
// (���Բ���д��operation���棡�������������һ����ɢ��ȥ��������ɡ��������)
void clear_sur(char board_show[][COL + 2], int x, int y, int board[][COL + 2])
{
	//�ж��Ƿ���������
	int i = 0;
	int j = 0;
	int number = 0;
	for (i = y - 1;i <= y + 1;i++)
	{
		for (j = x - 1;j <= x + 1;j++)
		{
			if (board[i][j] == 1)
				number++;
		}
	}
	if(0 == number)
	{//ִ��
		for (i = y - 1;i <= y + 1;i++)
		{
			for (j = x - 1;j <= x + 1;j++)
			{
				if (j<1 || j>COL || i<1 || i>ROW || board[i][j] == 2)
				{
					continue;
				}
				operation(board_show, j, i, board);
				clear_sur(board_show, j, i, board);
			}
		}
	}
}
//��ǻ�ȡ�������
void flag(char board_show[][COL + 2], int x, int y, int board[][COL + 2], int* m)
{
	////�ж������Ƿ���������Ƿ�Ϸ���ע�����α�����Ϊԭ��
	//int i = 0;
	//int j = 0;
	//scanf("%d.%d", &x, &y);//�������Ϊʲôû��ִ�У�
	while (x<1 || x>COL || y<1 || y>ROW || board[y][x] == 2)
	{
		int c = 0;
		while ((c = getchar()) != '\n')
		{
		}
		printf("����������ٴ��������꣨�Ⱥ���ݣ��õ��.��������  ");
		scanf("%d.%d", &x, &y);
	}
	//ע������ִ��Ҫȡ������չʾ�����׵�����
	if (board_show[y][x] == '!')
	{
		board_show[y][x] = '*';
		(*m)++;
	}
	else
	{
		board_show[y][x] = '!';
		(*m)--;
	}
}

//չʾ���Ų�
void mine_show(int board[][COL + 2])
{
	int i = 0;
	int j = 0;
	//��ӡ�Ϻ���
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ", i);
	printf("\n");
	//��ӡ�Ϻ���
	printf("  |");
	for (i = 1;i <= COL;i++)
		printf("---|");
	printf("\n");
	//��ӡ���
	for (i = 1;i <= ROW;i++)
	{
		printf("%2d|", i);
		for (j = 1;j <= COL;j++)
		{
			char c = ' ';
			if (board[i][j] == 1)
				c = '#';
			printf(" %c |", c);  //չʾ��
		}
		printf("%d\n  |", i);
		for (j = 1;j <= COL;j++)
		{
			printf("---|");
		}
		printf("\n");
	}

	//�º���
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ", i);
	printf("\n");
}
