#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//����ˮ�ɻ��� - Lily Number : ����������֣����м��ֳ��������֣�����1461��
//�Բ�ֳ�(1��461)��(14��61)��(146��1), ������в�ֺ�ĳ˻�֮�͵�������
//����һ��Lily Number.
//���� :
//	655 = 6 * 55 + 65 * 5
//	1461 = 1 * 461 + 14 * 61 + 146 * 1
//	��� 5λ���е����� Lily Number��
int main()
{
	int i = 0;
	int j = 0;
	for (i = 10000; i < 100000;i++)
	{
		int n = 0;
		for (j = 10;j < i;j *= 10)
			n += (i % j) * (i / j);
		if (n == i)
			printf("%d  ", n);
	}
	return 0;
}