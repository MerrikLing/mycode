#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#define _DEBUG_

void Find_max_subset(const int arr[], const int low, const int high, int record_max[])
{
	int max_current[3] = {0};//依次存储起始位置，终止位置，值
	for (int i = low;i <high;i++)
	{
		if (max_current[2] <=0)
		{
			max_current[0] = i;max_current[1] = i;max_current[2] = arr[i];
		}
		else
		{
			max_current[1] = i;max_current[2]+= arr[i];
		}
		if (max_current[2] >= record_max[2])
		{
			for (int j = 0;j < 3;j++)
				record_max[j] = max_current[j];
		}
	}
}
int main()
{
	int arr[] = { 100,113,110,85,105,102,86,63,81,101,94,106,101,79,94,90,97 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int* p = malloc(sizeof(int) * (sz-1));
	assert(p);
	for (int i = 0;i < sz - 1;i++)
	{
		*(p + i) = arr[i + 1] - arr[i];
#ifdef _DEBUG_

		printf("%d ", *(p + i));
#endif
	}
#ifdef _DEBUG_
	printf("\n");
#endif
	int record_max[3] = {0};
	Find_max_subset(p,0,sz-1, record_max);//d_arr, 0, sz - 1, & ret
	printf("最大值为：%d，对应子数组起始下标：%d，对应子数组终止下标：%d\n",record_max[2], record_max[0] + 1, record_max[1] + 1);
	free(p);
	p = NULL;
	return 0;
}