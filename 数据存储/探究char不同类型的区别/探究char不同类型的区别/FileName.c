#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	//̽��char, unsigned char,signed char
	char a = -1;
	unsigned char b = -1;
	signed char c = -1;
	printf("%d %d %d", a, b, c);//a c����-1��b��255
	return 0;
}