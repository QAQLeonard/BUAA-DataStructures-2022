#include<stdio.h>


int main()
{
	int top=-1;
	int stack[100];
	int command;
	int data;	
	while(scanf("%d ",&command)!=EOF&&command!=-1)
	{
		switch(command)
		{
			case 1:
				if(top==99)
				{
					printf("error ");
					continue;
				}
				scanf("%d ",&data);
				stack[++top]=data;
				break;
			case 0:
				if(top==-1)
				{
					printf("error ");
					continue;
				}
				printf("%d ",stack[top]);
				top--;
				break;
		}
	}
	return 0;
}
