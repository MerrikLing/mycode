#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	char a = 0;
	scanf("%c", &a);
	if (a <= 'z' && a >= 'a')
		a += 'A' - 'a';
	else if (a <= 'Z' && a >= 'A')
		a += 'a' - 'A';
	printf("%c", a);
	return 0;
}