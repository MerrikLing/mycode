#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//注意strcat不能给自己追加！因为结尾的\0会被覆盖掉，陷入死循环
char* MyStrcat(char* a,char *b)
{
	while (*a != '\0')
		a++;
	while (*a++ = *b++)
		;
}
int main()
{
	char a[50] = "Hello! ";
	strcat(a, "I'm coming!");
	MyStrcat(a, " Prepare for it!");
	printf("%s", a);
	return 0;
}