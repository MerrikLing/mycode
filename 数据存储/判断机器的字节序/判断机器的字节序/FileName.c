#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0x12345678;
	////��1 �����������Կ�ʼ�󣬲鿴�ڴ棬��a�ļ���
	//��2 ���������ж�
	char* b = (char*)&a;//ȡ����һ���ֽڽ����ж�
	if (*b == 0x78)
		printf("С�˴洢");
	else if (*b == 0x12)
		printf("С�˴洢");
	else
		printf("�������ϣ��������");
	return 0;
}