#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//С����ϲ�����֣�����ϲ��0��1�������ڵõ���һ���������ÿλ�������0��1��
//���ĳһλ���������Ͱ������1�������ż������ô�Ͱ������0������ش�����
//��õ������Ƕ��١�
//int main()
//{
//	int a;
//	int i = -1;
//	int n[9] = {0};
//	scanf("%d", &a);
//	while (a)
//	{
//		i++;
//		n[i] = a % 2;
//		a /= 10;
//	}
//	while (i>-1)
//	{
//		printf("%d", n[i--]);
//	}
//	return 0;
//}
//
//
////��ӡ���пո��*��ɵ�ֱ��������
//int main()
//{
//	int a;
//	scanf("%d", &a);
//	for (int i = 0;i < a;i++)
//	{
//		for (int j = 0;j < a - 1 - i;j++)
//			printf("  ");
//		for (int j = 0;j <= i;j++)
//			printf("* ");
//		printf("\n");
//
//	}
//	return 0;
//}


//ʵ��һ���ܱ��ַ������ָ��������Ԫ�ط����ַ������ߵĺ���
void f(int i, char*a,int s)
{
	//˼·:�����������
	i %= s;
	while (i--)
	{
		for (int j = 0;j < s-1;j++)
		{
			char t = *(a + 1+j);
			*(a + 1 + j) = *(a+j);
			*(a + j) = t;
		}

	}
}
//�״��ַ���ĩβ��\0
int main()
{
	char a[] = "abcdef";
	int i = 0;
	int s=strlen(a);
	scanf("%d", &i,s);
	f(i,a,s);
	printf("%s\n", a);
	return 0;
}