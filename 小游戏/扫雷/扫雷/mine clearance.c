#include"mine clearance.h"
//注意左右上下多加了一行
//初始化展示的棋盘
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
//随机安放雷
void set_mine(int board[][COL + 2], int x, int y)
{
	srand((unsigned)time(NULL));
	//生成两倍于雷的随机数（坐标）
	int i = 0;
	for (i = 1;i <= mine;i++)
	{
		int x = rand() % ROW + 1;
		int y = rand() % COL + 1;
		//防止重复放雷，用循环！
		while (board[x][y] == 1)
		{
			x = rand() % ROW + 1;
			y = rand() % COL + 1;
		}
		board[x][y] = 1;
	}
}
//展示
void display(char board_show[][COL + 2])
{
	int i = 0;
	int j = 0;
	//打印上横轴
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ",i);
	printf("\n");
	//打印上横线
	printf("  |");
	for (i = 1;i <= COL;i++)
		printf("---|");
	printf("\n");
	//打印棋格
	for (i = 1;i <= ROW;i++)
	{
		printf("%2d|", i);
		for (j = 1;j <= COL;j++)
		{
			if (board_show[i][j] == '!')
			{
				printf("\033[40;31m * \033[0m");//打印红色*
				printf("|");
			}
			else if (board_show[i][j] == 0)
			{
				printf("   ");//打印空白
				printf("|");
			}
			else if (board_show[i][j] != '*')
			{
				printf("\033[40;32m %d \033[0m", board_show[i][j]);//打印绿色的数字，更醒目
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

	//下横轴
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ", i);
	printf("\n");
}

//玩家操作
int operation(char board_show[][COL + 2], int x, int y, int board[][COL + 2])
{
	//判断坐标是否出界、重复
	while (x<1 || x>COL || y<1 || y>ROW|| board[y][x] == 2)
	{
		int c = 0;
		while((c=getchar())!='\n')
		{ }
		printf("输入错误，请重新输入坐标（先横后纵，用点号.隔开）：  ");
		scanf("%d.%d", &x, &y);
	}
	//是否失败——返回1
	if (board[y][x] == 1)
		return 1;
	//坐标无雷
	board[y][x] = 2;
	//是否胜利——返回0
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
	//游戏继续,展示周围的雷数,返回2
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
	return 2;//此处也有问题，与主文件有关
}

//周围没有雷时，把周围清空
// (绝对不能写在operation里面！！否则会像冲击波一样扩散出去，最终造成“输入错误”)
void clear_sur(char board_show[][COL + 2], int x, int y, int board[][COL + 2])
{
	//判断是否满足条件
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
	{//执行
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
//标记或取消标记雷
void flag(char board_show[][COL + 2], int x, int y, int board[][COL + 2], int* m)
{
	////判断坐标是否输入过，是否合法。注意两次标记则变为原形
	//int i = 0;
	//int j = 0;
	//scanf("%d.%d", &x, &y);//这行语句为什么没有执行？
	while (x<1 || x>COL || y<1 || y>ROW || board[y][x] == 2)
	{
		int c = 0;
		while ((c = getchar()) != '\n')
		{
		}
		printf("输入错误，请再次输入坐标（先横后纵，用点号.隔开）：  ");
		scanf("%d.%d", &x, &y);
	}
	//注意两次执行要取消！并展示余下雷的数量
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

//展示雷排布
void mine_show(int board[][COL + 2])
{
	int i = 0;
	int j = 0;
	//打印上横轴
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ", i);
	printf("\n");
	//打印上横线
	printf("  |");
	for (i = 1;i <= COL;i++)
		printf("---|");
	printf("\n");
	//打印棋格
	for (i = 1;i <= ROW;i++)
	{
		printf("%2d|", i);
		for (j = 1;j <= COL;j++)
		{
			char c = ' ';
			if (board[i][j] == 1)
				c = '#';
			printf(" %c |", c);  //展示雷
		}
		printf("%d\n  |", i);
		for (j = 1;j <= COL;j++)
		{
			printf("---|");
		}
		printf("\n");
	}

	//下横轴
	printf("   ");
	for (i = 1;i <= COL;i++)
		printf("%2d  ", i);
	printf("\n");
}
