#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int  a = -5;
	int  i = 0;
	int  n = 0;
	//也可用不断除2，模2来实现。但有局限性，负数不行，优化方法
	//强行转换为无符号类



	//for (i =0 ;i < 32;i++)
	//{
	//	if (a & 1 == 1)
	//		n++;
	//	a=a >> 1;
	//}
	//上面的方法必须循坏32次，优化如下
	while (a)
	{
		n++;
		//a=a& (a - 1);
		a  &= (a - 1);
	}//每执行一次，最右边的1就变为0
	printf("%d", n);
	return 0;
}