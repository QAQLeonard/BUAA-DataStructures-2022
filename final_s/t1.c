#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct ALOG
{
	int ID;
	char name[20];
	int m_ID;
	char time[7];
} Log;

typedef struct EXCEPTION
{
	int ID;
	char name[20];
} Exception;

int Cmp(const void *elem1,const void *elem2)
{
	Exception *e1 = (Exception *)elem1;
	Exception *e2 = (Exception *)elem2;
	return (*e1).ID-(*e2).ID;
	
}

int main()
{
	int log_num;
	scanf("%d",&log_num);
	Log log[log_num];
	Exception e[log_num];
	int e_sum=0;
	for(int i=0; i<log_num; i++)
	{
		scanf("%d",&log[i].ID);
		scanf("%s",log[i].name);
		scanf("%d",&log[i].m_ID);
		scanf("%s",log[i].time);
		for(int j=0; j<i; j++)
		{
			if(log[i].ID==log[j].ID&&log[i].m_ID!=log[j].m_ID)//Òì³£
			{
				bool flag=false;
				for(int k=0; k<e_sum; k++)
				{
					if(log[i].ID==e[k].ID)
					{
						flag=true;
						break;
					}
				}
				if(!flag)
				{
					e[e_sum].ID=log[i].ID;
					strcpy(e[e_sum].name,log[i].name);
					e_sum++;
				}
			}
		}
	}
	qsort(e,e_sum,sizeof(Exception),Cmp);
	for(int i=0;i<e_sum;i++)
	{
		printf("%d %s\n",e[i].ID,e[i].name);
	}
	return 0;
}
