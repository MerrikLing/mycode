#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a[3] = { 0 };
	int b[4] = { 0 };
	int i = 0;
	printf("�����1�����飨3������ ");
	for (i = 0;i < 3;i++)
		scanf("%d", a + i);
	printf("����ڶ������飨4������ ");
	for (i = 0;i < 4;i++)
		scanf("%d", b + i);
	int c[7] = { 0 };
	//�Ȱ�����ȫ������һ�����飬��bubble sort
	for (i = 0;i < 3;i++)
	{
		c[i] = a[i];
	}
	for (i = 0;i < 4;i++)
		c[i + 3] = b[i];
	int j = 0;
	int s = 0;
	for (i = 0;i < 6;i++)
	{
		j = 0;
		for(j=0;j<6-i;j++)
			{ if(c[j]>c[j+1])
			   {
			s = c[j + 1];
				c[j + 1] = c[j];
				c[j] = s;
			   }
			
		}
	}
	for (i = 0;i < 7;i++)
		printf("%d ", c[i]);
	return 0;
}