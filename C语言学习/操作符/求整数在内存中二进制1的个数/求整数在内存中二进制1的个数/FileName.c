#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int  a = -5;
	int  i = 0;
	int  n = 0;
	//Ҳ���ò��ϳ�2��ģ2��ʵ�֡����о����ԣ��������У��Ż�����
	//ǿ��ת��Ϊ�޷�����



	//for (i =0 ;i < 32;i++)
	//{
	//	if (a & 1 == 1)
	//		n++;
	//	a=a >> 1;
	//}
	//����ķ�������ѭ��32�Σ��Ż�����
	while (a)
	{
		n++;
		//a=a& (a - 1);
		a  &= (a - 1);
	}//ÿִ��һ�Σ����ұߵ�1�ͱ�Ϊ0
	printf("%d", n);
	return 0;
}