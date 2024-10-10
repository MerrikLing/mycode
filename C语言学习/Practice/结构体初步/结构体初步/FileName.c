#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//just for fun
struct suc
{
	char m[20];
	char status[20];
	int car;
};
void print(struct suc*p)
{
	printf("%s %d %s", p->m, p->car, p->status);
}
int main()
{
	struct suc s = { "1000w","CEO",7 };
	print(&s);
	return 0;
}