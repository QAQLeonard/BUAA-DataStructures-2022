#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct AEdit
{
	int key;
	int position;
	int length;
	char str[520];
	/*void init(int a,int b,int c)
	{
		key=a;
		position=b;
		length=c;
	};*///为啥c语言没有类！！！！！

} Edit;

void Insert(char str0[],int *length_str0,int pos,char str[],Edit *edit0)
{
	int temp_length=strlen(str);
	int i;
	edit0->key=1;
	edit0->position=pos;
	edit0->length=strlen(str);
	strcpy(edit0->str,str);
	for(i=*length_str0+temp_length; i>=pos+temp_length; i--)
	{
		str0[i]=str0[i-temp_length];
	}
	for(i=pos; i<pos+temp_length; i++)
	{
		str0[i]=str[i-pos];
	}
	*length_str0+=temp_length;
}

void Delete(char str0[],int *length_str0,int pos,int n,Edit *edit0)
{
	int i;
	edit0->key=2;
	edit0->position=pos;
	edit0->length=n;//0123456789
	for(i=pos; i<pos+n; i++) //0
	{
		edit0->str[i-pos]=str0[i];
		str0[i]=str0[i+n];
	}
	edit0->str[n]='\0';
	for(; str0[i+n]!='\0'; i++)
	{
		str0[i]=str0[i+n];
	}
	for(int j=i; j<i+n; j++)
	{
		str0[j]='\0';
	}

	*length_str0-=n;
}

void test_print(char str[])
{
	int i=0;
	while(str[i]!='\0')
	{
		printf("%c",str[i++]);
	}
	printf("\n");
}
int main()
{
	char str0[520];
	memset(str0,'\0',520);
	char c;
	int op,pos,n;
	int t=0;
	char str[520];
	int top=-1,i=0;
	Edit edit[520];
	Edit edit0;
	while((c=fgetc(stdin))!='\n')
	{
		str0[i++]=c;
	}
	str0[i]='\0';
	i=0;
	//printf("success in read_in\n");
//-------------------------------------------------------------------------------------------//
	scanf("%d",&t);
	for(int m=0;m<t;m++)
	{
		memset(str,'\0',520);
		memset(edit[++top].str,'\0',520);
		scanf("%d %d %s",&op,&pos,str);
		edit[top].position=pos;
		edit[top].length=strlen(str);
		strcpy(edit[top].str,str);
		switch(op)
		{
			case 1:
				edit[top].key=1;
				break;
			case 2:
				edit[top].key=2;
				break;
			
		}
	}
	c=fgetc(stdin);
	/*for(int j=0;j<=top;j++)
	{
		printf("%d %d %s %d\n",edit[j].key,edit[j].position,edit[j].str,edit[j].length);
	}
	*/
	//printf("success in read_edit\n");
//-------------------------------------------------------------------------------------------//	
	int length_str0=strlen(str0);
	while(scanf("%d",&op)&&op!=-1)
	{
		switch(op)
		{
			case 1:
				memset(str,'\0',520);
				memset(edit[++top].str,'\0',520);
				scanf("%d %s",&pos,str);
				if(pos>length_str0)
				{
					printf("ERROR INPUT");
					top--;
					break;
				}
				//printf("success in read_insert\n");
				Insert(str0,&length_str0,pos,str,&edit[top]);
				//test_print(str0);
				break;

			case 2:
				memset(str,'\0',520);
				memset(edit[++top].str,'\0',520);
				scanf("%d %d",&pos,&n);

				if(pos>=length_str0)
				{
					printf("ERROR INPUT");
					top--;
					scanf("%s",str);
					memset(str,'\0',520);
					break;
				}
				else if(pos+n>length_str0)
				{
					n=length_str0-pos;
				}
				//printf("success in read_delete\n");
				Delete(str0,&length_str0,pos,n,&edit[top]);
				//test_print(str0);
				break;

			case 3:
				//printf("success in read_cancel_%d\n",edit[top].key);
				
				if(edit[top].key==1&&top!=-1)
				{
					Delete(str0,&length_str0,edit[top].position,edit[top].length,&edit0);
					top--;
				}
				else if(edit[top].key==2&&top!=-1)
				{
					Insert(str0,&length_str0,edit[top].position,edit[top].str,&edit0);
					top--;
				}
				//test_print(str0);
				break;

			default:
				printf("ERROR INPUT OP!!!\n");
				break;
		}
	}
//-------------------------------------------------------------------------------------------//
	i=0;
	while(str0[i]!='\0')
	{
		printf("%c",str0[i++]);
	}
	printf("\n");

	return 0;
}
