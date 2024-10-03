#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
//memcpy负责拷贝两块独立空间中的数据，任意类型都行，但不能拷贝自身（有问题）
void* my_memcpy(void* d, const void* s, int n)
{
	assert(d && s);
	void* ret = d;
	for (int i = 0;i < n;i++)
	{//最好不要写成*((char*)d)++,在有的编译器下跑不了，因为(char*)d会被理解
		//为一个临时变量，++后没有意义，对d没有影响
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