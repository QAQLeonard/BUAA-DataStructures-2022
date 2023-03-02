#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char key[27];
char exkey[27];
char encrypt[30];
char str[1000];
int hashtable[27];
int main()
{
    
	FILE *fp,*pp;
    char ch;
    fp=fopen("encrypt.txt","r");
    pp=fopen("output.txt","w");
    int i=0,j=0;
    scanf("%s", exkey);
    int length_key=strlen(exkey);
    for(i=0,j=0;exkey[i]!='\0';i++)
    {
		if(encrypt[exkey[i]-'a']==0)
		{
			encrypt[exkey[i]-'a']=1;
			key[j]=exkey[i];
			j++;
		}
		else if(encrypt[exkey[i]-'a']==1) length_key--;
	}
	//printf("%s",key);
	for(i=length_key,j=25;i<26;j--)
	{
		if(encrypt[j]==0)
		{
			key[i]='a'+j;
			i++;
		}
	}
	
	
	while((ch=fgetc(fp))!=EOF)
	{
	    //printf("%c",ch);
		if(ch<'a'||ch>'z') fputc(ch,pp);
	    else
	    {
			fputc(key[ch-'a'],pp);
		}
	}
	
	
}

