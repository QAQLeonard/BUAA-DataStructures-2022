#include<stdio.h>
#include<stdbool.h>
char ch[100];
char exch[100];
int main()
{
	scanf("%s",ch);
	bool flag=false;
	int first_num_position=0,dot_position=0;
	int i,j;
	int jie=0;
	for(i=0,j=0;ch[i]!='\0';i++,j++)
	{
		if(ch[i]>='0'&&ch[i]<='9')
		{
			if(flag)exch[j]=ch[i];
			else if(!flag&&ch[i]>'0')
			{
				first_num_position=i;
				flag=true;
				exch[j]=ch[i];
				if(ch[i+1]!='\0')exch[++j]='.';
			}
			else j--;
		}
		else if(ch[i]=='.')
		{
			dot_position=i;
			j--;
		}
	}
	exch[j++]='e';
	if(first_num_position<dot_position)
	{
		jie=dot_position-first_num_position-1;
		exch[j]='\0';
	}
	else
	{
		jie=-first_num_position+dot_position;
		exch[j]='\0';
	}
	printf("%s%d",exch,jie);
	
	
}


