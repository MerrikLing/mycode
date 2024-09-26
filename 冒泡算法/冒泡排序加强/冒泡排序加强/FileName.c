#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
struct stu
{
	char name[20];
	int money;
};
int cmp_str(const void* e1, const void* e2)
{
	while (((*((char*)e1)++) - (*((char*)e2)++)) != 0)
		return (*((char*)e1)-1) - (*((char*)e2)-1);
}

int cmp_int(const void* e1, const void* e2)
{
	return *(int*)e1- *(int*)e2;
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
		for (j = 0;j < num - 1 - i;j++)
		{
			if (cmp((char*)p + j * width, (char*)p +(j+1)*width) >0)
			{
				swap((char*)p + j * width, (char*)p + (j + 1) * width,width);
			}

		}
	}
}
int main()
{
	int a[] = { 12,6,81,4,5,3,8,9,2,49,7,0,1,19 };
	int sz = sizeof(a) / sizeof(a[0]);
	printf("test one: \n");
	sort(a,sz,sizeof(a[0]), cmp_int);
	for (int i = 0;i < sz;i++)
		printf("%d ", a[i]);

	printf("\n\ntest two: \n");
	struct stu s[] = { {"Ken",10},{"Monkey",20} ,{"Ann",250} };
	int sz_s = sizeof(s) / sizeof(s[0]);
	//我的sort存在问题，对结构体不能正常起作用
	//具体来说，s[]中的 第三个结构体 总是会和 第二个结构体 换位置
	//cmp_str？  待测
	sort(s, sz_s, sizeof(s[0]), cmp_int);
	for (int j = 0;j < sz_s;j++)
		printf("%s %d  ", s[j].name, s[j].money);
	printf("\n");
	return 0;
}