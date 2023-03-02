#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node
{
	int code;
	struct Node *next;
} LinkNode,*LinkList;

void Init_List(LinkList *L)//初始化
{
	(*L)=(LinkNode *)malloc(sizeof(LinkNode));
	(*L)->next=NULL;
}

void Tail_Insert_List(LinkNode *L,int n)//尾插法，n为插入的个数
{
	int data=1;
	LinkNode *End=L;

	while(n>0)
	{
		data++;
		LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
		p->code=data;
		End->next=p;
		End=p;
		n--;
	}
	End->next=L;
}

LinkList Search_Item(int item,LinkList L)
{
	LinkNode *temp;
	temp=L;
	while(temp->code!=item) 
	{
		temp=temp->next;
	}
	return temp;
}

int main()
{
	int n,m,q;
	scanf("%d %d %d",&n,&m,&q);
	LinkList L;
	Init_List(&L);
	L->code=1;
	Tail_Insert_List(L,n-1);
	LinkList temp=Search_Item(q,L);
	//printf("%d",temp->code);
	while(n>1)
	{
		for(int i=1; i<m-1; i++)
		{
			temp=temp->next;
		}
		temp->next=temp->next->next;
		temp=temp->next;
		n--;
	}
	printf("%d",temp->code);
	return 0;
}
