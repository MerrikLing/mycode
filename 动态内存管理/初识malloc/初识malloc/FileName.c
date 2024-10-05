#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
int main()
{
	int a = 1;
	scanf("%d", &a);
	char* p = malloc(a);
	if (p == NULL)
	{
		printf("%s\n", strerror(errno));
		return 1;    //表示函数执行有问题
	}
	for (int i = 0;i < 19;i++)
	{
		//assert(p);
		*(p + i) = 60 + i;
	}
	for (int i = 0;i < 19;i++)
	{
		printf("%c ", * (p + i));
	}
	free(p);
	p = NULL;
	return 0;
}