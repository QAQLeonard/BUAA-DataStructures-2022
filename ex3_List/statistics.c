#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define state_0 0//未在读入单词 
#define state_1 1//正在读入单词 

//----------------------------------------------------------------------------//
typedef struct Node
{
	char word[30];
	int num;
	struct Node *next;
} LinkNode,*LinkList;

void Init_List(LinkList *L)//初始化
{
	(*L)=(LinkNode *)malloc(sizeof(LinkNode));
	(*L)->next=NULL;
}

LinkList Search_Item(char item[],LinkList L)
{
	LinkNode *temp;
	temp=L;
	while(temp!=NULL&&strcmp(temp->word,item)!=0)
	{
		temp=temp->next;
	}
	return temp;
}

void Listsort(LinkNode *L,int n)
{
	int i = 0;
	int j = 0;
	LinkNode *temp=L;
	LinkNode *p;
	LinkNode *p1;
	for(i=0;i<n-1;i++)
	{
		for (j=0;j<n-i-1;j++)
		{
			p=temp;
			p1=temp->next;
			if (strcmp(p->word,p1->word)>0)
			{
				int temp1=p->num;
				char temp2[30];
				strcpy(temp2,p->word);
				p->num=p1->num;
				strcpy(p->word,p1->word);
				p1->num=temp1;
				strcpy(p1->word,temp2);
			}
			temp=temp->next;
		}
		temp=L;
	}
}

int Get_ListLength(LinkList L)
{
	int ListLength=0;
	LinkNode *p=L;
	while(p)
	{
		ListLength++;
		p=p->next;
	}
	return ListLength;
}

void test_print(LinkList L)
{
	LinkList temp=L;
	while(temp!=NULL)
	{
		printf("%s %d\n",temp->word,temp->num);
		temp=temp->next;
	}
}
//-------------------------------------------------------------------------------//

int state=state_0; 

int main()
{
	FILE *fp;
	char FILEStreamReader;
	char BufferedReader[30];
	fp=fopen("article.txt","r");
	LinkList L;
	Init_List(&L);
	LinkNode *End=L;
	int i=0;
	
	
	//----------------------------------------------------------------------------//
	while((FILEStreamReader=fgetc(fp))!=EOF)
	{
		printf("%c",FILEStreamReader);
		if(FILEStreamReader<'A'||FILEStreamReader>'z'||(FILEStreamReader>'Z'&&FILEStreamReader<'a'))
		{
			if(state==state_0) continue;
			else if(state==state_1)
			{
				state=state_0;
				LinkList p=Search_Item(BufferedReader,L);
				BufferedReader[i]='\0';//缓冲区输入结束
				i=0;
				if(p!=NULL)
				{
					p->num++;
					p=NULL;
				}
				else
				{
					LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));//加入新节点 
					strcpy(p->word,BufferedReader);
					p->num=1;
					End->next=p;
					End=p;
				}
				memset(BufferedReader,'\0',30);//读完一个单词，缓冲区清零
			}
			
		}
		else if((FILEStreamReader>='A'&&FILEStreamReader<='Z')||(FILEStreamReader>='a'&&FILEStreamReader<='z'))
		{
			if(FILEStreamReader<97) FILEStreamReader=FILEStreamReader+32;//大写转小写 
			if(state==state_0) state=state_1;
			 
			BufferedReader[i]=FILEStreamReader;
			i++;
		}
	}
	End->next=NULL;
	//----------------------------------------------------------------------------//
		
	LinkList del=L;
	L=L->next;
	free(del);
	
	int length=Get_ListLength(L);
	Listsort(L,length);
	test_print(L);
	
}
