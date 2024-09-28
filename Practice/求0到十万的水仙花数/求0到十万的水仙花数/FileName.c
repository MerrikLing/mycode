#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int s = 0;
	int x = 0;
	for (x = 0;x <= 100000;x++)
	{
		i = x;
		s = 0;
		j = 10;
		while (i)
		{
			s+= (i % j) * (i % j) * (i % j);
			i /= j;
		}
		if (s == x)
			printf("%d ", x);
	}
	return 0;
}