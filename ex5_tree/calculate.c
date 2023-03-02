#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define Number 0
#define Operator 1

typedef struct AELEMENT
{
	union
	{
		int Num;
		char CalCh;
	} NC;
	int flag;
} Element;

typedef struct TreeNode
{
	Element data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
} TreeNode,*Tree;

void Element_print(Element e)
{
	if(e.flag==Number) printf("%d",e.NC.Num);
	else printf("%c",e.NC.CalCh);
}

int ISP(char ch1,char ch2)
{
	switch(ch2)
	{
		case '(':
			return -1;
		case ')':
			if(ch1=='(') return 0;
			return 1;
		case '*':
			if(ch1=='*'||ch1=='/'||ch1=='%'||ch1==')') return 1;
			return -1;
		case '/':
			if(ch1=='*'||ch1=='/'||ch1=='%'||ch1==')') return 1;
			return -1;
		case '%':
			if(ch1=='*'||ch1=='/'||ch1=='%'||ch1==')') return 1;
			return -1;
		case '+':
			if(ch1=='('||ch1=='#') return -1;
			return 1;//+
		case '-':
			if(ch1=='('||ch1=='#') return -1;
			return 1;//-
		case '#':
			if(ch1=='#') return 0;
			return 1;
	}
	printf("ERROR in ISP!!!!\n");
	return 0;
}

int suftop=-1;

void POSTFIX(Element mid[],Element suf[])//中缀转后缀 
{
	int midtop0=-1,tptop0=-1;
	Element tp[100];
	Element s;
	tp[++tptop0].NC.CalCh='#';
	tp[tptop0].flag=Operator;
	while(1)
	{
		s=mid[++midtop0];
		if(s.flag==Number) suf[++suftop]=s;
		else
		{
			if(s.NC.CalCh=='#')
			{
				while(tptop0>0)
				{
					suf[++suftop]=tp[tptop0--];
				}
				suf[++suftop].NC.CalCh='#';
				suf[suftop].flag=Operator;
				break;
			}
			else if(s.NC.CalCh==')')
			{
				while(tp[tptop0].NC.CalCh!='(')
				{
					suf[++suftop]=tp[tptop0--];
				}
				tptop0--;
			}
			else
			{
				while(ISP(tp[tptop0].NC.CalCh,s.NC.CalCh)>=0&&tptop0>0)
				{
					suf[++suftop]=tp[tptop0--];
				}
				tp[++tptop0]=s;
			}
		}
	}
}

int maths(int a,int b,char ch)
{
	switch(ch)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		default:
			printf("ERROR in MATH!!!!\n");
			return 0;
	}
}

Tree CREATE_TREE(Element data) //生成树
{
	Tree T = (Tree)malloc(sizeof(TreeNode));
	T->data = data;
	T->lchild = NULL;
	T->rchild = NULL;
	return T;
}

void TREE_CALCULATE(Tree ROOT)
{
	if(ROOT!=NULL)
	{
		TREE_CALCULATE(ROOT->rchild);
		TREE_CALCULATE(ROOT->lchild);
		if(ROOT->data.flag==Operator)
		{
			ROOT->data.flag=Number;
			char tempch=ROOT->data.NC.CalCh;
			ROOT->data.NC.Num=maths(ROOT->lchild->data.NC.Num,ROOT->rchild->data.NC.Num,tempch);
		} 
	}
}

Element mid[100];
Element suf[100];
Element Operatorch[100];
Tree tree[100];
int midtop=-1;
int treetop=-1;

int main()
{
	char ch[700];
	fgets(ch,700,stdin);
	int length=strlen(ch);
	int temp;
	int j;
	midtop=-1;

	for(int i=0; i<length-1&&ch[i]!='='; i++)//字符串转中缀
	{
		if(ch[i]==' ') continue;
		if(ch[i]>'9'||ch[i]<'0')
		{
			mid[++midtop].NC.CalCh=ch[i];
			mid[midtop].flag=Operator;
		}
		else
		{
			temp=0;
			for(j=i; ch[j]<='9'&&ch[j]>='0'; j++)
			{
				temp*=10;
				temp+=ch[j]-'0';
			}
			mid[++midtop].NC.Num=temp;
			mid[midtop].flag=Number;
			i=j-1;
		}
	}
	mid[++midtop].NC.CalCh='#';
	mid[midtop].flag=Operator;


	POSTFIX(mid,suf);//中缀转后缀
	/*for(int k=0; k<=suftop; k++)//输出后缀表达式
	{
		Element_print(suf[k]);
	}
	printf("\n");*/

	Tree ROOT;

	for(int i=0; i<suftop; i++)
	{
		if(suf[i].flag==Number)
		{
			Tree p=CREATE_TREE(suf[i]);
			tree[++treetop]=p;
		}
		else if(suf[i].flag==Operator)
		{
			Tree p=CREATE_TREE(suf[i]);
			p->rchild=tree[treetop--];
			p->lchild=tree[treetop--];
			tree[++treetop]=p;
		}
	}

	ROOT=tree[treetop];
	
	Element_print(ROOT->data);
	printf(" ");
	Element_print(ROOT->lchild->data);
	printf(" ");
	Element_print(ROOT->rchild->data);
	printf("\n");
	
	TREE_CALCULATE(ROOT);

	printf("%d",ROOT->data.NC.Num);
	
	return 0;
}
