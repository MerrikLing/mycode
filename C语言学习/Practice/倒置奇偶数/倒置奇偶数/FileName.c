#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//����һ���������飬����������λ�ã�ʹ��ȫ��λ������ǰ�벿�֣�ż��ȫλ�ں��
void sort(int a[])
{
	int i = 0;
	int count = 0;
	for(i=0;i<10;i++)
	{
		if (a[i] % 2 != 0)
		{
			int j = a[count];
			a[count++] = a[i];
			a[i] = j;
	    } 
	}
}
int main()
{
	printf("������10�����֣� ");
	int a[10] = { 0 };
	int i = 0;
	for (i = 0;i < 10;i++)
		scanf("%d", &a[i]);
	sort(a);
	for (i = 0;i < 10;i++)
		printf("%d ", a[i]);

	return 0;
}