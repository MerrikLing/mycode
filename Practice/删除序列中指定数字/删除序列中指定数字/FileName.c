#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	printf("输入序列中数字个数  ");
	scanf("%d", &a);
	int i = 0;
	int arr[50] = {0};
	for (i = 0;i < a;i++)
	{
		printf("输入序列中第 %d 数字  ",i+1);
		scanf("%d", &b);
		arr[i] = b;
	}
	for (i = 0;i < a;i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n输入序列中要删去的数字序号  ");
	scanf("%d", &c);

	for (i = 0;i < a;i++)
	{if(i!=c-1)
		printf("%d ", arr[i]);
	}
	return 0;
}