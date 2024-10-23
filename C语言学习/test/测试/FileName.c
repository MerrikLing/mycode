#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
int main()
{
	int* d = (int*)malloc(80);
	assert(d);
	*(d + 1) = 19;
	free(d);
	d = NULL;
	return 0;
}