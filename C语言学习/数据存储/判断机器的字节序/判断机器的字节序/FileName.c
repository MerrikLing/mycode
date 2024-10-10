#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a = 0x12345678;
	////法1 人来看，调试开始后，查看内存，看a的即可
	//法2 电脑自行判断
	char* b = (char*)&a;//取出第一个字节进行判断
	if (*b == 0x78)
		printf("小端存储");
	else if (*b == 0x12)
		printf("小端存储");
	else
		printf("均不符合，程序错误");
	return 0;
}