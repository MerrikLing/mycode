#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
int main()
{
	FILE* p = fopen("t.txt", "r");//注意反斜杠！
	if(p==NULL)
	{
		perror("fopen");
		return 1;
	}
	//操作……
	fprintf(p, "Hello World,waiting for my coming!");
	char a[100];
	//注意：不能同时读或者写，使用r则fprintf无效，vice versa
	fgets(a,100,p);
	printf("%s", a);
	//关闭
	fclose(p);
	p = NULL;
	return 0;
}