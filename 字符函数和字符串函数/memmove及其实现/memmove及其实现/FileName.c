#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
//memmove�����ƶ������ص����ڴ��
void* my_memmove(void* d, const void* s, int n)
{
	assert(d && s);
	void* r = d;
	//˼·�����s��dǰ�棬���ſ�������s��d���棬���ſ���
	if ((char*)d< (char*)s)
	{
		while(n--)
		{
			*(char*)d = *(char*)s;
			d = (char*)d + 1;
			s = (char*)s + 1;
		}
	}
	else
	{
		//d = (char*)d + n-1;//+n-1 ȷ��d��������һ���ֽڵ�λ��
		//s = (char*)s + n-1;
		//while (n--)
		//{
		//	*(char*)d = *(char*)s;
		//	d = (char*)d - 1;
		//	s = (char*)s - 1;
		//}

		//�Ż�����
		while (n--)
		{
			*((char*)d + n) = *((char*)s + n);
		}
	}

	return r;
}
int main()
{
	int a[] = { 0,2,3,5,6,7,8,9,4 };
	int sz = sizeof(a) / sizeof(a[0]);
	my_memmove(a+2, a, 16);
	for (int i = 0;i < sz;i++)
		printf("%d ", a[i]);
	return 0;
}