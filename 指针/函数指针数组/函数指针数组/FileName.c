#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int add(int x, int y)
{
	return x + y;
}
int sub(int x, int y)
{
	return x - y;
}
int mul(int x, int y)
{
	return x * y;
}
int div(int x, int y)
{
	return x / y;
}
void cal(int (*p)(int, int))
{
	printf("请输入两个数： ");
	int x = 0;
	int y = 0;
	scanf("%d%d", &x, &y);
	int ret = p(x, y);
	printf("%d\n", ret);
}
int main()
{
	int input = 0;

	do
	{
		printf("             计算器\n");
		printf(" 1.add 2.sub 3. mul 4.div 0.exit \n");
		scanf("%d", &input);
		int (*p[5])(int, int) = { 0,add,sub,mul,div };
		if (input == 1 || input == 2 || input == 3 || input == 4)
			cal(p[input]);
		else if (input == 0)
			break;
		else
			printf("输入错误！\n");
	} while (input);
	return 0;
}
