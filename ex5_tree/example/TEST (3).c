#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char stack1[1005],stack2[1005],hold[1005],s[1005];
int top1=-1,top2=-1,top3=-1,top=-1,ans[1005];
struct node
{
	int num;
	char op;
	struct node *lchild,*rchild;
};
struct node *T=NULL, *p=NULL, *q=NULL, *r=NULL, tree[1005], *stack3[1005];
int judge(char x,char y)
{
	if(x==')')
	{
		while(stack2[top2]!='(')
			stack1[++top1]=stack2[top2--];
		top2--;
	}
	else if(x=='+'||x=='-')
	{
		if(y!='(')
		{
			stack1[++top1]=stack2[top2--];
			stack2[++top2]=x;
		}
		else
			stack2[++top2]=x;
	}
	else if(x=='*'||x=='/')
	{
		if(y=='*'||y=='/')
		{
			stack1[++top1]=stack2[top2--];
			stack2[++top2]=x;
		}
		else if(y=='+'||y=='-'||y=='(')
			stack2[++top2]=x;
	}
}
void maths(char op)
{
	int a,b;
	b=ans[top--];
	a=ans[top--];
	switch(op)
	{
		case '+': 
				ans[++top]=a+b;
				break;
		case '-': 
				ans[++top]=a-b;
				break;
		case '*': 
				ans[++top]=a*b;
				break;
		case '/': 
				ans[++top]=a/b;
				break;
	}
	return;
}
void outorder(struct node*T)
{
	if(T!=NULL)
	{
		outorder(T->lchild);
		outorder(T->rchild);
		if(T->op=='\0')
			ans[++top]=T->num;
		else
			maths(T->op);
	}
	return;
}
int main()
{
	int i,j,l,temp=0;
	gets(hold);
	for(i=0;i<strlen(hold);i++)
	{
		if(hold[i]=='=')
		{
			if(hold[i-1]>='0'&&hold[i-1]<='9')	
				stack1[++top1]=' ';
			while(top2>-1)	
				stack1[++top1]=stack2[top2--];
			break;
		}
		else if(hold[i]==' ')
		{
			if(hold[i-1]>='0'&&hold[i-1]<='9')
				stack1[++top1]=' ';
			else
				continue;
		}
		else if(hold[i]>='0'&&hold[i]<='9')
			stack1[++top1]=hold[i];
		else
		{
			if(hold[i-1]>='0'&&hold[i-1]<='9')
				stack1[++top1]=' ';
			if(top2==-1)	stack2[++top2]=hold[i];
			else if(hold[i]=='(')
				stack2[++top2]=hold[i];
			else
				judge(hold[i],stack2[top2]);
		}
	}
	for(i=0;i<=top1;i++)
	{
//		printf("%c", stack1[i]);
		if(stack1[i]==' ')
		{
			p=(struct node*)malloc(sizeof(struct node));
			p->lchild=p->rchild=NULL;
			p->op='\0';
			p->num=temp;
			temp=0;
			stack3[++top3]=p;
		}
		else if(stack1[i]>='0'&&stack1[i]<='9')
			temp=temp*10+stack1[i]-'0';
		else
		{
			temp=0;
			p=(struct node*)malloc(sizeof(struct node));
			p->lchild=p->rchild=NULL;
			p->op=stack1[i];
			p->rchild=stack3[top3--];
			p->lchild=stack3[top3--];
			stack3[++top3]=p;
		}
	}
	T=stack3[top3--];
	if(T!=NULL)	printf("%c", T->op);
	if(T->lchild!=NULL)
	{
		if(T->lchild->op=='\0')	printf(" %d", T->lchild->num);
		else	printf(" %c", T->lchild->op);
	}
	if(T->rchild!=NULL)
	{
		if(T->rchild->op=='\0')	printf(" %d", T->rchild->num);
		else	printf(" %c", T->rchild->op);
	}
	outorder(T);
	printf("\n%d", ans[top]);
	return 0;
}

