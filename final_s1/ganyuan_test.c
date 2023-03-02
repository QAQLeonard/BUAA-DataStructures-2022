#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

char *RANGE[8]= {"caster","medic","supporter","specialist","vanguard","guard","defender","sniper"};

typedef struct SERVENT
{
	int ID;
	char name[60];
	int range;
	int level;
	bool flag;
} servent;

int Range_Compare(const void *elem1,const void *elem2)
{
	servent *stu1 = (servent *)elem1;
	servent *stu2 = (servent *)elem2;
	if((*stu1).range>(*stu2).range) return -1;
	else if((*stu1).range<(*stu2).range) return 1;
	else
	{
		if((*stu1).ID<(*stu2).ID) return -1;
		else return 1;
	}
}

int Level_Compare(const void *elem1,const void *elem2)
{
	servent *stu1 = (servent *)elem1;
	servent *stu2 = (servent *)elem2;
	if((*stu1).level>(*stu2).level) return 1;
	else if((*stu1).level<(*stu2).level) return -1;
	else
	{
		if((*stu1).ID<(*stu2).ID) return -1;
		else return 1;
	}
}

int ID_Compare(const void *elem1,const void *elem2)
{
	servent *stu1 = (servent *)elem1;
	servent *stu2 = (servent *)elem2;
	if((*stu1).ID<(*stu2).ID) return -1;
	else return 1;
}
servent ser[2000];
int ans[2000];

int main()
{
	int n,m;
	FILE *fp;
	fp = fopen("out.out", "w");
	scanf("%d %d",&n,&m);
	int need_n,need_r,max,min;
	

	char temp[20];

	for(int i=0; i<n; i++)
	{
		ser[i].range=-1;
		scanf("%d %s %s %d",&ser[i].ID,ser[i].name,temp,&ser[i].level);
		ser[i].flag=false;
		for(int j=0; j<8; j++)
		{
			if(strcmp(temp,RANGE[j])==0)
			{
				ser[i].range=j;
				break;
			}
		}
	}
	qsort(ser,n,sizeof(servent),Level_Compare);
	for(int i=0; i<n; i++)
	{
		fprintf(fp,"%d %s %s %d\n",ser[i].ID,ser[i].name,RANGE[ser[i].range],ser[i].level);
	}
	//printf("\n\n");
	qsort(ser,n,sizeof(servent),Range_Compare);
	for(int i=0; i<n; i++)
	{
		fprintf(fp,"%d %s %s %d\n",ser[i].ID,ser[i].name,RANGE[ser[i].range],ser[i].level);
	}
	//printf("\n\n");
	qsort(ser,n,sizeof(servent),ID_Compare);
	
	
	for(int i=0;i<m;i++)
	{
		scanf("%d %s %d %d",&need_n,temp,&min,&max);
		
		for(int j=0; j<8; j++)
		{
			if(strcmp(temp,RANGE[j])==0)
			{
				need_r=j;
				break;
			}
		}
		//printf("%d %d %d %d\n",need_n,need_r,min,max);
		int sum=0;
		memset(ans,0,sizeof(ans));
		
		for(int j=0;j<n&&sum<need_n;j++)//Ñ°ÕÒ¸ÉÔ±
		{
			if(ser[j].range==need_r&&ser[j].level>=min&&ser[j].level<=max&&!ser[j].flag)
			{
				printf("%d|| %d %s %s %d\n",j,ser[j].ID,ser[j].name,RANGE[ser[j].range],ser[j].level);
				ans[sum]=j;
				sum++;
			}
		}
		
		if(sum==need_n)
		{
			for(int j=0;j<sum-1;j++)
			{
				fprintf(fp,"%d ",ser[ans[j]].ID);
				ser[ans[j]].flag=true;
			}
			fprintf(fp,"%d\n",ser[ans[sum-1]].ID);
			ser[ans[sum-1]].flag=true;
		}
		else fprintf(fp,"DAMEDANE\n");
	}






	return 0;
}
