#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma GCC optimize ("O3")
#pragma once
#pragma pack (16)
char s[63800000];//字典中读入字符组成的字符串
char s2[63800000];//停用词中读入字符组成的字符串
char s3[63800000];//文章中读入字符组成的字符串
int web_sum = 0;//网站的个数
int keysum = 0;//关键词的个数
char everyword[30];//从文章中用getword读到的单词
int temp = 0, p = 0, q = 0, i = 0;
int id = 0;

struct keytimes  //每一个关键词的相关数据
{
	double tfkd[500000];//每一个关键词i在第j个文档中的TFDK
	int tnkd[500000];//每一个关键词I在第J个文档中的TNDK
	double idfk;//每一个关键词的IDFK
	int apperatimes;//每一个关键词，含有其的文档的个数
} thekey[200];

struct website  //每一个网站及其相关数据
{
	char name[100];//网站名
	double sim;//网站SIM
	int webpage;//网站序号
	int wordsum;//网站中含有单词的个数
} web[1000000];

struct mydict
{
	int son[26];
	int flag;
	int length;
} trie[1128347];//字典树


void insertdict(int len)
{
	int walk = 0;
	for ( i = 0; i < len; i++)   //s[i]不为结束符
	{
		if ((s[i] >= 'a' && s[i] <= 'z'))
		{
			temp = s[i] - 'a';
			if (!trie[p].son[temp])
				trie[p].son[temp] = ++id;
			p = trie[p].son[temp];
			walk++;
		}
		else
		{
			if (p != 0)
			{
				trie[p].flag = -1;//-1代表是字典中的单词
				trie[p].length = walk;
			}
			p = 0;
			walk = 0;
		}
	}
}

void insertstop(int len)
{
	int walk = 0;
	for ( i = 0; i < len; i++)
	{
		if ((s2[i] >= 'a' && s2[i] <= 'z'))
		{
			temp = s2[i] - 'a'; //long longest
			if (trie[p].son[temp] != 0)
				p = trie[p].son[temp];
			walk++;
		}
		else
		{
			if (p != 0 && walk == trie[p].length)
			{
				trie[p].flag = 0;//0代表是被停用了的单词
			}
			p = 0;
			walk = 0;
		}
	}
}

void insertkey(char *str)
{
	int p = 0, n, i;
	for (i = 0; str[i]; i++)
	{
		n = str[i] - 'a';
		if (!trie[p].son[n])
		{
			break;
		}
		p = trie[p].son[n];
	}
	if (p != 0 && trie[p].flag == -1)
	{
		trie[p].flag = ++keysum; //合格关键词按顺序设flag
	}
}

int judgeword(char everyword[])  //判断用getword提取的词是不是关键词，是的话就返回编号
{
	int q = 0;
	int n;
	for (int a = 0; everyword[a]; a++)
	{
		n = everyword[a] - 'a';
		if (!trie[q].son[n])
		{
			return 0;
		}
		q = trie[q].son[n];
	}
//	printf("%d\n", trie[q].flag);
	return trie[q].flag;
}

int cmp( const void *a, const void *b )
{
	struct website *c = (struct website *)a;
	struct website *d = (struct website *)b;
	if (d->sim - c->sim > 1e-6)
	{
		return 1;
	}
	else if (c->sim - d->sim > 1e-6)
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
	int endover = 0;
	int j = 0, k = 0, sign = 0;
	FILE *fp; //挨个打开这几个文件
	freopen("dictionary.txt", "r", stdin);
	int len = fread(s,  sizeof(char), 6375867, stdin);
	s[len] = '\0';
	insertdict(len);//构建字典树
	freopen("stopwords.txt", "r", stdin);
	len = fread(s2, sizeof(char), 6375867, stdin);
	s2[len] = '\0';
	temp = id = p = 0;
	insertstop(len);//构建停用词树
	fp = fopen("article.txt", "r");
	for (int a = 2; a < argc; a++)  //把关键词插入进去
	{
		insertkey(argv[a]);
	}
	i = 0;
	j = 0;
	k = 0;
	while (fgets(s3, 6375867, fp) != NULL)
	{
		if (endover == 0)
		{
			strcpy(web[i].name, s3);
			web[i].webpage = i + 1; //i是文档编号
			endover = 1;
			continue;
		}//将文档名字存进article.name
		else
		{
			for (j = 0; s3[j]; j++)   //一个字符一个字符读，变成单词
			{
				if ((s3[j] >= 'A' && s3[j] <= 'Z') || (s3[j] >= 'a' && s3[j] <= 'z'))
				{
					everyword[k] = (char)tolower(s3[j]);
					k++;
				}
				else if (s3[j] == '\f')     //该文档结束
				{
					endover = 0;
					i++;
					k = 0;
					break;
				}
				else
				{
					if (k != 0)
					{
						everyword[k] = '\0';
						sign = judgeword(everyword);
						k = 0;
						if (sign == 0)   //不存在或者是停用词
						{
							continue;
						}
						else if (sign == -1)     //字典词
						{
							web[i].wordsum++;
						}
						else if (sign > 0)     //关键词
						{
							web[i].wordsum++;
							if (thekey[sign].tnkd[i] == 0)
							{
								thekey[sign].apperatimes++;
							}
							thekey[sign].tnkd[i]++;
						}
						sign = -3;
					}

				}
			}
		}
	}
	//printf("%d\n", thekey[1].apperatimes);
	//printf("%d", i);
	web_sum = i;
	for (int a = 1; a <= keysum; a++)  //计算每个单词k在文档j的下的TFKD
	{
		for (int b = 0; b <= web_sum; b++)
		{
			if (web[b].wordsum == 0)  //空文档直接就是零
			{
				thekey[a].tfkd[b] = 0;
			}
			else
			{
				thekey[a].tfkd[b] = (double)thekey[a].tnkd[b] / (double)web[b].wordsum * 100;//TFKD计算
			}
			//	printf("key:%d article:%d TN:%d sum:%d TF:%.6f\n", a, b, thekey[a].tnkd[b], web[b].wordsum, thekey[a].tfkd[b]);
//			printf("%.6lf\n", thekey[a].tfkd[b]);

		}

	}
	for (int a = 1; a <= keysum; a++)  //每个单词的IDFK计算
	{
		if (thekey[a].apperatimes == 0 || web_sum + 1 == thekey[a].apperatimes)
		{
			thekey[a].idfk = 0;
		}
		else
			thekey[a].idfk = log10((double)(web_sum + 1) / (double)thekey[a].apperatimes);
		//	printf("%.6lf\n", thekey[a].idfk);
	}
	int use = 0;//判断SIM非零的个数
	for ( i = 0; i <= web_sum; i++)  //双循环计算每个网站的SIM
	{
		for (int b = 1; b <= keysum; b++)
		{
			web[i].sim += thekey[b].tfkd[i] * thekey[b].idfk;
		}
		if (web[i].sim > 1e-10)
		{
			use++;
		}
	}
	qsort(web, web_sum + 1, sizeof(web[0]), cmp); //排序，然后输出
	for (i = 0; i < whichless(5, use); i++)
	{
		printf("%.6lf %d %s", web[i].sim, web[i].webpage, web[i].name);
	}
	freopen("results.txt", "w", stdout);
	for (i = 0; i < whichless(atoi(argv[1]), use); i++)
	{
		printf("%.6lf %d %s", web[i].sim, web[i].webpage, web[i].name);
	}
	fclose(stdout);
	return 0;
}
