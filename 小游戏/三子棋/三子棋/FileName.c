
//规则：3*3的方格中先实现三个棋子一线的胜利，可以是对角线
//模块  1.生成并展示棋盘，显示玩家和电脑下的棋子 2.判断游戏胜负  
//3.电脑下棋（？），难道是随机下、无策略？
//
//针对课程中程序的改进： 1.清除屏幕（完成） 2.增加玩家对战模式
//进阶 1.开发玩家对战的五子棋 2.改变程序下三子棋的策略，让它更聪明（完成）
#include"game.h"

void game(int in)
{
	int x = 0;
	int y = 0;
	char board[ROW][COL] = { 0 };
	ini(board, ROW, COL);
	display(board, ROW, COL);
	switch(in)

	{case 2:
		while (1)
		{//电脑下
			system("cls");
			printf("电脑下棋");
			program(board, ROW, COL);
			display(board, ROW, COL);
			//判断
			char j = judge(board, ROW, COL);

			if (j == '*')
			{
				printf("玩家胜利！\n游戏结束\n");
				break;
			}
			if (j == '#')
			{
				printf("玩家失败！\n游戏结束\n");
				break;
			}
			if (j == 't')
			{
				printf("平局！\n游戏结束\n");
				break;
			}
			//玩家下
			printf("\n  玩家请输入下棋坐标(先横后纵，用点号（0的右侧）隔开)\n");
			scanf("%d.%d", &x, &y);
			playermove(board, x, y);
			display(board, ROW, COL);

			//判断
			j = judge(board, ROW, COL);
			if (j == '*')
			{
				printf("玩家胜利！\n游戏结束\n");
				break;
			}
			if (j == '#')
			{
				printf("玩家失败！\n游戏结束\n");
				break;
			}
			if (j == 't')
			{
				printf("平局！\n游戏结束\n");
				break;
			}

		}
		break;

	case 1:
		while (1)
		{			//玩家下
			printf("\n  玩家请输入下棋坐标(先横后纵，用点号（0的右侧）隔开)\n");
			scanf("%d.%d", &x, &y);
			playermove(board, x, y);
			//system("cls");
			display(board, ROW, COL);

			//判断
			char j = judge(board, ROW, COL);
			if (j == '*')
			{
				printf("玩家胜利！\n游戏结束\n");
				break;
			}
			if (j == '#')
			{
				printf("玩家失败！\n游戏结束\n");
				break;
			}
			if (j == 't')
			{
				printf("平局！\n游戏结束\n");
				break;
			}
			//电脑下
			system("cls");
			printf("电脑下棋");
			program(board, ROW, COL);
			display(board, ROW, COL);
			//判断
			j = judge(board, ROW, COL);

			if (j == '*')
			{
				printf("玩家胜利！\n游戏结束\n");
				break;
			}
			if (j == '#')
			{
				printf("玩家失败！\n游戏结束\n");
				break;
			}
			if (j == 't')
			{
				printf("平局！\n游戏结束\n");
				break;
			}
		}
		break;
	}
}
int main()
{
	printf("                三子棋\n");
	printf(" 输入 1 玩家先下，输入 2 电脑先下，输入 0 结束\n");
	int in = 0;
	scanf("%d", &in);
	while (in)
	{
		game(in);
		printf(" 输入 1 玩家先下，输入 2 电脑先下，输入 0 结束\n");
		scanf("%d", &in);
	}
	return 0;
}