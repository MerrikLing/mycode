#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int MYmemcmp(void* a, void* b, int n)
{
	while (n--)
	{
		if (*(char*)a > *(char*)b)
			return 1;
		if(*(char*)a < *(char*)b)
			return -1;
		a = (char*)a + 1;
		b = (char*)b + 1;
	}
	return 0;
}
int main()
{
	int a[] = { 1,2,3,4,5 };
	int b[] = { 1,0,3,4,5 };
	int ret = MYmemcmp(a, b, 12);
	printf("%d", ret);
	return 0;
}