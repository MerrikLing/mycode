#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
int myStrcmp(char* a, char* b)
{
	assert(a && b);
	while (*a++ == *b++ && *(a - 1) != '\0')//���� *(a - 1) != '\0'���
		;                             //��ȵ��������,�����ƺ�����ѭ����
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
		printf("���");
	else 
		printf("<");

	return 0;
}