#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//也可以创建一个月份的数组。如果是闰年的二月就加一
int is_leap(int a)
{
	if ((a % 4 == 0 && 0 != a % 100) || (a % 400 == 0))
		return 1;
	return 0;
}
int month(int y, int b)
{
	if (y == 1 && b == 2)
		return 29;
	else if (y == 0 && b == 2)
		return 28;
	else if (b == 4 || b == 6 || b == 9 || b == 11)
		return 30;
	return 31;
}
int main()
{
	int a = 0;
	int b = 0;
	printf("请依次输入年份和月份 ");
	scanf("%d %d", &a, &b);
	int y = is_leap(a);
	int d = month(y, b);
	printf("%d\n", d);
	return 0;
}