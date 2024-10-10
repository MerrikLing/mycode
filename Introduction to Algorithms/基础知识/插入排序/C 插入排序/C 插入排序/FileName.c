#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void insertion_sort(int* p,int sz)
{
	for (int j = 1;j < sz;j++)
	{
		int key = p[j];//从第二个元素开始
		////升序
		//int i;
		//for (i = j - 1;key < p[i] && i >= 0;i--)
		//{
		//	p[i + 1] = p[i];
		//}
		//p[i+1] = key;
		
		//降序
		int i;
		for (i = j - 1;key > p[i] && i >= 0;i--)
		{
			p[i + 1] = p[i];
		}
		p[i + 1] = key;
	}
}
int main()
{
	int a[5];
	for (int i = 0;i < 5;i++)
		scanf("%d", &a[i]);
	int sz = sizeof(a) / sizeof(a[0]);
	insertion_sort(a,sz);
	for (int i = 0;i < 5;i++)
		printf("%d ", a[i]);
	return 0;
}