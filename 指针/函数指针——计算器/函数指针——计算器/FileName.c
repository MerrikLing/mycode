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
int mul(int x ,int y)
{
	return x * y;
}
int div(int x,int y)
{
	return x / y;
}
void cal(int (*p)(int, int))
{
	printf("�������������� ");
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
		printf("             ������\n");
		printf(" 1.add 2.sub 3. mul 4.div 0.exit \n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			cal(add);
			break;
		case 2:
			cal(sub);
			break;
		case 3:
			cal(mul);
			break;
		case 4:
			cal(div);
			break;
		case 0:
			printf("   �˳�������\n");
			break;
		default:
			printf("�������\n");
			break;
		}
	} while (input);
	return 0;
}
