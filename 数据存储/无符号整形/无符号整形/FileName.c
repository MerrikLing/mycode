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
	}//��ѭ��ԭ��iΪ�޷�������i=0���һ�ᱻ��Ϊ��������
	return 0;
}