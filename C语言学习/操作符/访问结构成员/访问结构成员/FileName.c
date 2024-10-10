#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
struct stu
{
	char name[20];
	double scores ;
};
void in_stu(struct stu* s)
{
	strcpy(s->name,"sb");
	s->scores = 3.14;
}
void print(struct stu s)
{
	printf("%s %lf", s.name,s.scores);
}
int main()
{
	struct stu s = { 0 };
	in_stu(&s);
	print(s);

	return 0;
}