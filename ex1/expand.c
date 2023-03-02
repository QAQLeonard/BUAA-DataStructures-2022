#include<stdio.h>
#include<string.h>
#include<stdbool.h>
char ch[100];
char exch[100];

int readnum(char exch[],int *i)
{
	int temp=0;
	while((exch[*i]!='*')&&(exch[*i]!='/')&&(exch[*i]!='+')&&(exch[*i]!='-')&&(exch[*i]!='='))
	{
		temp*=10;
		temp+=exch[*i]-'0';
		//printf("%c",exch[*i]);
		(*i)++;
		
	}
	
	return temp;
}


int main()
{
	gets(ch);
	int temp=0,tempp=0,ans=0;
	int i,j;
	for(i=0,j=0;ch[i]!='\0';i++,j++)
	{
		if(ch[i]==' ')
		{
			j--;
			
		}
		else exch[j]=ch[i];
	}
	i=0;j=0;
	int state=0;//0代表+，1代表- 
	while((exch[i]!='=')&&(exch[i]!='\0'))
	{
		if((exch[i]!='*')&&(exch[i]!='/')&&(exch[i]!='+')&&(exch[i]!='-')&&(exch[i]!='='))
		{
			temp=readnum(exch,&i);
		}
		
		else if(exch[i]=='+'||exch[i]=='-')
		{
			if(state==0) {ans+=temp;temp=0;}
			else if(state==1) {ans-=temp;temp=0;}
			
			
			if(exch[i]=='+') state=0;
			else state=1;
			
			i++;
		}
		else if(exch[i]=='*')
		{
			i++;
			tempp=readnum(exch,&i);
			temp*=tempp;
			tempp=0;
			
		}
		else if(exch[i]=='/')
		{
			i++;
			tempp=readnum(exch,&i);
			temp/=tempp;
			tempp=0;
		}	
	}
	if(state==0) {ans+=temp;temp=0;}
	else if(state==1) {ans-=temp;temp=0;}
	
	
	printf("%d",ans);
	//printf("%d",temp);
	
}
