#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//����int(32λ)����m��n�Ķ����Ʊ���У��ж��ٸ�λ(bit)��ͬ
//���ǲ���
int fun(int m, int n)
{
	if (m < 0)
		m = -m;
	if (n < 0)
		n = -n;
	int i = 0;
	int count = 0;
	//for (i = 0;i < 32;i++)
	//{
	//	if (((m >> i) & 1) != ((n >> i) & 1))
	//	{
	//		count++;
	//	}
	//}

	//��һ��ʵ�ַ�������^
	int x = m ^ n;
	while (x)
	{
		count++;
		x = x & (x - 1);
	}
	return count;
}
int main()
{
	int m = 0;
	int n = 0;
	scanf("%d", &m);
	scanf("%d", &n);
	int a=fun(m, n);
	printf("%d", a);
	return 0;
}