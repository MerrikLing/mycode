#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
int my_strlen(const char* p)
{
	assert(p);//�ж��Ƿ�Ϊ��ָ��
	char* start = p;
	while (*p != '\0')
		p++;
	return p - start;

}
int main()
{
	//int a = my_strlen(NULL);
	int a=my_strlen("ahhh!");
	printf("%d", a);
	return 0;
}