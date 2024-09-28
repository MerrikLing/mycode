#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//此处实现升序排列
void bubble_sort(int arr[])
{
	int i = 0;
	for (i = 1;i <= 9;i++)
	{
		int j = 0;
		for(j=0;j<10-i;j++)
			if (arr[j] > arr[j + 1])
			{
				int a = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = a;
			}
	}
}
int main()
{
	int arr[] = { 9,1,6,4,5,2,7,8,0,3 };
	bubble_sort(arr);
	int i = 0;
	for (i = 0; i< 10;i++)
		printf("%d ", arr[i]);
	return 0;
}