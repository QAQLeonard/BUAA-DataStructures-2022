#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma GCC optimize ("O3")
#pragma once
#pragma pack (16)
char s[6380000];//字典中读入字符组成的字符串
char s2[6380000];//停用词中读入字符组成的字符串
char s3[6380000];//文章中读入字符组成的字符串
int web_sum = 1;//网站的个数
int keysum = 0;//关键词的个数
char everyword[30];//从文章中用getword读到的单词
int flag3[50000];//记录每个关键词在每个文档中是不是第一次出现的flag，用来记录DNK
int temp = 0, id = 0, p = 0, q = 0, i = 0;

struct keytimes  //每一个关键词的相关数据
{
	double tfkd[50000];//每一个关键词i在第j个文档中的TFDK
	int tnkd[50000];//每一个关键词I在第J个文档中的TNDK
	double idfk;//每一个关键词的IDFK
	int apperatimes;//每一个关键词，含有其的文档的个数
} thekey[2000];

struct website  //每一个网站及其相关数据
{
	char name[100];//网站名
	double sim;//网站SIM
	int webpage;//网站序号
	int wordsum;//网站中含有单词的个数
} web[10000];

struct mydict
{
	int son[26];
	int flag;
} trie[1500100];//字典树


void insertdict()
{
	for ( i = 0; s[i]; i++)  //s[i]不为结束符
	{
		if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
		{
			temp = s[i] - 'a';
			if (!trie[p].son[temp]) 
			{
				trie[p].son[temp] = ++id;
				//printf("yes!");
			}
			p = trie[p].son[temp];
		}
		else
		{
			if (p != 0)////感觉逻辑有问题？不应该是-1代表是字典里的单词吗？全局的话默认是0.以long为例，默认每个都是0，但l,lo,lon都不是单词
			{
				trie[p].flag = -1;//0代表是字典中的单词
			}
			p = 0;
		}
	}
}

void insertstop()
{
	for ( i = 0; s2[i]; i++)
	{
		if ((s2[i] >= 'A' && s2[i] <= 'Z') || (s2[i] >= 'a' && s2[i] <= 'z'))
		{
			temp = (s2[i] <= 'Z') ? s2[i] - 'A' : s2[i] - 'a';
			if (trie[p].son[temp] != 0)
				p = trie[p].son[temp];
		}
		//假设dictionary里有个long，stopwords里有个longest，这样的话，p就会停在‘g’的位置，
		//最后把‘g’的flag置了0，然而事实上stopwords里面没有long		
		else
		{
			if (p != 0)
			{
				trie[p].flag = 0;//-1代表是被停用了的单词
			}
			p = 0;
		}
	}
}

void insertkey(char *argv[], int i)
{
	int l = strlen(argv[i]);//建议改成argv[i][j]!='\0'
	for ( int j = 0; j < l; j++)
	{
		if ((argv[i][j] >= 'A' && argv[i][j] <= 'Z') || (argv[i][j] >= 'a' && argv[i][j] <= 'z'))
		{
			temp = (argv[i][j] <= 'Z') ? argv[i][j] - 'A' : argv[i][j] - 'a';
			if (trie[p].son[temp] != 0)
				p = trie[p].son[temp];
		}
		else
		{
			if (p != 0 && trie[p].flag == 0)
			{
				trie[p].flag = ++keysum;//flag不为0或-1的是关键词，其flag的值是他对应的关键词的编号
			}
			p = 0;
		}
	}
}

int judgeword(char everyword[], int l)  //判断用getword提取的词是不是关键词，是的话就返回编号
{
	int q = 0;
	int n;
	for (int a = 0; a < l; a++)
	{
		n = everyword[a] - 'a';
		if (!trie[q].son[n])
		{
			return 0;
		}
		q = trie[q].son[n];
	}
	return trie[q].flag;
}

