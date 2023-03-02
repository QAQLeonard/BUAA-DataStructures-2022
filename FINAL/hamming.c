#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

char example[20];

typedef struct WORD
{
	char ch[20];
	int length;
} Word;

Word w[20];


int cmp(const void *elem1,const void *elem2)
{
	Word *stu1 = (Word *)elem1;
	Word *stu2 = (Word *)elem2;
	if((*stu1).length-(*stu2).length>0) return -1;
	else if((*stu1).length-(*stu2).length<0) return 1;
	else
	{
		return strcmp(stu1->ch,stu2->ch);
	}
}

int main()
{
	int n=0;
	scanf("%d",&n);
	scanf("%s",example);
	for(int i=0; i<n-1; i++)
	{
		scanf("%s",w[i].ch);
		w[i].length=0;
	}
	//printf("0");
	int length=strlen(example);
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<length; j++)
		{
			if(w[i].ch[j]!=example[j]) w[i].length++;
		}
	}
	qsort(w,n-1,sizeof(Word),cmp);
	for(int i=0;i<n-1;i++)
	{
		printf("%s %s %d\n",example,w[i].ch,w[i].length);
	}
	return 0;
}
