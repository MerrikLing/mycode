#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main()
{
	char a[70] = "Hello,my world!I'm coming";
	char A[70];
	strcpy(A, a);
	char token[] = ",!";
	for (char* r = strtok(A, token);r != NULL;r = strtok(NULL, token))
		printf("%s\n", r);
	return 0;
}