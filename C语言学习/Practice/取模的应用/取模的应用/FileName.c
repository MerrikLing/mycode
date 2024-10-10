#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int n;
	scanf("%d", &n);
	int i = 0;
	while (n > 0)
	{
		if (9 == n % 10)
			i++;
		n /= 10;
	}
	printf("%d", i);

	return 0;
}