#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define A a
int f(int s)
{
	return s == 1;
}
int main()
{
	int x = 0;
	int y = 0;
	int i = 2;
	//for (i = 0;i < 10;i++)
	//	printf("%d", i);
	//printf("\n");
	//for (i = 3;i < 10;i++)
	scanf("%d", &x);
	i = f(x);
	printf("%d", i);

	return 0;
}