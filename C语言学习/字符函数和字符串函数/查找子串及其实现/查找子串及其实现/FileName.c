#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
//strstr��������Ӵ���᷵���Ӵ��ĵ�ַ������᷵�ؿ�ָ��
//�����Ǳ�����⣬��ʵ�ϴ��ڸ�����ķ�������KMP�㷨
char* myStrstr(const char* a, const char* b)
{
	assert(a && b);
	const char* c = b;
	while (*a != '\0')
	{
		char* d = a; //���ƴ浵��
		while (*a == *b && *a!='\0')
		{
			a++;b++;
			if (*b == '\0')
				return c;
		}
		a = d + 1; //���� ��ȡ�浵
	}
	return NULL;
}
int main()
{
	char a[] = "You're sb that is good";
	char b[] = "You're sb";
	char* c = myStrstr(a, b);
	if (c == NULL)
		printf("  ������\n");
	else
		printf("%s",c);

	printf("\n%p  %p", b,c);
	return 0;
}