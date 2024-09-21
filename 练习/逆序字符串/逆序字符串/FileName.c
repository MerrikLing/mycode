#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//比如有一个数组中元素分别为abc，要求把它们变成cba放入数组中，不是逆序打印
//void reverse(char* arr)
//{
//	int i = 0;
//	for (i = 0;i < 2;i++)
//	{
//		char c = *(arr + i);
//		*(arr + i) = *(arr+4-i);
//		*(arr + 4 - i) = c;
//	}
//}
//还可以用递归的方式实现
void reverse(char* arr)
{
	int i = strlen(arr);
	char c = *(arr);
	*(arr) = *(arr + i - 1);
	*(arr + i - 1) = '\0';
	if (i > 1)
	//if (strlen(arr+1) > 1)
		reverse(arr + 1);
	*(arr + i - 1) = c;
}
int main()
{
	char arr[] = { "abcde" };
	int i = 0;
	reverse(arr);
	for (i = 0;i < 5;i++)
		printf("%c ", arr[i]);
	return 0;
}