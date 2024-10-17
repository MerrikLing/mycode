#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//����
void merge(int a[],int p,int p1, int r)//pΪ��һ���������е���ʼ�㣬p1Ϊ�ڶ��ε���ʼ��
{
	int* ptr = (int*)malloc((r + 1 - p) * 4);
	assert(ptr);
	for (int i = p;i <= r;i++)
		*(ptr + i - p) = a[i];
	//�Ӷ�̬�滮���ڴ��ж�ȡ���У�
	//��һ������ȡ���ˣ���ֱ�Ӱ���һ���������²��ּ���ȥ
	int index1 = 0; 
	int index2 = p1 - p + 1;
	int i = p;
	while (index1 <= p1 - p && index2 <= r-p)
	{
		if (*(ptr + index1) <= *(ptr + index2))
		{
			a[i] = *(ptr + index1);
			index1++;i++;
		}
		else
		{
			a[i] = *(ptr + index2);
			index2++;i++;
		}
	}
	if(index1 <= p1 - p)
	{
		while (i <= r)
		{
			a[i] = *(ptr + index1);
			i++;index1++;
		}
	}
	else
	{
		while (i <= r)
		{
			a[i] = *(ptr + index2);
			i++;index2++;
		}
	}
	free(ptr);
	ptr = NULL;
}
void MergeSort(int a[], int p, int r) //p��������ʼλ�õ��±꣬r�ǽ���λ�õ��±�
{
	if (p >= r)
		return;
	int p1 = (p + r) / 2;
	MergeSort(a, p, p1);
	MergeSort(a, p1+1, r);
	merge(a,p,p1,r);
}
int main()
{
	int a[] = { 9,4,19,5,16,7,2,12,0,3,3,1 };
	int b = sizeof(a) / sizeof(a[0]);
	MergeSort(a,0,b-1);
	for (int i = 0;i < b;i++)
		printf("%d ", a[i]);
	return 0;
}