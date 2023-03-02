#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MIN(a,b) (a<b?a:b)

typedef struct AStudent
{
	int ID;
	char name[30];
	int seat_id;
} Student;

void read_in(FILE *fin,int num,Student student[],int *max)
{
	for(int i=0; i<num; i++)
	{
		fscanf(fin,"%d",&(student[i].ID));
		fscanf(fin,"%s",student[i].name);
		fscanf(fin,"%d",&(student[i].seat_id));
		if(student[i].seat_id>*max) *max=student[i].seat_id;
	}
}

int Seat_id_Compare(const void *elem1,const void *elem2)
{
	Student *stu1 = (Student *)elem1;
	Student *stu2 = (Student *)elem2;
	if(stu1->seat_id==stu2->seat_id) return stu1->ID-stu2->ID;
	else return stu1->seat_id-stu2->seat_id;
}

int ID_Compare(const void *elem1,const void *elem2)
{
	Student *stu1 = (Student *)elem1;
	Student *stu2 = (Student *)elem2;
	return stu1->ID-stu2->ID;
}

void check_omission(int num,Student student[],int *max)
{
	int Q=MIN(*max,num);
	int head=0,tail=num-1;
	int temp=0;
	while(temp<Q&&head<=tail)
	{
		while(head<=tail&&student[head].seat_id-temp>1&&temp<Q)
		{
			student[tail--].seat_id=++temp;
			*max=student[tail].seat_id;
		}
		temp=student[head++].seat_id;
	}
}

void check_repeat(int num,Student student[],int *max)
{
	int top=0;
	int temp=0;
	while(top<num)
	{
		if(student[top].seat_id-temp==0)
		{
			student[top++].seat_id=++*max;
		}
		else
		{
			temp=student[top].seat_id;
			top++;
		}
	}
}

void test_print(Student student[],int num)
{
	for(int i=0; i<num; i++)
	{
		printf("%d %s %d\n",student[i].ID,student[i].name,student[i].seat_id);
	}
}

int main()
{
	FILE *fin,*fp;
	fin=fopen("in.txt","r");
	fp=fopen("out.txt","w");
	int num=0;
	int max=0;
	scanf("%d",&num);
	Student student[num];
	
	read_in(fin,num,student,&max);

	qsort(student,num,sizeof(Student),Seat_id_Compare);

	check_omission(num,student,&max);
	
	qsort(student,num,sizeof(Student),Seat_id_Compare);
	
	//test_print(student,num);
	
	check_repeat(num,student,&max);
	
	qsort(student,num,sizeof(Student),ID_Compare);
	
	//test_print(student,num);

	for(int i=0; i<num; i++)
	{
		fprintf(fp,"%d %s %d\n",student[i].ID,student[i].name,student[i].seat_id);
	}
	return 0;
}
