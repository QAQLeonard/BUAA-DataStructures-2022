#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NHASH  3001
#define MULT  37
unsigned int hash(char *str)
{   
	unsigned int h=0;
    char *p;
    for(p=str; *p!='\0'; p++)
        h = MULT*h + *p;
    return h % NHASH;
}
char dic[3505][25],s[25];
struct node
{
	char x[25];
	struct node *next;	
};
int main()
{
	FILE *fin;
	int i,op,count;
	fin=fopen("dictionary3000.txt","r");
	for(count=0;;count++)
	{
		if(fscanf(fin,"%s",dic[count])==EOF)
			break; 
	}
	while(scanf("%s %d", s, &op)!=EOF)
	{
		if(op==1)
		{
			for(i=0;i<count;i++)
			{
				if(strcmp(s,dic[i])<=0)
					break;
			}
			if(i<count&&strcmp(s,dic[i])==0)
				printf("1 %d\n", i+1);
			else
				printf("0 %d\n", i+1);
		}
		else if(op==2)
		{
			int low=0,high=count-1,mid,flag=0,ans=0;
			while(low<=high)
			{
				mid=(low+high)/2;
				ans++;
				if(strcmp(s,dic[mid])==0)
				{
					flag=1;
					break;
				}
				else if(strcmp(s,dic[mid])<0)	high=mid-1;
				else	low=mid+1;
			}
			printf("%d %d\n", flag, ans);
		}
		else if(op==3)
		{
			int j,ans=0,low,high,mid,flag=0;
			int search[26][2]={0};
			for(i=0,j=0;i<=count;i++)
			{
				if(dic[i][0]-'a'==j)
					search[dic[i][0]-'a'][1]=i;
				else
				{
					search[dic[i][0]-'a'][0]=i;
					j=dic[i][0]-'a'; 
				} 
			}
//			for(i=0;i<=25;i++)
//				printf("%c %d %d\n", 'a'+i, search[i][0], search[i][1]);
			low=search[s[0]-'a'][0],high=search[s[0]-'a'][1];
			if(low==high)	printf("0 0\n"); 
			else
			{
				while(high>=low)
				{
					ans++;
					mid=(low+high)/2;
					if(strcmp(s,dic[mid])==0)
					{
						printf("1 %d\n", ans);
						flag=1;
						break;
					}
					else if(strcmp(s,dic[mid])<0)
						high=mid-1;
					else 
						low=mid+1; 
				}
				if(flag==0)
					printf("0 %d\n", ans);
			}
		}
		else
		{
			struct node* Hash[3505]={NULL},*p=NULL,*q=NULL;
			int ans=0,j,flag=0;
			for(i=0;i<=count;i++)
			{
				j=hash(dic[i]);
				p=(struct node*)malloc(sizeof(struct node));
				strcpy(p->x,dic[i]);
				p->next=NULL;
				if(Hash[j]==NULL)	Hash[j]=p;
				else
				{
					q=Hash[j];
					while(q->next!=NULL)	q=q->next;
					q->next=p;
				}
			}
			j=hash(s);
			p=Hash[j];
			while(p!=NULL&&strcmp(s,p->x)>=0)
			{
				ans++;
				if(strcmp(s,p->x)==0)
				{
					flag=1;
					break;
				}
				p=p->next;
			}
			printf("%d %d\n", flag, ans);
		}
	}
	return 0;
} 

