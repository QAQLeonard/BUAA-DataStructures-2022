#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NHASH  3001
#define MULT  37

char dictionary[3505][25];

unsigned int hash(char *str)
{
	unsigned int h=0;
	char *p;
	for(p=str; *p!='\0'; p++)
	{
		h = MULT*h + *p;
	}
	return h % NHASH;
}

typedef struct Node
{
	char ch[25];
	struct Node *next;
} LinkNode,*LinkList;

void find(int key,int num,char word[])
{

	int search[27];
	switch(key)
	{
		case 1://À≥–Ú≤È’“
		{
			int i;
			for(i=0; i<num; i++)
			{
				if(strcmp(word,dictionary[i])<=0)
				{
					break;
				}
			}
			if(strcmp(word,dictionary[i])==0) printf("1 %d\n", i+1);
			else printf("0 %d\n", i+1);
			break;
		}

		case 2://’€∞Î≤È’“
		{
			int low=0,high=num-1,mid=0,flag=0,ans=0;
			while(low<=high)
			{
				mid=(low+high)/2;
				ans++;
				if(strcmp(word,dictionary[mid])==0)
				{
					flag=1;
					break;
				}
				else if(strcmp(word,dictionary[mid])<0)	high=mid-1;
				else	low=mid+1;
			}
			printf("%d %d\n", flag, ans);
			break;
		}

		case 3://À˜“˝≤È’“
		{
			int i=0;
			memset(search,0,sizeof(search));
			int key_char='a';
			while(key_char<='z'&&i<num)
			{
				int j=i;
				while(dictionary[j][0]!=key_char&&j<num)
				{
					j++;
				}
				if(j<num)
				{
					search[key_char-'a']=j;
					i=j;
				}
				//printf("%c %d\n",key_char,search[key_char-'a']);
				key_char++;
			}
			int low=search[word[0]-'a'],high=search[word[0]-'a'+1]-1,mid,flag=0,ans=0;
			i=1;
			if(low==0) 
			{
				printf("0 0\n");
				return ;
			}
			while(high<=low)
			{
				high=search[word[0]-'a'+1+i]-1;
			}

			while(low<=high)
			{
				mid=(low+high)/2;
				ans++;
				if(strcmp(word,dictionary[mid])==0)
				{
					flag=1;
					break;
				}
				else if(strcmp(word,dictionary[mid])<0)	high=mid-1;
				else	low=mid+1;
			}
			printf("%d %d\n",flag,ans);
		}
		break;

		case 4://π˛œ£≤È’“
		{
			int i;
			LinkList Hash[3050]= {NULL};
			LinkList p,q;
			int ans=0,flag=0;
			int temp;
			for(i=0; i<=num; i++)
			{
				temp=hash(dictionary[i]);
				LinkList p=(LinkList)malloc(sizeof(LinkNode));
				strcpy(p->ch,dictionary[i]);
				p->next=NULL;
				if(Hash[temp]==NULL)	Hash[temp]=p;
				else
				{
					q=Hash[temp];
					while(q->next!=NULL)	q=q->next;
					q->next=p;
				}
			}
			temp=hash(word);
			p=Hash[temp];
			while(p!=NULL&&strcmp(word,p->ch)>=0)
			{
				ans++;
				if(strcmp(word,p->ch)==0)
				{
					flag=1;
					break;
				}
				p=p->next;
			}
			printf("%d %d\n", flag, ans);
			break;
		}
		default:
		{
			printf("ERROR OP!!!\n");
			break;
		}
	}
}
int main()
{

	return 0;
}
