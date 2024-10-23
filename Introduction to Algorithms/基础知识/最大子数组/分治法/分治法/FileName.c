#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <string.h>
//#define _DEBUG_
struct ReturndData
{
	int ret_low;
	int ret_high;
	int value;
};typedef struct ReturndData RD;

void FindMax_Crossing_Subarray(const int darr[], const int low, const int mid, const int high, RD* p_ret)
{
	//left
	int value_left = darr[mid]; int sum = 0;int left = 0;
	for (int i = mid;i >= low;i--)
	{
		sum += darr[i];
		if (sum > value_left)
		{
			value_left = sum;
			left = i;
		}
	}
	//right
	sum = 0;
	int value_right = darr[mid + 1];int right = 0;
	for (int i = mid + 1;i <= high;i++)
	{
		sum+= darr[i];
		if (sum > value_right)
		{
			value_right = sum;
			right = i;
		}
	}
	p_ret->ret_low = left;
	p_ret->ret_high = right;
	p_ret->value = value_left + value_right;
}
void FindMaxSubarray(const int darr[], const int low, const int high,RD*p_ret)//利用结构体返回多个参数
{
	if (low >= high)
	{
		p_ret->ret_low = low;
		p_ret->ret_high = high;
		p_ret->value = darr[low];
		return;
	}
	int mid = (low + high) / 2;

	FindMaxSubarray(darr, low, mid, p_ret);
	RD left;
	memcpy(&left, p_ret, sizeof(RD));

	FindMaxSubarray(darr, mid+1, high, p_ret);
	RD right;
	memcpy(&right, p_ret, sizeof(RD));

	FindMax_Crossing_Subarray(darr, low, mid, high, p_ret);
	RD cross;
	memcpy(&cross, p_ret, sizeof(RD));

	if (cross.value >= right.value && cross.value >= left.value)
		return;
	if (right.value >= cross.value && right.value >= left.value)
	{
		memcpy(p_ret, &right, sizeof(RD));
		return;
	}
	memcpy(p_ret, &left, sizeof(RD));
	return;
}
int main()
{
	int arr[] = { 100,113,110,85,105,102,86,63,81,101,94,106,101,79,94,90,97 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int* d_arr = (int*)malloc((sz - 1) * sizeof(int));
	assert(d_arr);
	for (int i = 0;i < sz - 1;i++)
	{
		*(d_arr + i)= arr[i + 1] - arr[i];
#ifdef _DEBUG_

		printf("%d ", *(d_arr + i));
#endif
	}
#ifdef _DEBUG_
	printf("\n");
#endif
	RD ret = {0};
	FindMaxSubarray(d_arr,0, sz - 1,&ret);
	printf("最大值为：%d，对应子数组起始下标：%d，对应子数组终止下标：%d\n", ret.value, ret.ret_low+1, ret.ret_high+1);

	free(d_arr);
	d_arr = NULL;
	return 0;
}