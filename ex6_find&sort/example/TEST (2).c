#include<stdio.h>
#include<string.h>
#include<ctype.h>
struct list
{
	int id,seat;
	char name[30];
};
struct list student[105];
int cmp1(const void *a, const void *b)
{
	struct list s1,s2;
	s1=*(struct list*)a,s2=*(struct list*)b;
	if(s1.seat!=s2.seat)
		return s1.seat-s2.seat;
	else
		return s1.id-s2.id;
}
int cmp2(const void *a, const void *b)
{
	struct list s1,s2;
	s1=*(struct list*)a,s2=*(struct list*)b;
	if(s1.seat-s2.seat!=0)
		return	s1.seat-s2.seat;
	else
		return s1.id-s2.id;
}
int cmp3(const void *a, const void *b)
{
	struct list s1,s2;
	s1=*(struct list*)a,s2=*(struct list*)b;
	return	s1.id-s2.id;
}
int main()
{
	FILE *fin,*fout;
	fin=fopen("in.txt","r");
	fout=fopen("out.txt","w");
	int n,i,j;
	scanf("%d", &n);
	for(i=0;i<=n-1;i++)
		fscanf(fin,"%d %s %d", &student[i].id, student[i].name, &student[i].seat);
	qsort(student,n,sizeof(student[0]),cmp1);
	int head=0,tail=n-1,Q=student[n-1].seat,count=1;
	if(n<Q)	Q=n;
	for(i=1;i<=Q&&head<=tail;i++)
	{
		if(student[head].seat>i)
		{
			student[tail--].seat=i;
			i++;
		}
		while(student[head].seat<=i&&head<=tail)
			head++;
	}
	qsort(student,n,sizeof(student[0]),cmp2);
	Q=student[n-1].seat;
	for(i=1;i<=n-1;i++)
		if(student[i].seat==student[i-1].seat)
			student[i].seat=++Q;
	qsort(student,n,sizeof(student[0]),cmp3);
	for(i=0;i<=n-1;i++)
		fprintf(fout,"%d %s %d\n", student[i].id, student[i].name, student[i].seat);
	fclose(fin);
	fclose(fout);
	return 0;
}


