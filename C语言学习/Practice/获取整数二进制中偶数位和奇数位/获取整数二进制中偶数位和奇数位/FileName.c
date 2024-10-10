#define _CRT_SECURE_NO_WARNINGS
//获取一个整数二进制序列中所有的偶数位和奇数位，分别打印出二进制序列
#include<stdio.h>
int main()
{
	int a = 0;
	scanf("%d", &a);
	int i = 0;

	//奇数位
	for (i = 30;i >=0;i -= 2)
		printf("%d", (a >> i) & 1);
	printf("\n");
	for (i = 31;i >= 0;i -= 2)
		printf("%d", (a >> i) & 1);
	return 0;
}