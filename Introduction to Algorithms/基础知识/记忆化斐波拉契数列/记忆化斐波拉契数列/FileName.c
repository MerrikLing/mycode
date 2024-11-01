#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
long long better_fib(int in, long long* p)
{
	if (*(p + in - 1) != 0)
	{ }
	else if (in <= 2)
		*(p + in-1) = 1;
	else
		*(p + in - 1)= better_fib(in - 1, p) + better_fib(in - 2, p);
	return *(p + in - 1);
}
int main()
{	while(1)
	{
		printf("计算菲波拉契数\n请输入： ");
		int in;
		scanf("%d", &in);
		long long* p = calloc(in, sizeof(long long));
		assert(p);

		printf("第%d个菲波拉契数：%lld\n\n", in, better_fib(in, p));

		free(p);
		p = NULL;
	}
	return 0;
}