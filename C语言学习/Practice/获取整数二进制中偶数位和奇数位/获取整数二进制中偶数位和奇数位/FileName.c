#define _CRT_SECURE_NO_WARNINGS
//��ȡһ���������������������е�ż��λ������λ���ֱ��ӡ������������
#include<stdio.h>
int main()
{
	int a = 0;
	scanf("%d", &a);
	int i = 0;

	//����λ
	for (i = 30;i >=0;i -= 2)
		printf("%d", (a >> i) & 1);
	printf("\n");
	for (i = 31;i >= 0;i -= 2)
		printf("%d", (a >> i) & 1);
	return 0;
}