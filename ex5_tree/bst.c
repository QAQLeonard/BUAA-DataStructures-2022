#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct TreeNode
{
	int data;
	int depth;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
} TreeNode,*Tree;

Tree CREATE_TREE(int data) //生成树
{
	Tree T = (Tree)malloc(sizeof(TreeNode));
	T->data = data;
	T->lchild = NULL;
	T->rchild = NULL;
	return T;
}

void INORDER_TREE(Tree ROOT) //中序遍历
{
	if (ROOT != NULL) 
	{
		INORDER_TREE(ROOT->lchild);
		if(ROOT->lchild==NULL&&ROOT->rchild==NULL) printf("%d %d\n", ROOT->data,ROOT->depth);
		INORDER_TREE(ROOT->rchild);
	}
}


int main()
{
	bool flag=false;
	int num;
	scanf("%d",&num);
	int data;
	scanf("%d",&data);
	Tree T=CREATE_TREE(data);
	T->depth=1;
	Tree end;
	for(int i=0; i<num-1; i++)
	{
		flag=false;
		scanf("%d",&data);
		Tree p=CREATE_TREE(data);
		end=T;

		while(!flag)
		{
			if(data<end->data)
			{
				if(end->lchild==NULL)
				{
					p->depth=end->depth+1;
					end->lchild=p;
					flag=true;
				}
				else
				{
					end=end->lchild;
				}
			}
			else
			{
				if(end->rchild==NULL)
				{
					p->depth=end->depth+1;
					end->rchild=p;
					flag=true;
				}
				else
				{
					end=end->rchild;
				}
			}
		}
	}

	INORDER_TREE(T);
}
