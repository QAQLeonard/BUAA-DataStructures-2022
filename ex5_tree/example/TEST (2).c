#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node
{
	char s[55];
	int count;
	struct node* lchild;
	struct node* rchild;
};
struct node tree[100005],*T=NULL,*p=NULL,*q=NULL;
char c,x[55];
void creatBT()
{
	p=(struct node*)malloc(sizeof(struct node));
	p->lchild=p->rchild=NULL;
	strcpy(p->s,x);
	if(T==NULL)
	{
		T=p;
		p->count=1;
	}
	else
	{
		q=T;
		while(1)
		{
			if(strcmp(x,q->s)<0)
			{
				if(q->lchild!=NULL)	q=q->lchild;
				else
				{
					q->lchild=p;
					p->count=1;
					break;
				}
			}
			else if(strcmp(x,q->s)>0)
			{
				if(q->rchild!=NULL)	q=q->rchild;
				else
				{
					q->rchild=p;
					p->count=1;
					break;
				}
			}
			else
			{
				q->count++;
				break;
			}	
		}
	} 
}
void inorder(struct node *T)
{
	p=T;
	struct node *stack[10005];
	int top=-1;
	while(p!=NULL||top!=-1)
	{
		while(p!=NULL)
		{
			stack[++top]=p;
			p=p->lchild;
		}
		p=stack[top--];
		printf("%s %d\n", p->s, p->count);
		p=p->rchild;
	}
	return ;
//	if(T!=NULL)
//	{
//		inorder(T->lchild);
//		printf("%s %d\n", T->s, T->count);
//		inorder(T->rchild);
//	}
}
int main()
{
	FILE *fin;
	int i,j=0;
	fin=fopen("article.txt", "r");
	while((c=fgetc(fin))!=EOF)	
	{
		if(tolower(c)<'a'||tolower(c)>'z')
		{
			x[j]='\0';
			if(j!=0)
				creatBT();
			j=0;
			memset(x,'\0',sizeof(x));
		}
		else
			x[j++]=tolower(c);
	}
	if(T!=NULL)	printf("%s", T->s);
	if(T->rchild!=NULL)	printf(" %s", T->rchild->s);
	if(T->rchild->rchild!=NULL)	printf(" %s", T->rchild->rchild->s);
	printf("\n");
	inorder(T);
	return 0;
} 

