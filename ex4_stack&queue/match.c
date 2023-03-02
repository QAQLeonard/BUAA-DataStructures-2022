#include<stdio.h>
#include<string.h>
#include<stdbool.h>
typedef struct MatchItem
{
	char ch;
	int position;
} Item;

Item item[300];

bool judge(char x,char y)
{
	if(x=='('&&y==')')	return true;
	else if(x=='{'&&y=='}')	return true;
	return false;
}

int main()
{
	int top=-1;
	int i=0;
	char str[500],ans[500];
	bool QuoteFlag=false;
	int length=0,line=0;
	FILE *fin;
	fin=fopen("example.c","r");
	while(fgets(str,500,fin)!=NULL)
	{
		printf("%s",)
		line++;
		length=strlen(str);
		for(int j=0; j<length; j++)
		{
			if(QuoteFlag&&!(str[j]=='*'&&str[j+1]=='/')) continue;
			else if(QuoteFlag&&(str[j]=='*'&&str[j+1]=='/'))
			{
				QuoteFlag=false;
				j++;
				continue;
			}


			if(str[j]=='('||str[j]=='{')
			{
				item[++top].ch=str[j];
				item[top].position=line;
				ans[i++]=str[j];
				if(str[j]=='{'&&top>0)
				{
					if(item[top-1].ch=='(')
					{
						printf("without maching '%c' at line %d\n",item[top-1].ch,item[top-1].position);
						return 0;
					}
				}
				//printf("%c %d\n",str[j],line);
			}

			else if(str[j]==')'||str[j]=='}')
			{
				//printf("%c %d\n",str[j],line);
				if(top<0)
				{
					printf("without maching '%c' at line %d\n",str[j],line);
					return 0;
				}

				if(judge(item[top].ch,str[j]))
				{
					top--;
					ans[i++]=str[j];
				}
				else
				{
					printf("without maching '%c' at line %d\n",str[j],line);
					return 0;
				}
			}

			else if(str[j]=='/'&&str[j+1]=='/')break;
			else if(str[j]=='/'&&str[j+1]=='*')
			{
				j++;
				QuoteFlag=true;
			}
			else if(str[j]=='\'')
			{
				j++;
				while(str[j]!='\''&&str[j]!='\0') j++;
			}

			else if(str[j]=='\"')
			{
				j++;
				while(str[j]!='\"'&&str[j]!='\0') j++;
			}

		}

	}
	ans[i]='\0';
	if(top!=-1)
	{
		printf("without maching '%c' at line %d\n",item[top].ch,item[top].position);
		return 0;
	}
	else printf("%s\n",ans);

}
