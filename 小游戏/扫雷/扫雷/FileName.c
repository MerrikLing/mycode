
//解决的问题：
//随机安放雷  展示出来的和实际埋的不一样   输入的要判断，输或者显示空格或胜
// 输入后要同时对实际的、展示的操作——先对实际的操作（替换），判断，若没输再对
//展示的操作   重复和输入错误的提醒 6.插旗功能 若周围没有雷，把周围清空
//  游戏结束后展示雷的排布
//
#include"mine clearance.h"
void game()
{
	int x = 0;
	int y = 0;
	int ret = 0;
	int sign = 2;
	int m = mine;
	int board[ROW + 2][COL + 2] = { 0 };//+2便于九宫格找雷（边缘就不用特殊化）
	char board_show[ROW + 2][COL + 2] = { 0 };//展示的棋盘
	ini(board_show);
	set_mine(board, ROW + 2, COL + 2);
	printf("\n            剩余 %d 个雷\n", m);
	display(board_show);
	//mine_show(board);//调试时使用
	while(1)
	{
		printf("标记雷或取消标记，输入 **\n普通操作则输入坐标（先横后纵，用点号.隔开）：  ");
		sign=scanf("%d.%d", &x, &y);
		if(sign==2)
		{
			ret = operation(board_show, x, y, board);
			//失败返回1,成功返回0，继续返回2
			if (1 == ret)
			{
				printf("\n  很遗憾，你踩到了雷，游戏结束！      雷分布：\n");
				mine_show(board);
				break;
			}
			if (0 == ret)
			{
				printf("\n  恭喜你，扫雷成功，游戏结束！       雷分布：\n");
				mine_show(board);
				break;
			}
			if (2 == ret)
			{
				clear_sur(board_show, x, y, board);
				system("cls");
				printf("\n            剩余 %d 个雷\n", m);
				display(board_show);
			}
		}
		else if (sign == 0)
		{//先清空缓存区——似乎输入**会使scanf出现不可知的结果，导致死循环
			int c = 0;
			while ((c = getchar()) != '\n')
			{
			}
			printf("请输入你认为是雷的坐标:  ");
			scanf("%d.%d", &x, &y);
			flag(board_show, x, y, board,&m);
			system("cls");
			printf("\n            剩余 %d 个雷\n", m);
			display(board_show);
		}
	}
}

int main()
{
	int in = 0;
	do
	{
		system("cls");
		printf("               扫雷\n");
		//加入规则说明
		game();
		printf("\n输入 1 再次游戏，输入 0 结束游戏   ");
		scanf("%d", &in);
	}
	while (in);
    return 0;
}