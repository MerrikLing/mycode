#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//�˴�ʵ����������
//�Ƚ���������������ʵ��ǰ��������ǰ�������򡭡�
void sort(int arr[])
{
	int i = 0;
	for (i = 1;i <= 9;i++)
	{
		int j = 0;
		for (j = i;j >0;j--)
			if (arr[j-1] > arr[j])
			{
				int a = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = a;
			}
	}
}
int main()
{
	int arr[] = { 9,1,6,4,5,2,7,8,0,3 };
	sort(arr);
	int i = 0;
	for (i = 0; i < 10;i++)
		printf("%d ", arr[i]);
	return 0;
}