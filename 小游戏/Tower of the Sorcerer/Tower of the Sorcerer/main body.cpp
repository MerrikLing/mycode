#include"head.hpp"
//��ʵ�ֿ���̨�汾����ʵ��ͼ�λ��汾
// 
// ������ͬ���ԵĽ�ɫ�� ���ӱ��䣬�������Ч���� ���ӽ��գ�
// ���ӶԵ��ֲ�
//��ɫ��������class��ʵ�֡���initi�г�ʼ����ң�ֱ�Ӵ���Ҳ��
//�浵�� ��������  ����Ч��  ը��? ����(��ǽ��)
//�������� ��ʾ���� �ֲ�  ���� ��ʯ
//ְҵ ħҩ ���� ���ص�ͼ ���ͼ

//�������������ƶ���ͼ�Σ� �£�ԭͼ���ϣ���Ӱ
//���ڵ����⣺
//
//
int main()
{start:
		/*printf("Brave warrior, welcome to the Tower of Sorcerer.\nPlease use your wisdom and courage to defeat the demon king and rescue the imprisoned princess! \n\n(Press any key to start the game)");
		_getch();*/
		//��ʼ��
		Player P;
		//zheshiweistingshusogohfoe
		initgraph(850, 650); // ��ʼ��һ������
		LoadImages();        // ����ͼƬ�ز�
		InitImage();         // ��ӡ��Ϸ������ʼ�ղ����ͼƬ
		//printf("%d", P.position[0]);
		int ret;
		int f = P.position[0];
		while(P.position[0]<FLOOR)
		{
			f = P.position[0];
			//display_map(Map[ P.position[0] ]);
			PrintMap(Map[P.position[0]],P);
			ret = move(Map[P.position[0]], P);
			//ret = 3;      //���ڵ���
			if (ret == 2) //����
			{
				//printf("Brave warrior,it's a reget that you have lost your life.\n");
				_getch();
				break;
			}
			if (ret == 3)   //ʤ����������ħ��
			{
				//printf("Congratulations!\nWith your great effort, you've managed to beat the demo king\nand save the princess from the Tower of the Sorcerer!\n");
				_getch();
				return 0;
			}
			//�������¥���޸�λ��,������λ�ù̶�Ϊ����һ��
			if (f != P.position[0])
			{
				P.position[1] -= 1;
				Map[P.position[0]][P.position[1]][P.position[2]] = 8;
			}
		}
		closegraph();        // �ر�ͼ�δ���
	
	return 0;
}

