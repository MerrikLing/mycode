#include"game.h"
//ע�⣺�С��д�0��ʼ��
//��ʼ������
void ini(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0;i < row;i++)
	{
		int j = 0;
		for (j = 0;j < col;j++)
		{
			board[i][j] = ' ';//�ַ���ֵ������""
		}

	}
}
//չʾ����
void display(char board[][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("\n");
	//��ӡ�����Ϻ���
	printf("   ");
	for (j = 0;j < col;j++)
	{
		printf("%2d ",j+1);//ʹ�ü��Ŷ������»���
		printf(" ");
	}
	printf("\n");
	//��ӡ�������������
	printf("  |");
	for (j = 0;j < col;j++)
	{
		printf("---");//ʹ�ü��Ŷ������»���
		printf("|");
	}
	printf("\n");
	//��ӡ���
	for (i = 0;i < row;i++)
	{
		printf("%2d", i + 1);
		printf("|");
		for (j = 0;j < col;j++)
		{
			printf(" %c ", board[i][j]);
			printf("|");
		}
		printf("%-2d", i + 1);
		printf("\n");

		printf("  |");
		for (j = 0;j < col;j++)
		{
			printf("---");//ʹ�ü��Ŷ������»���
			printf("|");
		}
		printf("\n");
	}
	//��ӡ�����º���
	printf("   ");
	for (j = 0;j < col;j++)
	{
		printf("%2d ", j + 1);//ʹ�ü��Ŷ������»���
		printf(" ");
	}
}
//1���������,Ҫ��ֹ�ظ�
void playermove1(char board[][COL], int x, int y)
{
	while (x > COL || y > ROW || x < 1 || y < 1)
	{//	��ðѻ�������գ���Ȼ���벻ͬ����ʱ�������ѭ��

		char c;
		while ((c = getchar()) != '\n')
		{
		}
		printf("����������������������\n");
		scanf("%d.%d", &x, &y);

	}
	while (board[y - 1][x - 1] != ' ')
	{
		char c;
		while ((c = getchar()) != '\n')
		{
		}
		printf("���������ظ�������������\n");
		scanf("%d.%d", &x, &y);
	}
	board[y - 1][x - 1] = '#';
}
//2���������,Ҫ��ֹ�ظ�
void playermove2(char board[][COL], int x, int y)
{
	while (x > COL || y > ROW || x < 1 || y < 1)
	{//	��ðѻ�������գ���Ȼ���벻ͬ����ʱ�������ѭ��
		char c;
		while ((c = getchar()) != '\n')
		{}
		printf("����������������������\n");
		scanf("%d.%d", &x, &y);
	}
	while (board[y - 1][x - 1] != ' ')
	{
		char c;
		while ((c = getchar()) != '\n')
		{
		}
		printf("���������ظ�������������\n");
		scanf("%d.%d", &x, &y);
	}
	board[y - 1][x - 1] = '*';
}

//�ж�:һ��ʤ��ƽ(t)������(c)
char judge(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	int link = 1;
	//��
	for (i = 0;i < row;i++)
	{
		 link = 1;
		for (j = 0;j+4 < col ;j++)
		{
			if (board[i][j] == board[i][j + 1]&& board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4] && board[i][j] != ' ')
				return board[i][j];
		}
	}
	//��
	for (i = 0;i < col;i++)
	{
		link = 1;
		for (j = 0;j+4 < row;j++)
		{
			if (board[j][i] == board[j + 1][i]&& board[j][i] == board[j + 2][i] && board[j][i] == board[j + 3][i] && board[j][i] == board[j + 4][i] && board[j][i] != ' ')
				return board[j][i];
		}
	}
	//б��������
	for (i = 0;i + 4 < row;i++)
	{
		for (j = 0;j+4 < col ;j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3] && board[i][j] == board[i + 4][j + 4] && board[i][j] != ' ')
				return board[i][j];
		}
	}
	for (i = 0;i + 4 < row;i++)
	{
		for (j = col-1;j - 4 >=0;j--)
		{
			if(board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3] && board[i][j] == board[i + 4][j - 4] && board[i][j] != ' ')
				return board[i][j];
		}
	}

	//����
	for (i = 0;i < row;i++)
	{
		int j = 0;
		for (j = 0;j < col;j++)
		{
			if (board[i][j] == ' ')
				return 'c';
		}
	}
	//ƽ��
	return 't';
}

