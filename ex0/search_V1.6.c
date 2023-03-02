//Vision 1.6，使用数组储存字典树
//Fail. The array is too large

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

//use dictionary tree to solve the problem
#define MAX_TREE 1000000
#define MAX 100000
#define eps 1e-8
typedef struct Node
{
	bool flag;
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

LinkNode tree[55283430];
int tree_num=0;

long long int TNd[MAX]= {0}; //文档总词数
long long int TNkd[MAX][100]= {{0}}; //每个单词k在文档d出现的频次（即出现次数）

int DNk[100]= {0}; //即出现该单词的文档数
double IDFk[100]= {0}; //逆文档频率
int N=0;//网页数
char buffer[1000000000];

void read_keyword(char word[], int c)
{
	int step = 0;
	long int end=0;
	while(end<MAX_TREE&&word[step]!='\0')
	{
		end=26*end+word[step]-'a'+1;
	}
	if(tree[end].flag)
	{
		tree[end].code=c;
	}
}

void read_dictionary(FILE *fin)
{
	char ch;
	int length=fread(buffer,sizeof(char),40000000,fin);
	int pos=0;
	int end=0;
	while(pos<length)
	{
		ch=buffer[pos];
		if(ch>='a'&&ch<='z')
		{
			end=26*end+ch-'a'+1;
			pos++;
		}
		else
		{
			if(end!=0) 
			{
				tree[end].flag=true;
				test_ans++;
				printf("success %lld %d\n",test_ans,end);
			}
			end=0;
			pos++;
		}
	}
}

void read_stopwords(FILE *fin)
{
	char word[100];
	while (fscanf(fin,"%s",word)!=EOF)
	{
		int end = 0;
		for(int i=0; word[i]!='\0'&&end<MAX_TREE; i++)
		{
			end=26*end+word[i]-'a'+1;
		}
		if(end<MAX_TREE) tree[end].flag=false;
	}
}

void read_article(FILE *fin,int num_k)
{
	int ch;
	int pos=0;
	bool flag_word=false; //record whether the string is a word to reduce time
	bool flag_end=true;//record the end of a website
	website[N].code=N+1;
	website[N].Sim=0;
	memset(website[N].TFkd,0,sizeof(website[N].TFkd));
	int end=0;
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
			if(end<MAX_TREE) end=26*end+ch-'a'+1;
		}
		else
		{
			if(flag_word)//is a word
			{
				flag_word=false;
				if(end<MAX_TREE&&tree[end].flag==true)//can be found
				{
					TNd[N]++;//文档总词数+1
					if (tree[end].code!=0)//is a keyword
					{
						if(TNkd[N][tree[end].code-1]==0)//该keyword未出现过
						{
							DNk[tree[end].code-1]++;
						}
						TNkd[N][tree[end].code-1]++;//keyword times++
					}
				}
				end=0;
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
	memset(tree,0,sizeof(tree));
	FILE *fd, *fs, *fa;
	fd = fopen("dictionary.txt", "r");
	fs = fopen("stopwords.txt", "r");
	fa = fopen("article.txt", "r");
	read_dictionary(fd);
	printf("success\n");
	read_stopwords(fs);
	for(int i=2; i<argc; i++)
	{
		read_keyword(argv[i],i-1);
	}
	int NUM=atoi(argv[1]);
	read_article(fa,argc-2);
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
