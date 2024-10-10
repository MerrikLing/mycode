#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<assert.h>
//memmove用于移动存在重叠的内存块
void* my_memmove(void* d, const void* s, int n)
{
	assert(d && s);
	void* r = d;
	//思路，如果s在d前面，则倒着拷贝；若s在d后面，正着拷贝
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
		//d = (char*)d + n-1;//+n-1 确保d变成了最后一个字节的位置
		//s = (char*)s + n-1;
		//while (n--)
		//{
		//	*(char*)d = *(char*)s;
		//	d = (char*)d - 1;
		//	s = (char*)s - 1;
		//}

		//优化方案
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