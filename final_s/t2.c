#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct AFunction
{
	char name[30];
	int c_fun[200];
} Function,*Fun;

typedef struct AEdit
{
	char str[520];
	int f;//对应哪一个函数
} Edit;

Function fun[300];

int main()
{
	Edit edit[300];
	int f_sum=0;
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
			int c_end=0;
			while(fun[edit[top_edit-1].f].c_fun[c_end]!=-1)
			{
				if(fun[edit[top_edit-1].f].c_fun[c_end]==edit[top_edit].f) //调用过
				{
					c_end=-1;
					break;
				}
				c_end++;
			}
			if(c_end!=-1) fun[edit[top_edit-1].f].c_fun[c_end]=edit[top_edit].f;//未调用
			top_edit--;
		}

		else if(key==8)//进栈
		{
			top_edit++;
			scanf(" %s",edit[top_edit].str);
			edit[top_edit].f=-1;
			for(int i=0; i<f_sum; i++)
			{
				if(strcmp(fun[i].name,edit[top_edit].str)==0)//出现过
				{
					edit[top_edit].f=i;
				}
			}
			
			if(edit[top_edit].f==-1)//未出现过的函数
			{
				strcpy(fun[f_sum].name,edit[top_edit].str);
				memset(fun[f_sum].c_fun,-1,sizeof(fun[f_sum].c_fun));
				edit[top_edit].f=f_sum;
				f_sum++;
			}
		}
		printf("          %d\n",top_edit);
	
	}

	for(int i=0;i<f_sum;i++)
	{
		if(fun[i].c_fun[0]!=-1)
		{
			printf("%s:",fun[i].name);
			int j=0;
			for(j=0;fun[i].c_fun[j+1]!=-1;j++)
			{
				printf("%s,",fun[fun[i].c_fun[j]].name);
			}
			printf("%s",fun[fun[i].c_fun[j]].name);
			printf("\n");
		}
	}
}
