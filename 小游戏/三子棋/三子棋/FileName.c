
//����3*3�ķ�������ʵ����������һ�ߵ�ʤ���������ǶԽ���
//ģ��  1.���ɲ�չʾ���̣���ʾ��Һ͵����µ����� 2.�ж���Ϸʤ��  
//3.�������壨�������ѵ�������¡��޲��ԣ�
//
//��Կγ��г���ĸĽ��� 1.�����Ļ����ɣ� 2.������Ҷ�սģʽ
//���� 1.������Ҷ�ս�������� 2.�ı������������Ĳ��ԣ���������������ɣ�
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
		{//������
			system("cls");
			printf("��������");
			program(board, ROW, COL);
			display(board, ROW, COL);
			//�ж�
			char j = judge(board, ROW, COL);

			if (j == '*')
			{
				printf("���ʤ����\n��Ϸ����\n");
				break;
			}
			if (j == '#')
			{
				printf("���ʧ�ܣ�\n��Ϸ����\n");
				break;
			}
			if (j == 't')
			{
				printf("ƽ�֣�\n��Ϸ����\n");
				break;
			}
			//�����
			printf("\n  �����������������(�Ⱥ���ݣ��õ�ţ�0���Ҳࣩ����)\n");
			scanf("%d.%d", &x, &y);
			playermove(board, x, y);
			display(board, ROW, COL);

			//�ж�
			j = judge(board, ROW, COL);
			if (j == '*')
			{
				printf("���ʤ����\n��Ϸ����\n");
				break;
			}
			if (j == '#')
			{
				printf("���ʧ�ܣ�\n��Ϸ����\n");
				break;
			}
			if (j == 't')
			{
				printf("ƽ�֣�\n��Ϸ����\n");
				break;
			}

		}
		break;

	case 1:
		while (1)
		{			//�����
			printf("\n  �����������������(�Ⱥ���ݣ��õ�ţ�0���Ҳࣩ����)\n");
			scanf("%d.%d", &x, &y);
			playermove(board, x, y);
			//system("cls");
			display(board, ROW, COL);

			//�ж�
			char j = judge(board, ROW, COL);
			if (j == '*')
			{
				printf("���ʤ����\n��Ϸ����\n");
				break;
			}
			if (j == '#')
			{
				printf("���ʧ�ܣ�\n��Ϸ����\n");
				break;
			}
			if (j == 't')
			{
				printf("ƽ�֣�\n��Ϸ����\n");
				break;
			}
			//������
			system("cls");
			printf("��������");
			program(board, ROW, COL);
			display(board, ROW, COL);
			//�ж�
			j = judge(board, ROW, COL);

			if (j == '*')
			{
				printf("���ʤ����\n��Ϸ����\n");
				break;
			}
			if (j == '#')
			{
				printf("���ʧ�ܣ�\n��Ϸ����\n");
				break;
			}
			if (j == 't')
			{
				printf("ƽ�֣�\n��Ϸ����\n");
				break;
			}
		}
		break;
	}
}
int main()
{
	printf("                ������\n");
	printf(" ���� 1 ������£����� 2 �������£����� 0 ����\n");
	int in = 0;
	scanf("%d", &in);
	while (in)
	{
		game(in);
		printf(" ���� 1 ������£����� 2 �������£����� 0 ����\n");
		scanf("%d", &in);
	}
	return 0;
}