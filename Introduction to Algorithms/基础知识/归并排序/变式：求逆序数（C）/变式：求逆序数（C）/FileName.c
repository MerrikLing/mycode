#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//升序
void merge(int a[], int p, int p1, int r, long long* p_count)//p为第一段有序数列的起始点，p1为第二段的起始点
{
	int* ptr = (int*)malloc((r + 1 - p) * 4);
	assert(ptr);
	for (int i = p;i <= r;i++)
		*(ptr + i - p) = a[i];
	//从动态规划的内存中读取数列！
	//若一段数列取完了，就直接把另一段数列余下部分加上去
	int record = 0;
	int index1 = 0;
	int index2 = p1 - p + 1;
	int i = p;
	while (index1 <= p1 - p && index2 <= r - p)
	{
		if (*(ptr + index1) <= *(ptr + index2))
		{
			a[i] = *(ptr + index1);
			index1++;i++;*p_count += record;
		}
		else
		{
			a[i] = *(ptr + index2);
			index2++;i++;record++;
		}
	}
	if (index1 <= p1 - p)
	{
		while (i <= r)
		{
			a[i] = *(ptr + index1);
			i++;index1++;*p_count += record;
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
void MergeSort(int a[], int p, int r, long long* p_count) //p是排序起始位置的下标，r是结束位置的下标
{
	if (p >= r)
		return;
	int p1 = (p + r) / 2;
	MergeSort(a, p, p1, p_count);
	MergeSort(a, p1 + 1, r, p_count);
	merge(a, p, p1, r, p_count);
}
int main()
{
	printf("请输入要排序的数列元素数： ");
	int n;
	scanf("%d", &n);
	int* arr = (int*)malloc(n * 8);
	assert(arr);
	for (int i = 0;i < n;i++)
		scanf("%d", arr + i);
	long long count = 0;
	MergeSort(arr, 0, n - 1, &count);
	printf("逆序数为： %lld", count);
	free(arr);
	arr = NULL;
	return 0;
}