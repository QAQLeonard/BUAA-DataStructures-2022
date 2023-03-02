#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node
{
	int a;
	int n;
	struct Node *next;
} LinkNode,*LinkList;

void Init_List(LinkList *L)//初始化
{
	(*L)=(LinkNode *)malloc(sizeof(LinkNode));
	(*L)->next=NULL;
}

void Tail_Insert_List(LinkNode *L)//尾插法，n为插入的个数
{
	int data1,data2;
	LinkNode *End=L;
	char ch;
	ch=getc(stdin);
	while(ch!='\n')
	{
		scanf("%d %d",&data1,&data2);
		LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
		p->a=data1;
		p->n=data2;
		End->next=p;
		End=p;
		ch=getc(stdin);
	}
	End->next=NULL;
}

LinkList Search_Item(int item,LinkList L)
{
	LinkList temp=L;
	while(temp!=NULL&&(temp->n)!=item)
	{
		temp=temp->next;
	}
	return temp;
}

void test_print(LinkList L)
{
	LinkList temp=L;
	while(temp->next!=NULL)
	{
		printf("%d %d ",temp->a,temp->n);
		temp=temp->next;
	}
	printf("%d %d\n",temp->a,temp->n);
}

void Listsort(LinkNode *head,int num)
{
	int i = 0;
	int j = 0;
	LinkNode *L=head;
	LinkNode *p;
	LinkNode *p1;

	for(i=0;i<num-1;i++)
	{
		L=head;
		for (j=0;j<num-i-1;j++)
		{
			p=L;
			p1=L->next;
			if (p->n<=p1->n)
			{
				int temp1=p->n;
				int temp2=p->a;
				p->n=p1->n;
				p->a=p1->a;
				p1->n=temp1;
				p1->a=temp2;
			}
			L=L->next;
		}
		L=head;
	}
}

int Get_ListLength(LinkList L)
{
	int ListLength=0;
	LinkNode *p=L->next;
	while(p)
	{
		ListLength++;
		p=p->next;
	}
	return ListLength;
}

int main()
{
	LinkList L1,L2,L3;//初始化并读取
	//int num1=0,num2=0;
	Init_List(&L1);
	Init_List(&L2);
	Init_List(&L3);
	scanf("%d %d",&L1->a,&L1->n);
	Tail_Insert_List(L1);
	//printf("L1 read successful\n");
	scanf("%d %d",&L2->a,&L2->n);
	Tail_Insert_List(L2);
	//printf("L2 read successful\n");
	L3->a=0;
	L3->n=0;

	LinkList temp1=L1,temp2=L2;
	LinkNode *End=L3;
	LinkList temp3;
	//test_print(L1);
	//test_print(L2);

	while(temp1!=NULL)//乘积
	{
		while(temp2!=NULL)
		{
			temp3=Search_Item((temp1->n)+(temp2->n),L3);
			if(temp3==NULL)
			{
				LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
				p->n=(temp1->n)+(temp2->n);
				p->a=(temp1->a)*(temp2->a);
				End->next=p;
				End=p;
				End->next=NULL;
			}
			else
			{
				temp3->a+=(temp1->a)*(temp2->a);
			}
			temp2=temp2->next;
			//test_print(L3);
		}
		temp2=L2;
		temp1=temp1->next;

	}
	//End->next=NULL;
	Listsort(L3,Get_ListLength(L3)+1);
	temp3=L3;
	while(temp3->next!=NULL)
	{
		if(temp3->a!=0) printf("%d %d ",temp3->a,temp3->n);
		temp3=temp3->next;
	}
	if(temp3->a!=0) printf("%d %d\n",temp3->a,temp3->n);
	return 0;
}
