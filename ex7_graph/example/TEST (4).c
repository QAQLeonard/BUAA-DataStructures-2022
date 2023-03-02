#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct STATION
{
	char name[20];
	int transition;
}STATION;
typedef struct Bian
{
	int weight;
	int linenum;
}Bian;
STATION station[512];
Bian bian[512][512];
int count=0,dis[512],book[512],ans[512],route[512];
void initmap();
int add(struct STATION temp);
int main()
{
	initmap();
	char Begin[20],End[20];
	int begin,end,i,j;
	gets(Begin);
	gets(End);
	for(i=1;i<=count;i++)
	{
		if(strcmp(Begin,station[i].name)==0)
			begin=i;
		if(strcmp(End,station[i].name)==0)
			end=i;
	}
	for(i=1;i<=count;i++)
		dis[i]=99999;
	for(i=1;i<=count;i++)
		if(bian[begin][i].weight!=0)
			dis[i]=bian[begin][i].weight;
	book[begin]=1;
	for(i=1;i<=count-1;i++)
	{
		int min=99999,temp;
		for(j=1;j<=count;j++)
		{
			if(dis[j]<min&&book[j]==0)
			{
				min=dis[j];
				temp=j;
			}
		}
		book[temp]=1,dis[temp]=min;
		if(route[temp]==0)	route[temp]=begin;
		for(j=1;j<=count;j++)
		{
			if(dis[j]>dis[temp]+bian[temp][j].weight&&bian[temp][j].weight!=0)
			{
				dis[j]=dis[temp]+bian[temp][j].weight;
				route[j]=temp;
			}
		}
	}
	j=end;
	int top=-1,cnt=1,pre=begin,now;
	while(j!=begin)
	{
		ans[++top]=j;
		j=route[j];
	}
	printf("%s", station[begin].name);
	while(top!=-1)
	{
		now=ans[top--];
		if(bian[pre][now].linenum==bian[now][ans[top]].linenum)
			cnt++;
		else
		{
			printf("-%d(%d)-%s", bian[pre][now].linenum, cnt, station[now].name);
			cnt=1;
		}
		pre=now;
	}
	return 0;
} 
void initmap()
{
	FILE *fin;
	fin=fopen("bgstations.txt","r");
	int sum,i,j,line,num,v1,v2;
	STATION st;
	fscanf(fin,"%d", &sum);
	for(i=1;i<=sum;i++)
	{
		fscanf(fin,"%d%d", &line, &num);
		v1=v2=-1;
		for(j=1;j<=num;j++)
		{
			fscanf(fin,"%s %d", st.name, &st.transition);
			v2=add(st);
			if(v1!=-1)
			{
				bian[v1][v2].weight=bian[v2][v1].weight=1;
				bian[v1][v2].linenum=bian[v2][v1].linenum=line;
			}
			v1=v2;
		}
	}
	fclose(fin);
}
int add(struct STATION temp)
{
	if(temp.transition==0)
	{
		station[++count].transition=temp.transition;
		strcpy(station[count].name,temp.name);
		return count;
	}
	else
	{
		int i=1;
		for(i=1;i<=count;i++)
		{
			if(strcmp(station[i].name,temp.name)==0)
				return i;
		}
		station[++count].transition=temp.transition;
		strcpy(station[count].name,temp.name);
		return count;
	}
}

