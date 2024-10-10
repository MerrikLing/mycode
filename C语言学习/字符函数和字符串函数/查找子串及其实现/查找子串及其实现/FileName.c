#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
//strstr如果存在子串则会返回子串的地址，否则会返回空指针
//以下是暴力求解，事实上存在更精妙的方法——KMP算法
char* myStrstr(const char* a, const char* b)
{
	assert(a && b);
	const char* c = b;
	while (*a != '\0')
	{
		char* d = a; //类似存档点
		while (*a == *b && *a!='\0')
		{
			a++;b++;
			if (*b == '\0')
				return c;
		}
		a = d + 1; //类似 读取存档
	}
	return NULL;
}
int main()
{
	char a[] = "You're sb that is good";
	char b[] = "You're sb";
	char* c = myStrstr(a, b);
	if (c == NULL)
		printf("  不存在\n");
	else
		printf("%s",c);

	printf("\n%p  %p", b,c);
	return 0;
}