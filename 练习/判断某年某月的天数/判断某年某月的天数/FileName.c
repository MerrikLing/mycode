#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//Ҳ���Դ���һ���·ݵ����顣���������Ķ��¾ͼ�һ
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
	printf("������������ݺ��·� ");
	scanf("%d %d", &a, &b);
	int y = is_leap(a);
	int d = month(y, b);
	printf("%d\n", d);
	return 0;
}