#include<stdio.h>
#include<string.h>
struct node
{
	int id,type,parent,father;
	int num[8];
	int length,flag;
};
struct node tree[1000005];
int queue[1005],ans[1005],flag1=0,min=1000,print;
void frontorder(int r)
{
	int i;
	if(r>=0)
	{
		if(tree[r].type==2&&tree[r].length==min&&flag1==0)
		{
			printf("%d ", r);
			flag1=1;
			print=r;
		}
		for(i=0;i<=7;i++)
			frontorder(tree[r].num[i]);
	}
}
int main()
{
	int n,i,target,head=-1,tail=-1,temp;
	int id,type,parent,num;
	FILE *fin;
	fin=fopen("in.txt", "r");
	scanf("%d %d", &n, &target);
	while(fscanf(fin,"%d %d %d %d", &id, &type, &parent, &num)!=EOF)
	{
		memset(tree[id].num,-1,sizeof(tree[id].num));
		tree[id].id=id,tree[id].type=type,tree[id].parent=parent;
		tree[id].length=0,tree[id].flag=0;
		tree[parent].num[num]=id;
	}
	queue[++tail]=target,tree[target].flag=1;
	while(head<=tail)
	{
		temp=queue[++head];
		if(tree[temp].type==2&&tree[temp].length<min)	
			min=tree[temp].length; 
		else if(tree[temp].type==1)
		{
			if(tree[tree[temp].parent].flag==0)
			{
				queue[++tail]=tree[temp].parent;
				tree[tree[temp].parent].flag=1;
				tree[tree[temp].parent].father=temp;
				tree[tree[temp].parent].length=tree[temp].length+1;
			}
		}
		else if(tree[temp].type==0)
		{
			if(tree[tree[temp].parent].flag==0)
			{
				queue[++tail]=tree[temp].parent;
				tree[tree[temp].parent].length=tree[temp].length+1;
				tree[tree[temp].parent].father=temp;
				tree[tree[temp].parent].flag=1;
			}
			for(i=0;i<=7;i++)
				if(tree[temp].num[i]>=0&&tree[tree[temp].num[i]].flag==0)	
				{
					queue[++tail]=tree[temp].num[i];
					tree[queue[tail]].length=tree[temp].length+1;
					tree[queue[tail]].father=temp;
					tree[tree[temp].num[i]].flag=1;
				}
		}
	}
	frontorder(0);
	for(i=-1;print!=target;print=tree[print].father)
		ans[++i]=tree[print].father;
	for(i--;i>=0;i--)
		printf("%d ", ans[i]);
	return 0;
}


