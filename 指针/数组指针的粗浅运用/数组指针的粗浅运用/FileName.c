#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void print(int(*p)[5])//��ά�����׵�ַ�ǵ����еĵ�ַ���������ַ
{
	int i = 0;
	int j = 0;
	for (i = 0;i < 3;i++)
	{
		for (j = 0;j < 5;j++)
			//printf("%d ", p[i][j]);
			//��һ�ַ���
			printf("%d ", *(*(p + i) + j));//p+i��ʾ��i�е�ַ��*���ʾĳ��������
		printf("\n");
	}

}
int main()
{
	int a[3][5] = { 1,2,3,4,5,6,7,8,9,10 };
	int(*p)[5] = a;
	print(a);
	//printf("%p ", p);
	//printf("%p", p+1);
	return 0;
}