
//��������⣺
//���������  չʾ�����ĺ�ʵ����Ĳ�һ��   �����Ҫ�жϣ��������ʾ�ո��ʤ
// �����Ҫͬʱ��ʵ�ʵġ�չʾ�Ĳ��������ȶ�ʵ�ʵĲ������滻�����жϣ���û���ٶ�
//չʾ�Ĳ���   �ظ��������������� 6.���칦�� ����Χû���ף�����Χ���
//  ��Ϸ������չʾ�׵��Ų�
//
#include"mine clearance.h"
void game()
{
	int x = 0;
	int y = 0;
	int ret = 0;
	int sign = 2;
	int m = mine;
	int board[ROW + 2][COL + 2] = { 0 };//+2���ھŹ������ף���Ե�Ͳ������⻯��
	char board_show[ROW + 2][COL + 2] = { 0 };//չʾ������
	ini(board_show);
	set_mine(board, ROW + 2, COL + 2);
	printf("\n            ʣ�� %d ����\n", m);
	display(board_show);
	//mine_show(board);//����ʱʹ��
	while(1)
	{
		printf("����׻�ȡ����ǣ����� **\n��ͨ�������������꣨�Ⱥ���ݣ��õ��.��������  ");
		sign=scanf("%d.%d", &x, &y);
		if(sign==2)
		{
			ret = operation(board_show, x, y, board);
			//ʧ�ܷ���1,�ɹ�����0����������2
			if (1 == ret)
			{
				printf("\n  ���ź�����ȵ����ף���Ϸ������      �׷ֲ���\n");
				mine_show(board);
				break;
			}
			if (0 == ret)
			{
				printf("\n  ��ϲ�㣬ɨ�׳ɹ�����Ϸ������       �׷ֲ���\n");
				mine_show(board);
				break;
			}
			if (2 == ret)
			{
				clear_sur(board_show, x, y, board);
				system("cls");
				printf("\n            ʣ�� %d ����\n", m);
				display(board_show);
			}
		}
		else if (sign == 0)
		{//����ջ����������ƺ�����**��ʹscanf���ֲ���֪�Ľ����������ѭ��
			int c = 0;
			while ((c = getchar()) != '\n')
			{
			}
			printf("����������Ϊ���׵�����:  ");
			scanf("%d.%d", &x, &y);
			flag(board_show, x, y, board,&m);
			system("cls");
			printf("\n            ʣ�� %d ����\n", m);
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
		printf("               ɨ��\n");
		//�������˵��
		game();
		printf("\n���� 1 �ٴ���Ϸ������ 0 ������Ϸ   ");
		scanf("%d", &in);
	}
	while (in);
    return 0;
}