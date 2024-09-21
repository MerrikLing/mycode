#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int f(int a, int b)
{
	int x = a;
	int y = b;
	//a = a % b;	
	while (a)
	{
		b %= a;
		int d = b;
		b = a;
		a = d;
	}
	return x * y / b;
}
int main()
{
	int a = 0;
	int b = 0;
	scanf("%d%d", &a, &b);
	int c = f(a, b);
	printf("%d", c);
	return 0;
}