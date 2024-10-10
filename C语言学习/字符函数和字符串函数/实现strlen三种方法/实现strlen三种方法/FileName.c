#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//第一种
int strlen_1(const char* a)
{
	int b = 0;
	while (*a++ != '\0')
	{ b++; }
	return b;
}
//指针作差
int strlen_2(const char* a)
{
	char* p = a;
	while(*p != '\0')
	{
		p++;
	}
	int c = p - a;
	return c;
}
//递归
int strlen_3(const char* a)
{
	if (*a == '\0')
		return 0;
	return 1 + strlen_3(a + 1);
}
int main()
{
	char a1[] = "abcdefghi";//9个
	char a2[] = "ab";
	char a3[] = "avsf2";
	//int b1 = strlen_1(a1);
	//int b2 = strlen_2(a2);
	int b3 = strlen_3(a3);

	//printf("%d\n", b1);
	//printf("%d\n", b2);
	printf("%d\n", b3);
	return 0;
}