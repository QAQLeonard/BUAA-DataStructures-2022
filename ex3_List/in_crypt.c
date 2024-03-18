#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
	char ch;
	struct Node *next;
} LinkNode, *LinkList;

void Init_List(LinkList *L) // 初始化
{
	(*L) = (LinkNode *)malloc(sizeof(LinkNode));
	(*L)->next = NULL;
}

void test_print(LinkList L)
{
	LinkList temp = L;
	while (temp->next != NULL)
	{
		printf("%c", temp->ch);
		temp = temp->next;
	}
	printf("%c\n", temp->ch);
}

char exkey[33];
int hashtable[100];
char key[100];

int main()
{

	FILE *fp, *pp;
	char read_ch;
	fp = fopen("in.txt", "r");
	pp = fopen("in_crpyt.txt", "w");
	int i = 0;
	gets(exkey);
	LinkList L; // 链表初始化
	Init_List(&L);
	L->ch = exkey[0];
	hashtable[exkey[0] - ' '] = 1;

	LinkNode *End = L; // 确立密匙
	for (i = 1; exkey[i] != '\n' && exkey[i] != '\0' && exkey[i] >= ' ' && exkey[i] <= '~'; i++)
	{
		// printf("%c",exkey[i]);
		if (hashtable[exkey[i] - ' '] == 0)
		{
			hashtable[exkey[i] - ' '] = 1;
			LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
			p->ch = exkey[i];
			End->next = p;
			End = p;
		}
		else if (hashtable[exkey[i] - ' '] == 1)
			continue;
	}
	// End->next=NULL;
	// test_print(L);
	for (i = 0; i < 95; i++)
	{
		if (hashtable[i] == 0)
		{
			LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
			p->ch = i + ' ';
			End->next = p;
			End = p;
			// printf("%c",i+' ');
		}
	}
	// End->next=NULL;
	// test_print(L);

	End->next = L;
	LinkList temp = End;
	char temp_char;
	int n = 95;

	while (n > 1)
	{
		temp_char = temp->next->ch;
		LinkList DelLinkList = temp->next;
		temp->next = DelLinkList->next;
		free(DelLinkList);
		for (int i = 0; i < temp_char - ' ' + 31; i++)
		{
			temp = temp->next;
		}

		key[temp_char - ' '] = temp->next->ch;
		n--;
	}
	temp_char = temp->ch;
	key[temp_char - ' '] = exkey[0];
	// test_print(L);

	while ((read_ch = fgetc(fp)) != EOF)
	{
		// printf("%c",ch);
		if (read_ch < ' ' || read_ch > '~')
			fputc(read_ch, pp);
		else
		{
			fputc(key[read_ch - ' '], pp);
		}
	}
}
