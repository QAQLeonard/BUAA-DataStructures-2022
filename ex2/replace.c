#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


bool check(char ch1,char ch2)
{
	if(ch1==ch2||ch2-ch1==32||ch1-ch2==32) return true;
	return false; 
}


int main()
{
    FILE *fp,*pp;
    
    fp=fopen("filein.txt","r");
    pp=fopen("fileout.txt","w");

    char in[20],out[20],ch,str[1050];
    scanf("%s", in);
	scanf("%s",out);
    int length_in=0,length_out=0,length_txt=0;
    bool flag=false;
    int i=0;
    length_in=strlen(in);
    length_out=strlen(out);

    while((ch=fgetc(fp))!=EOF)
    {
        str[i]=ch;
        i++;
    }
    length_txt=i+1;
    
    for(i=0;i<length_txt;i++)
    {
        flag=false;
		if (check(str[i],in[0]))
        {
            flag=true;
			for(int j=1;j<length_in;j++)
            {
                if(!check(str[i+j],in[j]))
                {
                    flag=false;
                }
            }

            if(flag)
            {
                for(int j=0;j<length_out;j++)
                {
                    fputc(out[j], pp);
                }
                i+=length_in-1;
            }

            else
            {
                fputc(str[i], pp);
            }
        }

        else
        {
            fputc(str[i], pp);
        }
    }

    fclose(fp);
    fclose(pp);
}
