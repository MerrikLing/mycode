#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//�����ҵ���С��Ԫ�أ�������A[0]������Ȼ���ҵ��ڶ�С��Ԫ�أ���������
void choose_sort(int a[],int b) //����
{
	for (int i = 0;i < b-1;i++)
	{
		int key = a[i];
		int record = i;
		for (int j = i+1;j < b;j++)
		{
			if (a[j] < key)
			{
				key = a[j];
				record = j;
			}
		}
		if (record > i)
		{
			int swap = a[i];
			a[i] = key;
			a[record] = swap;
		}
	}
}
int main()
{
	int a[] = { 9, 5, 6, 49, 2, 3,3, 7, 8, 19, 12 };
	int b = sizeof(a) / sizeof(a[0]);
	choose_sort(a,b);
	for (int i = 0;i < b;i++)
		printf("%d ", a[i]);
	return 0;
}