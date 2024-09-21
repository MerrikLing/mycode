#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	int d = 9;
	float *p= (float*)&d;
	printf("%f", *p);
	return 0;
}