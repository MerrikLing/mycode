#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
int myStrcmp(char* a, char* b)
{
	assert(a && b);
	while (*a++ == *b++ && *(a - 1) != '\0')//加入 *(a - 1) != '\0'解决
		;                             //相等的特殊情况,否则似乎会死循环！
	return *(a - 1) - *(b - 1);
}
int main()
{
	char a[] = "abcd";
	char b[] = "abcd";
	int r = myStrcmp(a, b);
	if (r > 0)
		printf(">");
	else if(r==0)
		printf("相等");
	else 
		printf("<");

	return 0;
}