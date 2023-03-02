#include<stdio.h>
#include<stdlib.h>

#define MaxTreeSize 100

typedef struct TreeNode
{
	int data;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
} TreeNode,*Tree;

Tree CREATE_TREE(int data) //创建一个树节点
{
	Tree T=(Tree)malloc(sizeof(TreeNode));
	T->data=data;
	T->lchild=NULL;
	T->rchild=NULL;
	return T;
}

void INSERT_TREE(Tree ROOT,int data) //插入节点
{
	if (ROOT==NULL)
	{
		ROOT=CREATE_TREE(data);
	}
	else if (data<ROOT->data)
	{
		INSERT_TREE(ROOT->lchild, data);
	}
	else if (data > ROOT->data)
	{
		INSERT_TREE(ROOT->rchild, data);
	}
}

Tree SEARCH_TREE(Tree ROOT, int data) //寻找某个节点，返回地址
{
	if (ROOT == NULL)
	{
		return NULL;
	}
	else if (data == ROOT->data)
	{
		return ROOT;
	}
	else if (data < ROOT->data)
	{
		return SEARCH_TREE(ROOT->lchild, data);
	}
	else if (data > ROOT->data)
	{
		return SEARCH_TREE(ROOT->rchild, data);
	}
}

void PREORDER_TREE(Tree ROOT) //前序遍历
{
	if (ROOT != NULL)
	{
		printf("%d ", ROOT->data);
		PREORDER_TREE(ROOT->lchild);
		PREORDER_TREE(ROOT->rchild);
	}
}

void INORDER_TREE(Tree ROOT) //中序遍历
{
	if (ROOT != NULL)
	{
		INORDER_TREE(ROOT->lchild);
		printf("%d ", ROOT->data);
		INORDER_TREE(ROOT->rchild);
	}
}

void POSTORDER_TREE(Tree ROOT) //后序遍历
{
	if (ROOT != NULL)
	{
		POSTORDER_TREE(ROOT->lchild);
		POSTORDER_TREE(ROOT->rchild);
		printf("%d ", ROOT->data);
	}
}

void LEVELORDER_TREE(Tree Root)//层次遍历
{
	Tree queue[100];
	if(Root==NULL)
	{
		return ;
	}
	int head=0;
	int tail=0;
	queue[tail++]=Root;
	while(head<tail)
	{
		Tree p=queue[head++];
		printf("%d\n",p->data);
		if(p->lchild!=NULL) queue[tail++]=p->lchild;
		if(p->rchild!=NULL) queue[tail++]=p->rchild;
	}
}

void DELETE_TREENODE(Tree ROOT, int data)//删除某个节点
{
	if (ROOT == NULL)
	{
		return;
	}
	else if (data < ROOT->data)
	{
		DELETE_TREENODE(ROOT->lchild, data);
	}
	else if (data > ROOT->data)
	{
		DELETE_TREENODE(ROOT->rchild, data);
	}
	else
	{
		if (ROOT->lchild == NULL && ROOT->rchild == NULL)
		{
			free(ROOT);
			ROOT = NULL;
		}
		else if (ROOT->lchild == NULL)
		{
			Tree temp = ROOT;
			ROOT = ROOT->rchild;
			free(temp);
		}
		else if (ROOT->rchild == NULL)
		{
			Tree temp = ROOT;
			ROOT = ROOT->lchild;
			free(temp);
		}
		else
		{
			Tree temp = ROOT->rchild;
			while (temp->lchild != NULL)
			{
				temp = temp->lchild;
			}
			ROOT->data = temp->data;
			DELETE_TREENODE(ROOT->rchild, temp->data);
		}
	}
}


void DELETE_TREE(Tree ROOT)
{
	if (ROOT != NULL)
	{
		
		DELETE_TREE(ROOT->lchild);
		DELETE_TREE(ROOT->rchild);
		free(ROOT);
	}
}
