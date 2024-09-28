#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
struct stu
{
	char name[20];
	int money;
};
int cmp_str(const void* e1, const void* e2)
{
	
		return (*(char*)e1) - (*(char*)e2);
}

int cmp_int(const void* e1, const void* e2)
{
	return *(int*)e1- *(int*)e2;
}
//排列比较结构体中数据的函数和一般的不一样！
int cmp_int_struct(const void* e1, const void* e2)
{
	return ((struct stu*)e1)->money - ((struct stu*)e2)->money;
}

void swap(char*const p1, char* const p2, const int width)
{
	for (int i = 0;i < width;i++)
	{
		char s = *(p2+i);
		*(p2 + i) = *(p1 + i);
		*(p1 + i) = s;
	}
}
void sort(void* p, const int num,const int width,int(* cmp)(const void*e1,const void *e2))
{
	int i,j;
	for(i=0;i< num -1;i++)
	{
		int flag = 1;
		for (j = 0;j < num - 1 - i;j++)
		{
			if (cmp((char*)p + j * width, (char*)p +(j+1)*width) >0)
			{
				swap((char*)p + j * width, (char*)p + (j + 1) * width,width);
				flag = 0;
			}				
		}
		if (flag == 1)
			break;
	}
}
int main()
{
	int a[] = { 12,6,81,4,24,5,3,8,9,2,49,7,0,1,19 };
	int sz = sizeof(a) / sizeof(a[0]);
	printf("test one: \n");
	sort(a,sz,sizeof(a[0]), cmp_int);
	for (int i = 0;i < sz;i++)
		printf("%d ", a[i]);

	printf("\n\ntest two: \n");
	struct stu s[] = { {"Ken",100},{"Monkey",20} ,{"Ann",250} };
	int sz_s = sizeof(s) / sizeof(s[0]);

	////cmp_str？  待测
	sort(s, sz_s, sizeof(s[0]), cmp_int_struct);
	for (int j = 0;j < sz_s;j++)
		printf("%s %d  ", s[j].name, s[j].money);
	printf("\n");

	printf("\n\ntest 3: \n");
	//用一个一维数组不用指针，储存多个字符串，我在写阿瓦隆时实现过，但忘了
	char b[][4] = {"abc","c","bcd","acd"};
	int sz_s2 = sizeof(b) / sizeof(b[0]);
	sort(b, sz_s2, sizeof(b[0]), cmp_str);
	for (int i = 0;i < sz_s2;i++)
		printf("%s  ", b[i]);
	return 0;
}