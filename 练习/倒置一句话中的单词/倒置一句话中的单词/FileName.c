#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//��㲻����
int main()
{
	char a[101] = { 0 };
	char b[101] = { 0 };
	//scanf�����ո�Ҫͣ�£�
	gets(a);
	int i = 0;
	int c = 0;
	for (i = 100;i >= 0;i--)
	{
		if (a[i] == 0)
			continue;
		if (a[i] != ' ')
		{
			b[c] = a[i];
			c++;
		}
		if (a[i] == ' '||i==0)
		{
			c--;
			do
			{
				printf("%c", b[c]);
				b[c] = 0;
				c--;
			} 
			while (c!=-1);
			c = 0;
			printf(" ");
		}
	}
	return 0;
}