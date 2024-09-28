#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
struct stu
{
	char name[20];
	int money;
};
int cmp(const void* e1, const void* e2)
{
	return *(int*)e1 - *(int*)e2;
}
int m_cmp(const void* e1, const void* e2)
{
	return (((struct stu*)e1)->money) - ((struct stu*)e2)->money;
}
int main()
{
	int a[10] = { 6,5,3,2,8,9,7,1,0,4 };
	int sz = sizeof(a) / sizeof(a[0]);
	qsort(a, sz, sizeof(a[0]), cmp);
	int i = 0;
	for (i = 0;i < sz;i++)
		printf("%d ", a[i]);
	
	printf("\n");
	struct stu s[] = { {"张三",250},{"李四",1000} ,{"王五",20} };
	int sz_s = sizeof(s) / sizeof(s[0]);
	qsort(s, sz_s, sizeof(s[0]), m_cmp);
	for (int j = 0;j < sz_s;j++)
		printf("%s %d  ", s[j].name, s[j].money);

	return 0;
}