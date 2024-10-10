#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//小乐乐喜欢数字，尤其喜欢0和1。他现在得到了一个数，想把每位的数变成0或1。
//如果某一位是奇数，就把它变成1，如果是偶数，那么就把它变成0。请你回答他最
//后得到的数是多少。
//int main()
//{
//	int a;
//	int i = -1;
//	int n[9] = {0};
//	scanf("%d", &a);
//	while (a)
//	{
//		i++;
//		n[i] = a % 2;
//		a /= 10;
//	}
//	while (i>-1)
//	{
//		printf("%d", n[i--]);
//	}
//	return 0;
//}
//
//
////打印带有空格的*组成的直角三角形
//int main()
//{
//	int a;
//	scanf("%d", &a);
//	for (int i = 0;i < a;i++)
//	{
//		for (int j = 0;j < a - 1 - i;j++)
//			printf("  ");
//		for (int j = 0;j <= i;j++)
//			printf("* ");
//		printf("\n");
//
//	}
//	return 0;
//}


//实现一个能被字符串左边指定个数的元素放在字符串最后边的函数
void f(int i, char*a,int s)
{
	//思路:相邻逐个交换
	i %= s;
	while (i--)
	{
		for (int j = 0;j < s-1;j++)
		{
			char t = *(a + 1+j);
			*(a + 1 + j) = *(a+j);
			*(a + j) = t;
		}

	}
}
//易错，字符串末尾是\0
int main()
{
	char a[] = "abcdef";
	int i = 0;
	int s=strlen(a);
	scanf("%d", &i,s);
	f(i,a,s);
	printf("%s\n", a);
	return 0;
}