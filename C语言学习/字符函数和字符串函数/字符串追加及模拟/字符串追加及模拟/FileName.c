#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//ע��strcat���ܸ��Լ�׷�ӣ���Ϊ��β��\0�ᱻ���ǵ���������ѭ��
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