//Vision 1.5，使用数组集中分配内存

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

//use dictionary tree to solve the problem
#define MAX 100000
#define eps 1e-8
typedef struct Node
{
	bool flag;
	struct Node *letter[26];
	int code;
} LinkNode, *LinkList;

typedef struct AWEBSITE
{
	double Sim;
	char name[10];
	double TFkd[100];//词频
	int code;
} WEBSITE;

long long int test_ans=0;

WEBSITE website[MAX];
LinkNode tree[5528343];
int tree_num=0;

long long int TNd[MAX]= {0}; //文档总词数
long long int TNkd[MAX][100]= {{0}}; //每个单词k在文档d出现的频次（即出现次数）

int DNk[100]= {0}; //即出现该单词的文档数
double IDFk[100]= {0}; //逆文档频率
int N=0;//网页数
char buffer[1000000000];

void read_keyword(LinkList *Root, char word[], int c)
{
	int step = 0;
	LinkList end = *Root;
	while(end!=NULL&&word[step]!='\0')
	{
		end=end->letter[word[step++]-'a'];
	}
	if(end!=NULL&&end->flag==true)
	{
		end->code=c;
	}
}

void read_dictionary(LinkList *Root, FILE *fin)
{
	char ch;
	int length=fread(buffer,sizeof(char),40000000,fin);
	int pos=0;
	LinkList end=*Root;
	while(pos<length)
	{
		ch=buffer[pos];
		if(ch>='a'&&ch<='z')
		{
			if(end->letter[ch-'a']==NULL)
			{
				//test_ans++;
				LinkList p=&tree[tree_num++];
				memset(p->letter,0,sizeof(p->letter));
				p->flag=false;
				p->code=-1;
				end->letter[ch-'a']=p;
			}
			end=end->letter[ch-'a'];
			pos++;
		}
		else
		{
			end->flag=true;
			pos++;
			end=*Root;
		}
	}
}

void read_stopwords(LinkList *Root, FILE *fin)
{
	char word[100];
	while (fscanf(fin,"%s",word)!=EOF)
	{
		LinkList end = *Root;
		for(int i=0; word[i]!='\0'&&end!=NULL; i++)
		{
			end=end->letter[word[i]-'a'];
		}
		if(end!=NULL) end->flag = false;
	}
}

void read_article(LinkList Root,FILE *fin,int num_k)
{
	int ch;
	int pos=0;
	bool flag_word=false; //record whether the string is a word to reduce time
	bool flag_end=true;//record the end of a website
	website[N].code=N+1;
	website[N].Sim=0;
	memset(website[N].TFkd,0,sizeof(website[N].TFkd));
	LinkList end=Root;
	int length=fread(buffer,sizeof(char),40000000,fin);

	while(pos<length)
	{
		ch=buffer[pos];
		if(flag_end)
		{
			flag_end=false;
			while(ch<'0'||ch>'9')
			{
				ch=buffer[++pos];
			}
			int temp_n=0;
			while((ch>='0'&&ch<='9')||ch=='-')
			{
				website[N].name[temp_n++]=ch;
				ch=buffer[++pos];
			}
			website[N].name[temp_n++]='\0';
			continue;
		}
		if(ch=='\f')//到下一个网页
		{
			for(int i=0; i<num_k; i++)
			{
				website[N].TFkd[i]=(double)TNkd[N][i]*100/(double)TNd[N];
				//printf("%lf\n",website[N].TFkd[i]);
			}
			flag_end=true;
			//printf("%lld\n",TNd[N]);
			N++;
			website[N].code=N+1;
			website[N].Sim=0;
			memset(website[N].TFkd,0,sizeof(website[N].TFkd));
		}
		if(ch>='A'&&ch<='Z')
		{
			ch+=32;
		}
		if(ch>='a'&&ch<='z')
		{
			flag_word=true;
			if(end!=NULL) end=end->letter[ch-'a'];
		}
		else
		{
			if (flag_word)//is a word
			{
				flag_word = false;
				if(end!=NULL&&end->flag==true)//can be found
				{
					TNd[N]++;//文档总词数+1
					if (end->code!=-1)//is a keyword
					{
						if(TNkd[N][end->code]==0)//该keyword未出现过
						{
							DNk[end->code]++;
						}
						TNkd[N][end->code]++;//keyword times++
					}
				}
				end=Root;
			}
		}
		pos++;
	}
	for(int i=0; i<num_k; i++)
	{
		website[N].TFkd[i]=(double)TNkd[N][i]*100/(double)TNd[N];
	}
	N++;
	for(int i=0; i<num_k; i++)
	{
		if (DNk[i]==0) IDFk[i] = 0;
		else IDFk[i]=log10((double)N/(double)(DNk[i]));
	}

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<num_k; j++)
		{
			website[i].Sim+=website[i].TFkd[j]*IDFk[j];
		}
	}
}


int Sim_Compare(const void *elem1,const void *elem2)
{
	WEBSITE *stu1 = (WEBSITE *)elem1;
	WEBSITE *stu2 = (WEBSITE *)elem2;
	if(((*stu1).Sim-(*stu2).Sim)>eps) return -1;
	else if(((*stu1).Sim-(*stu2).Sim)<-eps) return 1;
	else
	{
		if((*stu1).code-(*stu2).code>0) return 1;
		else return -1;
	}
}

void data_print(int num_k)
{
	printf("DNk:\n");
	for(int i=0; i<num_k; i++)
	{
		printf("%d ",DNk[i]);
	}
	printf("\n");
	printf("TFkd:\n");
	for(int i=0;i<N;i++)
	{
		printf("%s:",website[i].name);
		for(int j=0;j<num_k;j++)
		{
			printf("%.6lf ",website[i].TFkd[j]);
		}
		printf("\n");
	}
}

int main(int argc,char *argv[])
{
	
	LinkList Root = &tree[0];
	tree_num++;
	for (int i = 0; i < 26; i++)
	{
		Root->letter[i] = NULL;
	}
	Root->flag = false;
	Root->code = -1;
	FILE *fd, *fs, *fa;
	fd = fopen("dictionary.txt", "r");
	fs = fopen("stopwords.txt", "r");
	fa = fopen("article.txt", "r");
	read_dictionary(&Root, fd);
	//printf("%d\n",test_ans);
	read_stopwords(&Root, fs);
	for(int i=2; i<argc; i++)
	{
		read_keyword(&Root,argv[i],i-2);
	}
	int NUM=atoi(argv[1]);
	read_article(Root,fa,argc-2);
	//data_print(argc-2);
	qsort(website,N+1,sizeof(WEBSITE),Sim_Compare);
	
	

	for(int i=0; i<5; i++)
	{
		if(fabs(website[i].Sim)>eps) printf("%.6lf %d %s\n",website[i].Sim,website[i].code,website[i].name);
	}
	FILE *fp;
	fp = fopen("results.txt", "w");
	for(int i=0; i<NUM; i++)
	{
		if(fabs(website[i].Sim)>eps) fprintf(fp,"%.6lf %d %s\n",website[i].Sim,website[i].code,website[i].name);
	}
	return 0;
}
