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
	//��ӡ�������������
	printf("|");
	for (j = 0;j < col;j++)
	{
		printf("---");//ʹ�ü��Ŷ������»���
		printf("|");
	}
	printf("\n");
	//��ӡ���
	for (i = 0;i < row;i++)
	{
		printf("|");
		for (j = 0;j < col;j++)
		{
			printf(" %c ", board[i][j]);
			printf("|");
		}
		printf("\n");

		printf("|");
		for (j = 0;j < col;j++)
		{
			printf("---");//ʹ�ü��Ŷ������»���
			printf("|");
		}
		printf("\n");
	}
}
//�������,Ҫ��ֹ�ظ�
void playermove(char board[][COL], int x, int y)
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
	board[y - 1][x - 1] = '*';
}
//��������
void program(char board[ROW][COL], int row, int col)
{
	srand((unsigned)time(NULL));
	//���ԣ��������������ģ������������Ϊ�����������������������
	int i = 0;
	int j = 0;
	//����
	//�ᡪ��������ѭ�����
	for (i = 0;i < row;i++)
	{
		for (j = 0;j < col;j++)
		{
			if (board[i][j] == board[i][(j + 1) % col] && board[i][(j + 2) % col] == ' ' && board[i][j] == '#')
			{
				board[i][(j + 2) % col] = '#';
				return;
			}
		}
	}
	//��
	for (i = 0;i < col;i++)
	{
		for (j = 0;j < row;j++)
		{
			if (board[j][i] == board[(j + 1) % row][i] && board[(j + 2) % row][i] == ' ' && board[(j + 1) % row][i] == '#')
			{
				board[(j + 2) % row][i] = '#';
				return;
			}
		}
	}


	//�Խ��ߡ�2��
	for (i = 0, j = 0;i < row && j < col;i++, j++)
	{
		if (board[i][j] == board[(i + 1) % row][(j + 1) % col] && board[(i + 2) % row][(j + 2) % col] == ' ' && board[i][j] == '#')
		{
			board[(i + 2) % row][(j + 2) % col] = '#';
			return;
		}
	}
	for (i = 0, j = 2;i < row && j >= 0;i++, j--)
	{
		if (board[i][j] == board[(i + 1) % row][(j + 5) % col] && board[(i + 2) % row][(j + 4) % col] == ' ' && board[i][j] == '#')
		{
			board[(i + 2) % row][(j + 4) % col] = '#';
			return;
		}
	}
	//����
//�ᡪ��������ѭ�����
	for (i = 0;i < row;i++)
	{
		for (j = 0;j < col;j++)
		{
			if (board[i][j] == board[i][(j + 1) % col] && board[i][(j + 2) % col] == ' ' && board[i][j] == '*')
			{
				board[i][(j + 2) % col] = '#';
				return;
			}
		}
	}
	//��
	for (i = 0;i < col;i++)
	{
		for (j = 0;j < row;j++)
		{
			if (board[j][i] == board[(j + 1) % row][i] && board[(j + 2) % row][i] == ' ' && board[(j + 1) % row][i] == '*')
			{
				board[(j + 2) % row][i] = '#';
				return;
			}
		}
	}


	//�Խ��ߡ�2��
	for (i = 0, j = 0;i < row && j < col;i++, j++)
	{
		if (board[i][j] == board[(i + 1) % row][(j + 1) % col] && board[(i + 2) % row][(j + 2) % col] == ' ' && board[i][j] == '*')
		{
			board[(i + 2) % row][(j + 2) % col] = '#';
			return;
		}
	}
	for (i = 0, j = 2;i < row && j >= 0;i++, j--)
	{
		if (board[i][j] == board[(i + 1) % row][(j + 5) % col] && board[(i + 2) % row][(j + 4) % col] == ' ' && board[i][j] == '*')
		{
			board[(i + 2) % row][(j + 4) % col] = '#';
			return;
		}
	}
	//�����
	while (1)
	{
		int i = rand() % row;
		int j = rand() % col;
		if (board[i][j] == ' ')
		{
			board[i][j] = '#';
			break;
		}
	}
}
//�ж�:һ��ʤ��ƽ(t)������(c)
char judge(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	//��
	for (i = 0;i < row;i++)
	{
		int link = 1;
		for (j = 0;j < col - 1;j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j] != ' ')
				link++;
		}
		if (link == checker)
			return board[i][j];
	}
	//��
	for (i = 0;i < col;i++)
	{
		int link = 1;
		for (j = 0;j < row - 1;j++)
		{
			if (board[j][i] == board[j + 1][i] && board[j][i] != ' ')
				link++;
		}
		if (link == checker)
			return board[j][i];
	}
	//б�������壩
	if (board[0][0] == board[1][1] && board[2][2] == board[1][1] && board[0][0] != ' ')
		return board[0][0];
	if (board[2][0] == board[1][1] && board[0][2] == board[1][1] && board[1][1] != ' ')
		return board[1][1];
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

