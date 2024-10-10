#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
int main()
{
	unsigned int i = 0;
	for (i = 3;i >= 0;i--)
	{
		printf("%u \n", i);
		Sleep(500);
	}//死循环原因：i为无符号数，i=0后减一会被视为最大的正数
	return 0;
}