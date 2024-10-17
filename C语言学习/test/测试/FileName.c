#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define A a
int f()
{
	return 2 == 1;
}
int main()
{
	int x = 0;
	int y = 0;
	int i = 2;
	int ret = f();
	//printf("%d", ret);
	if (2 == 2.0)
		printf("equal");
	else
		printf("inequal");

	return 0;
}