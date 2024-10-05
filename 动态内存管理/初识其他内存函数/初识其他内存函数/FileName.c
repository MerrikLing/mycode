#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
int main()
{
	int s;
	scanf("%d", &s);
	int* a = calloc(s, sizeof(int));
	if (a == NULL)
	{
		printf("%s", strerror(errno));
		return 1;
	}
	for (int i = 0;i < s;i++)
		printf("%d ",*(a + i));
	//
	int *a1=realloc(a, s * sizeof(int) + 20);
	printf("\n");
	assert(a1);
	a = a1;
	for (int i = 0;i < s+5;i++)
	{
		printf("%d ", *(a + i));
	}
	free(a);
	a = NULL;
	return 0;
}