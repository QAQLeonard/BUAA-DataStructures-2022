#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>


int main()
{
	FILE *f1, *f2;
	f1 = fopen("10.out", "r");
	f2 = fopen("out.out", "r");
	int ch1,ch2;
	int line=1;
	while(((ch1=fgetc(f1))!=EOF)&&((ch2=fgetc(f2))!=EOF))
	{
		if(ch1!=ch2) printf("%d\n",line);
		if(ch1=='\n') line++;
	}
	return 0;
	
}
