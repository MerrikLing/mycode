#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//两个int(32位)整数m和n的二进制表达中，有多少个位(bit)不同
//不是补码
int fun(int m, int n)
{
	if (m < 0)
		m = -m;
	if (n < 0)
		n = -n;
	int i = 0;
	int count = 0;
	//for (i = 0;i < 32;i++)
	//{
	//	if (((m >> i) & 1) != ((n >> i) & 1))
	//	{
	//		count++;
	//	}
	//}

	//另一种实现方法，用^
	int x = m ^ n;
	while (x)
	{
		count++;
		x = x & (x - 1);
	}
	return count;
}
int main()
{
	int m = 0;
	int n = 0;
	scanf("%d", &m);
	scanf("%d", &n);
	int a=fun(m, n);
	printf("%d", a);
	return 0;
}