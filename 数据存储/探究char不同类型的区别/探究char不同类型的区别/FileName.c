#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	//探究char, unsigned char,signed char
	char a = -1;
	unsigned char b = -1;
	signed char c = -1;
	printf("%d %d %d", a, b, c);//a c都是-1，b是255
	return 0;
}