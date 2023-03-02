#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node
{
	char name[30];
	struct Node *next;
} LinkNode,*LinkList;

typedef struct AFunction
{
	char name[30];
	LinkList L;
	struct AFunction *next;
} Function,*Fun;

typedef struct AEdit
{
	char str[520];
	Fun f;//对应哪一个函数
} Edit;

int main()
{
	Function *ffunction=NULL;

	Edit edit[200];
	int top_edit=-1;
	int key;
	while(1)
	{
		scanf("%d",&key);

		if(key==0)//出栈
		{
			
			if(top_edit==0)
			{
				break;
			}
			
			LinkList c_end=edit[top_edit-1].f->L;//上一个指令函数调用的函数堆栈
			LinkList temp;
			
			if(c_end==NULL)//第一个调用的函数
			{
				LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
				strcpy(p->name,edit[top_edit].str);
				p->next=NULL;
				edit[top_edit-1].f->L=p;
				top_edit--;
				
				continue;				
			}
			while(c_end!=NULL)//检查函数是否已经调用过
			{
				if(strcmp(c_end->name,edit[top_edit].str)==0)//该函数调用过
				{
					break;
				}
				temp=c_end;
				c_end=c_end->next;
			}

			if(c_end==NULL)//未调用过
			{
				LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
				strcpy(p->name,edit[top_edit].str);
				p->next=NULL;
				temp->next=p;
				
				
			}
			top_edit--;
		}

		else//进栈
		{
			top_edit++;
			scanf(" %s",edit[top_edit].str);
			//printf("%d\n",top_edit);
			Fun f_end=ffunction;
			Fun temp;

			if(f_end==NULL)//第一个函数
			{
				Function *p=(Function *)malloc(sizeof(Function));
				strcpy(p->name,edit[top_edit].str);
				p->L=NULL;
				p->next=NULL;
				ffunction=p;
				edit[top_edit].f=p;
				//printf("first\n");
				continue;
			}

			while(f_end!=NULL)//检查函数是否已经出现过
			{
				if(strcmp(f_end->name,edit[top_edit].str)==0)//该函数调用过
				{
					edit[top_edit].f=f_end;
					break;
				}
				temp=f_end;
				f_end=f_end->next;
			}

			if(f_end==NULL)//未出现过
			{
				Function *p=(Function *)malloc(sizeof(Function));//添加对应的function 
				strcpy(p->name,edit[top_edit].str);
				p->L=NULL;
				p->next=NULL;
				temp->next=p;
				edit[top_edit].f=p;
				//printf("first\n");
			}

		}
	}
	
	//printf("%s\n",ffunction->L->name);
	Fun end=ffunction;
	//printf("%s:",end->name);
	while(end!=NULL)
	{
		if(end->L!=NULL)
		{
			printf("%s:",end->name);
			LinkList temp=end->L;
			while(temp->next!=NULL)
			{
				printf("%s,",temp->name);
				temp=temp->next;
			}
			printf("%s\n",temp->name);
		}
		end=end->next;
	}
}
