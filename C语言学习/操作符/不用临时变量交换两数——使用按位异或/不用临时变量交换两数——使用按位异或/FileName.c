#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 7;
	int b = 5;
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("%d %d",a,b);
	return 0;
}