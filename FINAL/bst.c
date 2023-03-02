#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int sum=0;

int temp_arr[2000];

typedef struct TreeNode
{
	int data;
	int times;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
	int way[1000];
	int depth;
} TreeNode,*Tree;

int max=0;
Tree max_num=NULL;

Tree CREATE_TREE(int data,int depth) //创建一个树节点
{
	Tree T=(Tree)malloc(sizeof(TreeNode));
	T->data=data;
	T->times=0;
	T->depth=depth;
	T->lchild=NULL;
	T->rchild=NULL;
	return T;
}

void INSERT_TREE(Tree *ROOT,int data,int cmp_times,int depth) //插入节点
{
	if (*ROOT==NULL)
	{
		*ROOT=CREATE_TREE(data,depth);
		sum+=cmp_times;
	}
	else if (data<(*ROOT)->data)
	{
		INSERT_TREE(&(*ROOT)->lchild, data,cmp_times+1,depth+1);
	}
	else if (data>(*ROOT)->data)
	{
		INSERT_TREE(&(*ROOT)->rchild, data,cmp_times+1,depth+1);
	}
	else if(data==(*ROOT)->data)
	{
		cmp_times++;
		(*ROOT)->times++;
		sum+=cmp_times;
	}
}

void POSTORDER_TREE(Tree ROOT,int depth,int way[]) //后序遍历
{
	if (ROOT != NULL)
	{
		way[depth]=ROOT->data;
		for(int i=0;i<depth;i++)
		{
			ROOT->way[i]=way[i];
		}
		ROOT->depth=depth;
		POSTORDER_TREE(ROOT->lchild,depth+1,way);
		POSTORDER_TREE(ROOT->rchild,depth+1,way);
		if(ROOT->times>max)
		{
			max=ROOT->times;
			max_num=ROOT;
		}
	}
}

int main()
{
	Tree root=NULL;
	int n;
	int temp;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&temp);
		INSERT_TREE(&root,temp,0,0);
	}
	POSTORDER_TREE(root,0,temp_arr);
	printf("%d\n",sum);
	for(int i=0;i<max_num->depth;i++)
	{
		printf("%d ",max_num->way[i]);
	}
	printf("%d\n",max_num->data);
	return 0;
}
