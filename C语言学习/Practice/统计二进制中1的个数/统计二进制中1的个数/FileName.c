#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int fun(int a)
{
	int i = 0;
	int c = 0;
	for (i = 1;i <= 32;i++)
	{
		if ((a & 1) == 1)
			c++;
		a >>= 1;
	}
	return c;
}
int main()
{
	int a = 0;
	scanf("%d", &a);
	int b = fun(a);
	printf("%d", b);
	return 0;
}