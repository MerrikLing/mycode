#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//��Ϊ��ӡһ�����Σ�����
int main()
{
	int a = 0;
	int i = 0;
	int j = 0;
	int h = 0;
	printf("������ ");
	scanf("%d", &a);
	for (i = 1;i <= a;i++)
	{
		for (j = 1;j <= a;j++)
		{
			if (j == i || j + i == a + 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	
	return 0;
}