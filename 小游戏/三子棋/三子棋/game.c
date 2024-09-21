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
	//打印棋盘最上面的线
	printf("|");
	for (j = 0;j < col;j++)
	{
		printf("---");//使用减号而不是下划线
		printf("|");
	}
	printf("\n");
	//打印棋格
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
			printf("---");//使用减号而不是下划线
			printf("|");
		}
		printf("\n");
	}
}
//玩家下棋,要防止重复
void playermove(char board[][COL], int x, int y)
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
	board[y - 1][x - 1] = '*';
}
//电脑下棋
void program(char board[ROW][COL], int row, int col)
{
	srand((unsigned)time(NULL));
	//策略：有两个连起来的，填第三个（分为进攻、防御）若无则随机填
	int i = 0;
	int j = 0;
	//进攻
	//横——尝试用循环解决
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
	//竖
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


	//对角线—2种
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
	//防守
//横——尝试用循环解决
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
	//竖
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


	//对角线—2种
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
	//随机下
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
//判断:一方胜，平(t)，继续(c)
char judge(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	//横
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
	//竖
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
	//斜（三子棋）
	if (board[0][0] == board[1][1] && board[2][2] == board[1][1] && board[0][0] != ' ')
		return board[0][0];
	if (board[2][0] == board[1][1] && board[0][2] == board[1][1] && board[1][1] != ' ')
		return board[1][1];
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

