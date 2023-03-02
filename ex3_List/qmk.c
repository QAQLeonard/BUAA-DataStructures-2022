#include<stdio.h>
#include<string.h>
struct data
{
    char vocabulary[100];
    int times;
} lib[1000]={"\0", 0}, *pointer[1000]={NULL}, *hold;
FILE *in;

int main()
{
    int i=0, j=0, k=0, flag, n;
    char buffer[1000], c;
    in=fopen("article.txt", "r");
    
    while((c=fgetc(in))!=EOF)
    {
        if(c>='A'&&c<='Z')
        {
            buffer[i]=c-'A'+'a';
            i++;
        }
        else if(c>='a'&&c<='z')
        {
            buffer[i]=c;
            i++;
        }
        else
        {
            buffer[i]='\0';
            flag=0;
            for(k=0; k<j; k++)
            {
                if(strcmp(lib[k].vocabulary,buffer)==0)
                {
                    flag=1;
                    lib[k].times++;
                }
            }
            if(flag==0)
            {
                strcpy(lib[j].vocabulary, buffer);
                pointer[j]=&lib[j];
                j++;
                
            }
            i=0;
        }
    }

    buffer[i]='\0';
            flag=0;
            for(k=0; k<j; k++)
            {
                if(strcmp(lib[k].vocabulary,buffer)==0)
                {
                    flag=1;
                    lib[k].times++;
                }
            }
            if(flag==0)
            {
                strcpy(lib[j].vocabulary, buffer);
                pointer[j]=&lib[j];
                j++;
                
            }

    n=j;
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-1-i; j++)
        {
            if(strcmp(pointer[j]->vocabulary, pointer[j+1]->vocabulary)>0)
            {
                hold=pointer[j];
                pointer[j]=pointer[j+1];
                pointer[j+1]=hold;
            }
        }
    }
    for(i=1; i<n; i++)
    {
        printf("%s %d\n", pointer[i]->vocabulary, pointer[i]->times+1);
    }
    return 0;
}
