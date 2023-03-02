#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	int depth;
	struct node *lchild;
	struct node *rchild;
};
struct node tree[10005];
struct node *T=NULL, *p=NULL, *q=NULL;
void creatBT(int num, int count)
{
	p=(struct node*)malloc(sizeof(struct node));
	p->lchild=NULL,p->rchild=NULL;
	p->data=num;
	if(T==NULL)
	{
		T=p;
		T->depth=1;
	}
	else
	{
		q=T;
		while(1)
		{
			if(num<q->data)
			{
				if(q->lchild!=NULL)
				{
					q=q->lchild;
					count++;
				}
				else
				{
					q->lchild=p;
					p->depth=count+1;
					break;
				}
			}
			else if(num>=q->data)
			{
				if(q->rchild!=NULL)
				{
					q=q->rchild;
					count++;
				}
				else
				{
					q->rchild=p;
					p->depth=count+1;
					break;
				}
			}
		}
	}
}
void inorder(struct node* T)
{
	if(T!=NULL)
	{
		inorder(T->lchild);
		if(T->lchild==NULL&&T->rchild==NULL)
			printf("%d %d\n", T->data, T->depth); 
		inorder(T->rchild);
	}
}
int a[10005];
int main()
{
	int i,n,count,num,head,tail;
	scanf("%d", &n);
	for(i=1;i<=n;i++)	
	{
		scanf("%d", &num);
		count=1;
		creatBT(num,count);
	}
	inorder(T);
	return 0;
} 

