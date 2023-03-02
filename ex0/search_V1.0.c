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


WEBSITE website[MAX];

long long int TNd=0;//文档总词数
long long int TNkd[100]= {0}; //每个单词k在文档d出现的频次（即出现次数）

int DNk[100]= {0}; //即出现该单词的文档数
double IDFk[100]= {0}; //逆文档频率
int N=0;//网页数


void read_keyword(LinkList *Root, char word[], int c)
{
	int step = 0;
	LinkList end = *Root;
	while(end!=NULL&&word[step]!='\0')
	{
		end=end->letter[word[step++]-'a'];
	}
	if (end!=NULL && end->flag == true)
	{
		end->code = c;
	}
}

void read_dictionary(LinkList *Root, FILE *fin)
{
	char word[50];
	while (fscanf(fin,"%s",word) != EOF)
	{
		LinkList end = *Root;
		//printf("%s\n",word);
		for (int i = 0; word[i] != '\0'; i++)
		{
			if (end->letter[word[i] - 'a'] == NULL)
			{
				LinkList p = (LinkList)malloc(sizeof(LinkNode));
				for (int i = 0; i < 26; i++)
				{
					p->letter[i] = NULL;
				}
				p->flag = false;
				p->code = -1;
				end->letter[word[i] - 'a'] = p;
			}
			end = end->letter[word[i] - 'a'];
		}
		if(word[0]!='\0') end->flag = true;
	}
}

void read_stopwords(LinkList *Root, FILE *fin)
{
	char word[100];
	while (fscanf(fin,"%s",word) != EOF)
	{
		//printf("%s\n",word);
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
	bool flag_word=false; //record whether the string is a word to reduce time
	char word[100];
	int temp_w=0;
	bool flag_end=true;//record the end of a website
	website[N].code=N+1;
	website[N].Sim=0;
	memset(website[N].TFkd,0,sizeof(website[N].TFkd));
	while ((ch=fgetc(fin))!=EOF)
	{
		//printf("%c",ch);
		if(flag_end)
		{
			while(!(ch>='0'&&ch<='9'))
			{
				ch = fgetc(fin);
			}
			//printf("BBBBrnmd\n");
			flag_end=false;
			int temp_n=0;
			while((ch>='0'&&ch<='9')||ch=='-')
			{
				//printf("%c",ch);
				website[N].name[temp_n++]=ch;
				ch = fgetc(fin);
			}
			website[N].name[temp_n++]='\0';
			//print("%s",website);
			continue;
		}

		if (ch=='\f')//到下一个网页
		{
			//printf("chaoAAAArnmd\n");
			for(int i=0; i<num_k; i++)
			{
				website[N].TFkd[i]=(double)TNkd[i]*100/(double)TNd;
			}
			flag_end=true;
			N++;
			/*for(int m=0;m<num_k;m++)
			{
				printf("%lf\n",website[N-1].TFkd[m]);
			}
			printf("\n");*/
			website[N].code=N+1;
			website[N].Sim=0;
			memset(website[N].TFkd,0,sizeof(website[N].TFkd));
			memset(TNkd,0,sizeof(TNkd));
			TNd=0;
			continue;
		}

		if(ch>='A'&&ch<='Z')
		{
			ch+=32;
		}
		if(ch>='a'&&ch<='z')
		{
			flag_word=true;
			word[temp_w++]=ch;
		}
		else
		{
			if (flag_word)//is a word
			{
				flag_word = false;
				word[temp_w]='\0';
				bool flag_dic=false; //to record whether the word can be found in the dictionary tree
				LinkList end = Root;
				for(int i=0; word[i]!='\0'&&end!=NULL; i++) //find word
				{
					end = end->letter[word[i]-'a'];
				}
				if(end!=NULL&&end->flag==true) 
				{
					flag_dic=true;
					//if(N==0) printf("%s\n",word);
				}
				if(flag_dic)//is included in dictionary tree
				{
					if(N==0&&TNd>370) printf("%s ",word);
					TNd++;//文档总词数+1
					if (end->code!=-1)//is a keyword
					{
						if(TNkd[end->code]==0)//该keyword未出现过
						{
							DNk[end->code]++;
						}
						TNkd[end->code]++;//keyword times++
					}
				}
				memset(word,'\0',sizeof(word));
				temp_w=0;
			}
		}
	}
	for(int i=0; i<num_k; i++)
	{
		website[N].TFkd[i]=(double)TNkd[i]*100/(double)TNd;
	}
	flag_end=true;
	N++;
	for (int i = 0; i < num_k; i++)
	{
		if (DNk[i]==0) IDFk[i] = 0;
		else IDFk[i]=log10((double)N/(double)(DNk[i]));
		//printf("%lf\n",IDFk[i]);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j=0; j<num_k; j++)
		{
			website[i].Sim+=website[i].TFkd[j]*IDFk[j];
		}
	}
}


int Sim_Compare(const void *elem1,const void *elem2)
{
	WEBSITE *stu1 = (WEBSITE *)elem1;
	WEBSITE *stu2 = (WEBSITE *)elem2;
	if(fabs((*stu1).Sim-(*stu2).Sim)<eps)
	{
		if((*stu1).code-(*stu2).code>0) return 1;
		else return -1;
	}
	else
	{
		if((*stu1).Sim-(*stu2).Sim>eps) return -1;
		else return 1;
	}
}

int main(int argc,char *argv[])
{
	//printf("AAAArnmd\n");
	LinkList Root = (LinkList)malloc(sizeof(LinkNode));
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

	read_stopwords(&Root, fs);
	//printf("AAAArnmd\n");
	for(int i=2; i<argc; i++)
	{
		//printf("%s\n",argv[i]);
		read_keyword(&Root,argv[i],i-2);
	}
	int NUM=atoi(argv[1]);
	//printf("AAAArnmd\n");
	read_article(Root,fa,argc-2);

	//printf("SuccessAAAArnmd\n");
	qsort(website,N+1,sizeof(WEBSITE),Sim_Compare);

	printf("%d\n",N);
	
	for(int i=0; i<5; i++)
	{
		if(fabs(website[i].Sim)>eps) printf("%.6lf %d %s\n",website[i].Sim,website[i].code,website[i].name);
	}
	
	FILE *fp;
	fp = fopen("results.txt", "w");
	for(int i=0; i<NUM; i++)
	{
		if(fabs(website[i].Sim)>eps) fprintf(fp,"%.6lf %d %s\n",website[i].Sim,website[i].code,website[i].name);
		//fprintf(fp,"%.6lf %d %s\n",website[i].Sim,website[i].code,website[i].name);
	}
	return 0;
}
