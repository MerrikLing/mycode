#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
int main()
{
	FILE* p = fopen("t.txt", "r");//ע�ⷴб�ܣ�
	if(p==NULL)
	{
		perror("fopen");
		return 1;
	}
	//��������
	fprintf(p, "Hello World,waiting for my coming!");
	char a[100];
	//ע�⣺����ͬʱ������д��ʹ��r��fprintf��Ч��vice versa
	fgets(a,100,p);
	printf("%s", a);
	//�ر�
	fclose(p);
	p = NULL;
	return 0;
}