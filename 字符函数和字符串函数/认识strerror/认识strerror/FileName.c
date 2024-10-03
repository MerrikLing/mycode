#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<errno.h>
int main()
{
	//printf("%s\n", strerror(12));
	//printf("%s\n", strerror(19));
	/*char a;
	scanf("%c", &a);
	printf("%s\n", strerror(errno));*/
	printf("%c\n", tolower('S'));
	printf("%c\n", tolower('s'));
	printf("%c\n", tolower(';'));
	printf("%c\n", toupper('S'));
	printf("%c\n", toupper('s'));
	printf("%c\n", toupper(';'));
	return 0;
}