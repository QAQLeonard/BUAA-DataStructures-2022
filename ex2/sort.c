#include<stdio.h>
#include<string.h>

typedef struct aPerson{
	char name[30];
	char phone[12];
	int number;
}Person; 


void bubbleSortPLUS(Person a[], int n) 
{
	int i, j, flag;
	Person temp;
	for (i = 0; i < n - 1; i++) {
		flag = 0;
		for ( j = 0; j < n - 1 - i; j++)  
		{
			if (strcmp(a[j].name,a[j + 1].name)>0)
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}
int main()
{
	int num=0;
	char ch;
	scanf("%d",&num);
	int times[num];
	memset(times,0,num);
	Person person[num];
	
	for(int i=0;i<num;i++)
	{
		scanf("%s",person[i].name);
		ch=fgetc(stdin);
		scanf("%s",person[i].phone);
		ch=fgetc(stdin);
		person[i].number=0;
		
		for(int j=0;j<i;j++)
		{
			if(strcmp(person[i].name,person[j].name)==0)
			{
				if(strcmp(person[i].phone,person[j].phone)!=0) {person[i].number++;}
				else 
				{
					//person[i].number=0;
					num--;
					i--;
					break;
				}
			}
		}
	}
	

	
	for(int i=0;i<num;i++)
	{
		if(person[i].number>0)
		{
			int length=strlen(person[i].name);
			person[i].name[length]='_';
			person[i].name[length+1]='0'+person[i].number;
			person[i].name[length+2]='\0';
		}
	}
	bubbleSortPLUS(person,num);
	
	printf("\n");
	for(int i=0;i<num;i++)
	{
		printf("%s %s\n",person[i].name,person[i].phone);
	}
	
	return 0;
}
