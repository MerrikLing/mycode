#include"game.h"
//�Ľ���չʾÿ��ÿ����ţ����ж�
void game()
{
	int x = 0;
	int y = 0;
	char board[ROW][COL] = { 0 };
	ini(board, ROW, COL);
	display(board, ROW, COL);
	while (1)
	{//1�������(#)
		printf("\n  1�������������������(�Ⱥ���ݣ��õ�ţ�0���Ҳࣩ����)  ");
		scanf("%d.%d", &x, &y);
		playermove1(board, x, y);
		display(board, ROW, COL);
		//�ж�
		char j = judge(board, ROW, COL);

		if (j == '*')
		{
			printf("\n2�����ʤ����\n��Ϸ����\n");
			break;
		}
		if (j == '#')
		{
			printf("\n1�����ʤ����\n��Ϸ����\n");
			break;
		}
		if (j == 't')
		{
			printf("\nƽ�֣�\n��Ϸ����\n");
			break;
		}
		//2������£�*��
		printf("\n  2�������������������(�Ⱥ���ݣ��õ�ţ�0���Ҳࣩ����)   ");
		scanf("%d.%d", &x, &y);
		playermove2(board, x, y);
		display(board, ROW, COL);

		//�ж�
		j = judge(board, ROW, COL);
		if (j == '*')
		{
			printf("\n2�����ʤ����\n��Ϸ����\n");
			break;
		}
		if (j == '#')
		{
			printf("\n1�����ʤ����\n��Ϸ����\n");
			break;
		}
		if (j == 't')
		{
			printf("\nƽ�֣�\n��Ϸ����\n");
			break;
		}

	}
}
int main()
{
	printf("      ������(��Ҷ�ս)\n");
	printf(" ���� 1 ��ʼ������ 0 ����\n");
	int in = 0;
	scanf("%d", &in);
	while (in)
	{
		game();
		printf("��Ϸ���������� 1 ��ʼ��һ�֣����� 0 ����\n");
		scanf("%d", &in);
	}
	return 0;
}