#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
#include<string.h>
//void my_strcpy(char b[], char a[])
//{
//	int i = strlen(a)-1;
//	while (i >= 0)
//	{
//		b[i] = a[i];
//		i--;
//	}
//}
//�Ż�
//void my_strcpy(char* bp, char* ap)
//{
//	while(*bp++=*ap++)//�ȸ�ֵ���ٵ�ַ��һ�����һ����\0����˹����ֵ��0һ��
//	{ }
//}
//��һ���Ż�
char* my_strcpy(char* bp, const char* ap)
{
	char* p = bp;
	assert(bp != NULL);
	assert(ap != NULL);
	while (*bp++ = *ap++)//�ȸ�ֵ���ٵ�ַ��һ�����һ����\0����˹����ֵ��0һ��
	{
	}
	return p;
}
int main()
{
	char a[] = "abcd";
	char b[5] = { 0 };	
	printf("%s", my_strcpy(b, a));
	return 0;
}