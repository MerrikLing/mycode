#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//输入一个整形数组，调整奇数的位置，使其全部位于数组前半部分，偶数全位于后半
void sort(int a[])
{
	int i = 0;
	int count = 0;
	for(i=0;i<10;i++)
	{
		if (a[i] % 2 != 0)
		{
			int j = a[count];
			a[count++] = a[i];
			a[i] = j;
	    } 
	}
}
int main()
{
	printf("请输入10个数字： ");
	int a[10] = { 0 };
	int i = 0;
	for (i = 0;i < 10;i++)
		scanf("%d", &a[i]);
	sort(a);
	for (i = 0;i < 10;i++)
		printf("%d ", a[i]);

	return 0;
}