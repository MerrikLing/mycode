#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int cmp(const void* e1, const void* e2)
{
	return *(int*)e1 - *(int*)e2;
}
int main()
{
	int a[10] = { 6,5,3,2,8,9,7,1,0,4 };
	int sz = sizeof(a) / sizeof(a[0]);
	qsort(a, sz, sizeof(a[0]), cmp);
	int i = 0;
	for (i = 0;i < sz;i++)
		printf("%d ", a[i]);
	return 0;
}