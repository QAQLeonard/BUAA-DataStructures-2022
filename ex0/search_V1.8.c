//Vision 1.4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

//use dictionary tree to solve the problem
#define MAX 50000
#define eps 1e-8
int trie[4000010][26];
int flag_key[4000100][26];
long long int pos=0;

typedef struct AWEBSITE
{
	double Sim;
	char name[10];
	double TFkd[100];//词频
	int code;
} WEBSITE;

long long int test_ans=0;

WEBSITE website[MAX];

long long int TNd[MAX]= {0}; //文档总词数
long long int TNkd[MAX][100]= {{0}}; //每个单词k在文档d出现的频次（即出现次数）

int DNk[100]= {0}; //即出现该单词的文档数
double IDFk[100]= {0}; //逆文档频率
int N=0;//网页数
char buffer[1000000000];

void read_keyword(char word[], int c)
{
	int step = 0;
	int p=0;
	int p0=0;
	int n=0;
	while(word[step]!='\0'&&trie[p][word[step]-'a']!=0)
	{
		n=word[step]-'a';
		p0=p;
		p=trie[p][n];
		step++;
	}
	if(word[step]=='\0')
	{
		flag_key[p0][n]=c;
	}
}

void read_dictionary(FILE *fin)
{
	int length=fread(buffer,sizeof(char),40000000,fin);
	int i=0;
	int p0=0;
	int p=0;
	int n=0;
	while(i<length)
	{
		if((((buffer[i]|0x20)-0x61)^((buffer[i]|0x20)-0x7b))<0)
		{
			n=(buffer[i]&0x1f)-1;
			if(trie[p][n]==0)
			{
				pos++;
				trie[p][n]=pos;

			}
			p0=p;
			p=trie[p][n];
			i++;
		}
		else
		{
			if(p!=0) flag_key[p0][n]=-1;
			p=0;
			n=0;
			i++;
		}

	}
}

void read_stopwords(FILE *fin)
{
	char word[100];
	while (fscanf(fin,"%s",word)!=EOF)
	{
		int p=0;
		int p0=0;
		int n=0;
		int i=0;
		for(i=0; word[i]!='\0'; i++)
		{
			if(trie[p][(word[i]&0x1f)-1]==0)
			{
				p=0;
				break;
			}
			n=(word[i]&0x1f)-1;
			p0=p;
			p=trie[p][n];
		}
		if(word[i]=='\0')
		{
			flag_key[p0][n]=-2;
		}
	}
}

void read_article(FILE *fin,int num_k)
{
	int ch;
	int h=0;
	bool flag_word=false; //record whether the string is a word
	bool flag_found=true;
	bool flag_end=true;//record the end of a website
	website[N].code=N+1;
	website[N].Sim=0;
	memset(website[N].TFkd,0,sizeof(website[N].TFkd));
	int length=fread(buffer,sizeof(char),40000000,fin);
	int p=0;
	int p0=0;
	int n=0;
	while(h<length)
	{
		ch=buffer[h];
		if(flag_end)
		{
			flag_end=false;
			while(ch<'0'||ch>'9')
			{
				ch=buffer[++h];
			}
			int temp_n=0;
			while((ch>='0'&&ch<='9')||ch=='-')
			{
				website[N].name[temp_n++]=ch;
				ch=buffer[++h];
			}
			website[N].name[temp_n++]='\0';
			continue;
		}
		if(ch=='\f')//到下一个网页
		{
			for(int i=0; i<num_k; i++)
			{
				website[N].TFkd[i]=(double)TNkd[N][i]*100/(double)TNd[N];
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
		if((((ch|0x20)-0x61)^((ch|0x20)-0x7b))<0)
		{
			flag_word=true;
			if(trie[p][(ch&0x1f)-1]==0) flag_found=false;
			if(flag_found)
			{
				n=(ch&0x1f)-1;
				p0=p;
				p=trie[p][n];
			}
		}
		else
		{
			if(flag_word)//is a word
			{
				flag_word = false;
				if(flag_found&&flag_key[p0][n]!=-2&&flag_key[p0][n]!=0)
				{
					TNd[N]++;//文档总词数+1
					int c=flag_key[p0][n];
					if(c!=0)//is a keyword
					{
						if(TNkd[N][c-1]==0)//该keyword未出现过
						{
							DNk[c-1]++;
						}
						TNkd[N][c-1]++;//keyword times++
					}
				}
				flag_found=true;
				p=0;
				n=0;
				p0=0;
			}
		}
		h++;
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

/*void data_print(int num_k)
{
	printf("DNk:\n");
	for(int i=0; i<num_k; i++)
	{
		printf("%d ",DNk[i]);
	}
	printf("\n");
	printf("TFkd:\n");
	for(int i=0; i<N; i++)
	{
		printf("%s:",website[i].name);
		for(int j=0; j<num_k; j++)
		{
			printf("%.6lf ",website[i].TFkd[j]);
		}
		printf("\n");
	}
}*/

int main(int argc,char *argv[])
{

	FILE *fd, *fs, *fa;
	fd = fopen("dictionary.txt", "r");
	fs = fopen("stopwords.txt", "r");
	fa = fopen("article.txt", "r");
	read_dictionary(fd);

	//printf("%lld\n",test_ans);
	read_stopwords(fs);
	for(int i=2; i<argc; i++)
	{
		read_keyword(argv[i],i-1);
	}
	int NUM=atoi(argv[1]);
	read_article(fa,argc-2);
	//printf("%d\n",N);
	//printf("%lld\n",TNd[0]);

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
