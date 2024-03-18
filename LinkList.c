#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
	int num;
	struct Node *next;
} LinkNode, *LinkList;

void InitList(LinkList *L) //?????
{
	(*L) = (LinkNode *)malloc(sizeof(LinkNode));
	(*L)->next = NULL;
}

int GetListLength(LinkList L) //???????????
{
	int ListLength = 0;
	LinkNode *p = L;
	while (p)
	{
		ListLength++;
		p = p->next;
	}
	return ListLength;
}

void TailInsertList(LinkNode *L, int n) // ¦Â?¾Þ??n??????????
{
	int data;
	LinkNode *End = L;
	while (n--)
	{
		scanf("%d", &data);
		LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
		p->num = data;
		End->next = p;
		End = p;
	}
	End->next = NULL;
}

LinkList SearchItem(int item, LinkList L) //?????item????????????????NULL
{
	LinkNode *temp;
	temp = L;
	while (temp != NULL && temp->num != item)
	{
		temp = temp->next;
	}
	return temp;
}

LinkList SearchPosition(int position, LinkList L)
{
	int i = 0;
	LinkList temp;
	temp = L;
	for (i = 0; i < position; i++)
	{
		temp = temp->next;
	}
	return temp;
}

void DeletePosition(int position, LinkList L)
{
	LinkList temp = L;
	for (int i = 0; i < position; i++)
	{
		temp = temp->next;
	}
	LinkList DelLinkList = temp->next;
	temp->next = DelLinkList->next;
	free(DelLinkList);
	DelLinkList = NULL;
	temp = NULL;
}

void AddPosition(int position, LinkList L, int data)
{
	LinkList temp = L;
	for (int i = 0; i < position; i++)
	{
		temp = temp->next;
	}
	LinkList AddLinkList = (LinkList)malloc(sizeof(LinkNode));
	AddLinkList->num = data;
	AddLinkList->next = temp->next->next;
	temp->next = AddLinkList;
	temp = NULL;
}

void ListBubbleSort(LinkNode *L, int n)
{
	int i = 0;
	int j = 0;
	LinkNode *temp = L;
	LinkNode *p;
	LinkNode *p1;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			p = temp;
			p1 = temp->next;
			if (p->num <= p1->num)
			{
				int temp1 = p->num;
				p->num = p1->num;
				p1->num = temp1;
			}
			temp = temp->next;
		}
		temp = L;
	}
}

void TestPrint(LinkList L)
{
	LinkList temp = L;
	while (temp->next != NULL)
	{
		printf("%d ", temp->num);
		temp = temp->next;
	}
	printf("%d\n", temp->num);
}

void HeadInsertList(LinkList L, int n) //???????¾Þ??n??????????
{
	int data;
	while (n--)
	{
		scanf("%d", &data);
		LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
		p->num = data;
		p->next = L->next;
		L->next = p;
	}
}
// Í·²å??

void DeleteData(LinkList L, int data)
{
	LinkList temp = L;
	while (temp->next != NULL)
	{
		if (temp->next->num == data)
		{
			LinkList DelLinkList = temp->next;
			temp->next = DelLinkList->next;
			free(DelLinkList);
			DelLinkList = NULL;
		}
		else
		{
			temp = temp->next;
		}
	}
}