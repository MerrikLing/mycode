#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
//memcpy���𿽱���������ռ��е����ݣ��������Ͷ��У������ܿ������������⣩
void* my_memcpy(void* d, const void* s, int n)
{
	assert(d && s);
	void* ret = d;
	for (int i = 0;i < n;i++)
	{//��ò�Ҫд��*((char*)d)++,���еı��������ܲ��ˣ���Ϊ(char*)d�ᱻ���
		//Ϊһ����ʱ������++��û�����壬��dû��Ӱ��
		*(char*)d = *(char*)s;
		d = (char*)d + 1;
		s = (char*)s + 1;
	}
	return ret;
}
int main()
{
	int a[] = { 0,2,3,5,6,7,8,9,4 };
	int b[20] = { 0 };
	int sz = sizeof(a) / sizeof(a[0]);
	my_memcpy(b, a, sizeof(a)-4);
	for (int i = 0;i < sz;i++)
		printf("%d ", b[i]);

	return 0;
}