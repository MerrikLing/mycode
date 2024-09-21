#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	printf("请输入一个数字  ");
	int a = 0;
	scanf("%d", &a);
	int i = 1;
	int j = 1;
	int r = 0;
	for (i = 1;i <= a;i++)
	{
		j *= i;
		r += j;
	}
	printf("%d", r);
	return 0;
}