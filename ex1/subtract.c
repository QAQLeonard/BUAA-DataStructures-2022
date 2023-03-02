#include <stdio.h>
#include <string.h>
#include<stdbool.h>
char exch1[100], exch2[100],ch1[100],ch2[100];
int num1[100], num2[100];

int len;

int main() 
{
	bool flag=false;
	scanf("%s%s", exch1, exch2);
	int length1 = strlen(exch1);
	int length2 = strlen(exch2);
	int real_length1=0,real_length2=0;
	int i,j;
	memset(num1, 0, sizeof(num1));
	memset(num2, 0, sizeof(num2));
	bool read_flag=false;
	for(i=0,j=0;i<length1;i++)
	{
		if(exch1[i]!='0'&&(!read_flag))
		{
			real_length1=length1-i;
			ch1[j++]=exch1[i];
			read_flag=true;
		}
		else if(read_flag)
		{
			ch1[j++]=exch1[i];
		}
	}
	read_flag=false;
	for(i=0,j=0;i<length2;i++)
	{
		if(ch2[i]!='0'&&(!read_flag))
		{
			real_length2=length2-i;
			ch2[j++]=exch2[i];
			read_flag=true;
		}
		else if(read_flag)
		{
			ch2[j++]=exch2[i];
		}
	}
	//printf("%d %d\n",length1,length2);
	
	if ( real_length1 < real_length2 || (strcmp(ch1,ch2)<0 && real_length1 == real_length2) ) 
	{
		flag = true;
		
		for (int i = length2 - 1 ; i >= length2-real_length2 ; i--)
			num1[length2 - i - 1] = exch2[i] - '0';
			
		for (int i = length1 - 1 ; i >= length1-real_length1 ; i--)
			num2[length1 - i - 1] = exch1[i] - '0';
	} 
	else 
	{
		for (int i = length1 - 1 ; i >= length1-real_length1 ; i--)
			num1[length1 - i - 1] = exch1[i] - '0';
			
		for (int i = length2 - 1 ; i >= length2-real_length2 ; i--)
			num2[length2 - i - 1] = exch2[i] - '0';
	}
	if (real_length1 > real_length2)
		len = real_length1;
	else
		len = real_length2;
		
	for (int i = 0 ; i < len ; i++) 
	{
		num1[i] = num1[i] - num2[i];
		if (num1[i] < 0) 
		{
			num1[i + 1] -= 1;
			num1[i] += 10;
		}
	}
	while (num1[len - 1] == 0 && len > 1) len--;
	
	if (flag) printf("-");
	
	for (int i = len - 1 ; i >= 0 ; i--)
		printf("%d", num1[i]);
		
	printf("\n");
	
	return 0;
}
