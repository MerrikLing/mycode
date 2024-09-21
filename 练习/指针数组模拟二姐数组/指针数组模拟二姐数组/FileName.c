#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a[4] = { 1,2,3,4 };
	int b[4] = { 5,6,7,8 };
	int* p[2] = { a,b };
	int i = 0;
	int j = 0;
	for (i = 0;i < 2;i++)
	{
		for (j = 0;j < 4;j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
	return 0;
}