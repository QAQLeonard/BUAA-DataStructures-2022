#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct ARRAY
{
	int *a;
	int length;
} array;

int cmp(const void *a, const void *b)
{
	return (*(int *)a-*(int *)b );
}

array shuffle(array myarr)
{
	//printf("shuffle\n");
	static unsigned lucky_number = 520;
	int len=myarr.length;
	int *mylist=myarr.a;
	while(len > 1)
	{
		int temp = *mylist;
		*mylist = *(mylist + lucky_number % len);
		*(mylist + lucky_number % len) = temp;
		mylist++;
		len--;
		lucky_number *= 113344;
		lucky_number += 993311;
	}
	return myarr;
}

array merge(array a1,array a2)
{
	//printf("merge\n");
	a1.a=(int *)realloc(a1.a,(a1.length+a2.length)*sizeof(int));
	for(int i=0; i<a2.length; i++)
	{
		a1.a[i+a1.length]=a2.a[i];
	}
	free(a2.a);
	a1.length+=a2.length;
	return a1;
}

array sort(array arr)
{
	//printf("sort\n");
	int flag;
	for(int i=0; i<arr.length-1; i++)
	{
		flag=0;
		for(int j=0; j<arr.length-1-i; j++)
		{
			if(arr.a[j]>arr.a[j + 1])
			{
				int temp=arr.a[j];
				arr.a[j]=arr.a[j + 1];
				arr.a[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0) break;
	}
	return arr;
}

array calculate(char ch[],int head,int tail)
{
	if(ch[head]=='m')
	{
		//printf("merge\n");
		int temp=head+6;
		int top=-1;
		while(top!=-1||temp==head+6)
		{

			while((ch[temp]!='('&&ch[temp]!=')'&&ch[temp]!='['&&ch[temp]!=']')&&temp<tail)
			{
				temp++;
			}
			if(ch[temp]=='('||ch[temp]=='[') top++;
			else if(ch[temp]==')'||ch[temp]==']') top--;
			temp++;
		}
		temp--;
		//printf("%d %d||%d %d\n",head+6,temp,temp+2,tail-1);
		return merge(calculate(ch,head+6,temp),calculate(ch,temp+2,tail-1));
	}

	else if(ch[head]=='s'&&ch[head+1]=='h')
	{
		//printf("%c %c\n",ch[head+8],ch[tail-1]);
		return shuffle(calculate(ch,head+8,tail-1));
	}

	else if(ch[head]=='s'&&ch[head+1]=='o')
	{
		//printf("%c %c",ch[head+5],ch[tail-1]);
		return sort(calculate(ch,head+5,tail-1));
	}

	else if(ch[head]=='[')
	{
		int num=0;
		//printf("0\n");
		int temp0=head;
		while(ch[temp0]!=']')
		{
			temp0++;
			if(ch[temp0]==',') num++;
		}
		num++;
		array myarr;
		int *aa=(int *)malloc(num*sizeof(int));
		memset(aa,0,num*sizeof(int));
		temp0=head+1;
		//printf("%d\n",num);
		for(int i=0; i<num; i++)
		{
			bool flag0=0;
			if(ch[temp0]=='-')
			{
				flag0=1;
				temp0++;
			}
			while((ch[temp0]>='0'&&ch[temp0]<='9'))
			{
				//printf("%c",ch[temp0]);
				aa[i]*=10;
				aa[i]+=ch[temp0]-'0';
				temp0++;
			}
			if(flag0) aa[i]=-aa[i];
			//printf("%d ",aa[i]);
			temp0++;
		}
		//printf("\n");
		myarr.a=aa;
		myarr.length=num;
		return myarr;
	}
	else
	{
		printf("ERROR!\n");
		exit(0);
	}
}

char ch1[300],ch2[300];

int main()
{
	scanf("%s",ch1);
	scanf("%s",ch2);

	array a1=calculate(ch1,0,strlen(ch1)-1);
	array a2=calculate(ch2,0,strlen(ch2)-1);

	if(a1.length!=a2.length)
	{
		printf("Failed\n");
		return 0;
	}
	else
	{
		for(int i=0; i<a1.length; i++)
		{
			if(a1.a[i]!=a2.a[i])
			{
				printf("Failed\n");
				return 0;
			}
		}
	}
	printf("TobyWendy\n");

	/*for(int i=0; i<a1.length; i++)
	{
		printf("%d ",a1.a[i]);
	}
	printf("\n");
	for(int i=0; i<a2.length; i++)
	{
		printf("%d ",a2.a[i]);
	}
	printf("\n");*/
	return 0;
}