int getword(char everyword[], FILE *fp)  //把article的单词一个个读进everyword里
{
	int c;
	int y = 0;
	char take[5];
	while ((c = fgetc(fp)) != EOF)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c = c + 'Z' - 'A';
		}
		else if (c == '\f')    //更换了文档，所以要重置掉这个代表单词第一次出现的flag数组
		{
			memset(flag3, 0, sizeof(flag3));
			web_sum++;
			fgets(take, 5, fp);///???
			fgets(web[web_sum].name, 10, fp);
		}
		else if (c <= 'z' && c >= 'a')
		{
			everyword[y++] = c;
		}
		else if (y > 0)
			break;
	}
	everyword[y] = '\0';
	return c;
}

int cmp( const void *a, const void *b )
{
	struct website *c = (struct website *)a;
	struct website *d = (struct website *)b;
	if (c->sim - d->sim < 1e-8)
	{
		return 1;
	}
	else if (c->sim - d->sim > 1e-8)
	{
		return -1;
	}
	else
		return c->webpage - d->webpage;
}

int whichless(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;//挨个打开这几个文件
	freopen("dictionary.txt", "rb", stdin);
	fread(s,  sizeof(char), 6375867, stdin);
	freopen("stopwords.txt", "rb", stdin);
	fread(s2, sizeof(char), 6375867, stdin);
	insertdict();//构建字典树
	temp = id = p = 0;
	insertstop();//构建停用词树
	fp = fopen("article.txt", "r");
	temp = id = p = 0;
	for (int a = 2; a < argc; a++)  //把关键词插入进去
	{
		insertkey(argv, i);
	}
	fgets(web[0].name, 10, fp);//把第一个名字读进去
	while (getword(everyword, fp) != EOF)
	{
		if (judgeword(everyword, strlen(everyword)) != 0)   //判断一下子是不是字典里面的单词
		{
			if (judgeword(everyword, strlen(everyword)) > 0)  //是的话，再判断是不是关键词
			{
				int sign = judgeword(everyword, strlen(everyword)) - 1;//sign从0开始
				if (flag3[sign] == 0)
				{
					thekey[sign].apperatimes++;//记录这个单词在这个文档中出现过
					flag3[sign] = 1;//出现过了下次就不记了，避免重复
				}
				thekey[sign].tnkd[web_sum]++;//tnd就让这个thekeysign对websum遍历做和即可
			}
			web[web_sum].wordsum++;//只要是字典里的单词，文档单词数均累计
		}
	}
	for (int a = 0; a < web_sum; a++)  //序号赋值
	{
		web[a].webpage = a;
	}
	for (int a = 0; a < keysum; a++)  //计算每个单词k在文档j的下的TFKD
	{
		for (int b = 0; b < web_sum; b++)
		{
			if (web[b].wordsum == 0)  //空文档直接就是零
			{
				thekey[a].tfkd[b] = 0;
			}
			else
			{
				thekey[a].tfkd[b] = (double)thekey[a].tnkd[b] / (double)web[b].wordsum * 100;//TFKD计算
			}
		}
	}
	for (int a = 0; a < keysum; a++)  //每个单词的IDFK计算
	{
		thekey[a].idfk = log10((double)web_sum / (double)thekey[i].apperatimes);
	}
	int use = 0;//判断SIM非零的个数
	for (int a = 0; a < web_sum; a++)  //双循环计算每个网站的SIM
	{
		for (int b = 0; b < keysum; b++)
		{
			web[a].sim += thekey[b].tfkd[a] * thekey[b].idfk;
		}
		if (web[a].sim > 1e-10)
		{
			use++;
		}
	}
	qsort(web, web_sum + 1, sizeof(web[0]), cmp);//排序，然后输出
	for (int a = 0; a < whichless(5, use); a++)
	{
		printf("%.6lf %d %s", web[a].sim, web[a].webpage + 1, web[a].name);
	}
	freopen("results.txt", "w", stdout);
	for (i = 0; i < whichless(atoi(argv[1]), use); i++)
	{
		printf("%.6lf %d %s", web[i].sim, web[i].webpage + 1, web[i].name);
	}
	fclose(stdout);
	return 0;
}
