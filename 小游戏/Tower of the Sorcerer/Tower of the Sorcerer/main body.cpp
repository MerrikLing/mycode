#include"head.hpp"
//��ʵ�ֿ���̨�汾����ʵ��ͼ�λ��汾
// 
// ������ͬ���ԵĽ�ɫ�� ���ӱ��䣬�������Ч���� ���ӽ��գ�
// ���ӶԵ��ֲ�
//��ɫ��������class��ʵ�֡���initi�г�ʼ����ң�ֱ�Ӵ���Ҳ��
//�浵�� ��������  ����Ч��  ը��? ����(��ǽ��)
//�ֲ�  ���� ��ʯ
//ְҵ ħҩ ���� ���ص�ͼ ���ͼ

//������Խ����������
// ���  �������� ��
// ����ˮ���� ����  
//������Ч���������� ���Կ��ǲ�ͬ¥�㲻ͬ�ı�������
//���ڵ����⣺
// ��ֵ�����⣡ ���Կ���ÿ�������Ʋ�ͬ����ֵ
//����
//���˫�����޷��򴩶Է��ķ����ͻ���ѭ��

//��Ϸ˵���� �����������ɿ��ӻ�
//���밴ESC�˳����� ��Ҫֱ�ӵ�رգ���������Ƶ��Դ�����ͷţ���Ƶ�����𻵣���

int main()
{
		Player P;            //��ʼ��
		initgraph(850, 650); // ��ʼ��һ������
		LoadImages();        // ����ͼƬ�ز�
		StartImage();        // ��Ϸ��ʼ����
		InventInfor();       //��������Ϣ
		//��������
		PlaySound(TEXT("ZeldaBackground.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP); //�������ֻ�����ڴ�������Ƶ��
		InitImage();         // ��ӡ��Ϸ������ʼ�ղ����ͼƬ
		int ret;
		int f = P.position[0];
		while(P.position[0]<FLOOR)
		{
			f = P.position[0];
			PrintMap(Map[P.position[0]],P);
			ret = play(Map[P.position[0]], P);
			if (ret == -12)
			{
				break;
			}
			else if (ret == 2) //����
			{
				musicDie();
				PrintLose();
				break;
			}
			else if (ret == 3)   //ʤ�������ҵ�����
			{
				musicWin();
				PrintWin();
				break;
			}
			//ret 4 5 6 7 �ֱ��ʾ�������ң�����¥��ת����ĳ�ʼλ��
			if (f != P.position[0])
			{ 
				ChangeFloor(Map,P,ret);
			}
		}
		closeMusic();
		closegraph();        // �ر�ͼ�δ���
	
	return 0;
}

