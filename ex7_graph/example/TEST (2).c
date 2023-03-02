#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct edge
{
	int id,to;
	struct edge *next;
}Elink;
typedef struct ver
{
	int from;
	Elink *link;
}Vlink;
Vlink map[10005];
Elink *head=NULL;
Elink* insert(Elink* head,int id,int v);
void dfs(int k,int n,int step);
int book[10005],ans[10005];
int main()
{
	int n,m,i,id,uu,vv;
	scanf("%d %d", &n, &m);
	for(i=0;i<n;i++)
	{
		map[i].from=i;
		map[i].link=NULL;
	}
	for(i=0;i<m;i++)
	{
		scanf("%d %d %d", &id, &uu, &vv);
		map[uu].link=insert(map[uu].link,id,vv);
		map[vv].link=insert(map[vv].link,id,uu);
	}
	book[0]=1;
	dfs(0,n,0);
	return 0;
}
Elink* insert(Elink* head,int id,int v)
{
	Elink *p=NULL,*q=NULL;
	p=(Elink*)malloc(sizeof(Elink));
	p->id=id,p->next=NULL,p->to=v;
	if(head==NULL)
	{
		head=p;
		return head;
	}
	for(q=head;q->next!=NULL&&q->next->id<id;q=q->next);
	p->next=q->next;
	q->next=p;
	return head;
}
void dfs(int k,int n,int step)
{
	int i;
	Elink *p=map[k].link;
	if(k==n-1)
	{
		for(i=0;i<step;i++)
			printf("%d ",ans[i]);
		printf("\n");
		return;
	}
	while(p!=NULL)
	{
		if(book[p->to]==0)
		{
			ans[step]=p->id;
			book[p->to]=1;
			dfs(p->to,n,step+1);
			book[p->to]=0;
		}
		p=p->next;
	}
	return;
}

