#include"game.h"
//注意：行、列从0开始！
//初始化棋盘
void ini(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0;i < row;i++)
	{
		int j = 0;
		for (j = 0;j < col;j++)
		{
			board[i][j] = ' ';//字符赋值不能用""
		}

	}
}
//展示棋盘
void display(char board[][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("\n");
	//打印棋盘上横轴
	printf("   ");
	for (j = 0;j < col;j++)
	{
		printf("%2d ",j+1);//使用减号而不是下划线
		printf(" ");
	}
	printf("\n");
	//打印棋盘最上面的线
	printf("  |");
	for (j = 0;j < col;j++)
	{
		printf("---");//使用减号而不是下划线
		printf("|");
	}
	printf("\n");
	//打印棋格
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
			printf("---");//使用减号而不是下划线
			printf("|");
		}
		printf("\n");
	}
	//打印棋盘下横轴
	printf("   ");
	for (j = 0;j < col;j++)
	{
		printf("%2d ", j + 1);//使用减号而不是下划线
		printf(" ");
	}
}
//1号玩家下棋,要防止重复
void playermove1(char board[][COL], int x, int y)
{
	while (x > COL || y > ROW || x < 1 || y < 1)
	{//	最好把缓存区清空！不然输入不同类型时会出现死循环

		char c;
		while ((c = getchar()) != '\n')
		{
		}
		printf("输入坐标有误，请重新输入\n");
		scanf("%d.%d", &x, &y);

	}
	while (board[y - 1][x - 1] != ' ')
	{
		char c;
		while ((c = getchar()) != '\n')
		{
		}
		printf("输入坐标重复，请重新输入\n");
		scanf("%d.%d", &x, &y);
	}
	board[y - 1][x - 1] = '#';
}
//2号玩家下棋,要防止重复
void playermove2(char board[][COL], int x, int y)
{
	while (x > COL || y > ROW || x < 1 || y < 1)
	{//	最好把缓存区清空！不然输入不同类型时会出现死循环
		char c;
		while ((c = getchar()) != '\n')
		{}
		printf("输入坐标有误，请重新输入\n");
		scanf("%d.%d", &x, &y);
	}
	while (board[y - 1][x - 1] != ' ')
	{
		char c;
		while ((c = getchar()) != '\n')
		{
		}
		printf("输入坐标重复，请重新输入\n");
		scanf("%d.%d", &x, &y);
	}
	board[y - 1][x - 1] = '*';
}

//判断:一方胜，平(t)，继续(c)
char judge(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	int link = 1;
	//横
	for (i = 0;i < row;i++)
	{
		 link = 1;
		for (j = 0;j+4 < col ;j++)
		{
			if (board[i][j] == board[i][j + 1]&& board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4] && board[i][j] != ' ')
				return board[i][j];
		}
	}
	//竖
	for (i = 0;i < col;i++)
	{
		link = 1;
		for (j = 0;j+4 < row;j++)
		{
			if (board[j][i] == board[j + 1][i]&& board[j][i] == board[j + 2][i] && board[j][i] == board[j + 3][i] && board[j][i] == board[j + 4][i] && board[j][i] != ' ')
				return board[j][i];
		}
	}
	//斜——两种
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

	//继续
	for (i = 0;i < row;i++)
	{
		int j = 0;
		for (j = 0;j < col;j++)
		{
			if (board[i][j] == ' ')
				return 'c';
		}
	}
	//平局
	return 't';
}

