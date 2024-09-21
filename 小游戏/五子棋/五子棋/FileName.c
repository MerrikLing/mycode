#include"game.h"
//改进：展示每行每列序号，改判断
void game()
{
	int x = 0;
	int y = 0;
	char board[ROW][COL] = { 0 };
	ini(board, ROW, COL);
	display(board, ROW, COL);
	while (1)
	{//1号玩家下(#)
		printf("\n  1号玩家请输入下棋坐标(先横后纵，用点号（0的右侧）隔开)  ");
		scanf("%d.%d", &x, &y);
		playermove1(board, x, y);
		display(board, ROW, COL);
		//判断
		char j = judge(board, ROW, COL);

		if (j == '*')
		{
			printf("\n2号玩家胜利！\n游戏结束\n");
			break;
		}
		if (j == '#')
		{
			printf("\n1号玩家胜利！\n游戏结束\n");
			break;
		}
		if (j == 't')
		{
			printf("\n平局！\n游戏结束\n");
			break;
		}
		//2号玩家下（*）
		printf("\n  2号玩家请输入下棋坐标(先横后纵，用点号（0的右侧）隔开)   ");
		scanf("%d.%d", &x, &y);
		playermove2(board, x, y);
		display(board, ROW, COL);

		//判断
		j = judge(board, ROW, COL);
		if (j == '*')
		{
			printf("\n2号玩家胜利！\n游戏结束\n");
			break;
		}
		if (j == '#')
		{
			printf("\n1号玩家胜利！\n游戏结束\n");
			break;
		}
		if (j == 't')
		{
			printf("\n平局！\n游戏结束\n");
			break;
		}

	}
}
int main()
{
	printf("      五子棋(玩家对战)\n");
	printf(" 输入 1 开始，输入 0 结束\n");
	int in = 0;
	scanf("%d", &in);
	while (in)
	{
		game();
		printf("游戏结束。输入 1 开始下一局，输入 0 结束\n");
		scanf("%d", &in);
	}
	return 0;
}