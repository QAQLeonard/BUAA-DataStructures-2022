#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma GCC optimize ("O3")
#pragma once
#pragma pack (16)
char s[63800000];//�ֵ��ж����ַ���ɵ��ַ���
char s2[63800000];//ͣ�ô��ж����ַ���ɵ��ַ���
char s3[63800000];//�����ж����ַ���ɵ��ַ���
int web_sum = 0;//��վ�ĸ���
int keysum = 0;//�ؼ��ʵĸ���
char everyword[30];//����������getword�����ĵ���
int temp = 0, p = 0, q = 0, i = 0;
int id = 0;

struct keytimes  //ÿһ���ؼ��ʵ��������
{
	double tfkd[500000];//ÿһ���ؼ���i�ڵ�j���ĵ��е�TFDK
	int tnkd[500000];//ÿһ���ؼ���I�ڵ�J���ĵ��е�TNDK
	double idfk;//ÿһ���ؼ��ʵ�IDFK
	int apperatimes;//ÿһ���ؼ��ʣ���������ĵ��ĸ���
} thekey[200];

struct website  //ÿһ����վ�����������
{
	char name[100];//��վ��
	double sim;//��վSIM
	int webpage;//��վ���
	int wordsum;//��վ�к��е��ʵĸ���
} web[1000000];

struct mydict
{
	int son[26];
	int flag;
	int length;
} trie[1128347];//�ֵ���


void insertdict(int len)
{
	int walk = 0;
	for ( i = 0; i < len; i++)   //s[i]��Ϊ������
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
				trie[p].flag = -1;//-1�������ֵ��еĵ���
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
				trie[p].flag = 0;//0�����Ǳ�ͣ���˵ĵ���
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
		trie[p].flag = ++keysum; //�ϸ�ؼ��ʰ�˳����flag
	}
}

int judgeword(char everyword[])  //�ж���getword��ȡ�Ĵ��ǲ��ǹؼ��ʣ��ǵĻ��ͷ��ر��
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
	FILE *fp; //�������⼸���ļ�
	freopen("dictionary.txt", "r", stdin);
	int len = fread(s,  sizeof(char), 6375867, stdin);
	s[len] = '\0';
	insertdict(len);//�����ֵ���
	freopen("stopwords.txt", "r", stdin);
	len = fread(s2, sizeof(char), 6375867, stdin);
	s2[len] = '\0';
	temp = id = p = 0;
	insertstop(len);//����ͣ�ô���
	fp = fopen("article.txt", "r");
	for (int a = 2; a < argc; a++)  //�ѹؼ��ʲ����ȥ
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
			web[i].webpage = i + 1; //i���ĵ����
			endover = 1;
			continue;
		}//���ĵ����ִ��article.name
		else
		{
			for (j = 0; s3[j]; j++)   //һ���ַ�һ���ַ�������ɵ���
			{
				if ((s3[j] >= 'A' && s3[j] <= 'Z') || (s3[j] >= 'a' && s3[j] <= 'z'))
				{
					everyword[k] = (char)tolower(s3[j]);
					k++;
				}
				else if (s3[j] == '\f')     //���ĵ�����
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
						if (sign == 0)   //�����ڻ�����ͣ�ô�
						{
							continue;
						}
						else if (sign == -1)     //�ֵ��
						{
							web[i].wordsum++;
						}
						else if (sign > 0)     //�ؼ���
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
	for (int a = 1; a <= keysum; a++)  //����ÿ������k���ĵ�j���µ�TFKD
	{
		for (int b = 0; b <= web_sum; b++)
		{
			if (web[b].wordsum == 0)  //���ĵ�ֱ�Ӿ�����
			{
				thekey[a].tfkd[b] = 0;
			}
			else
			{
				thekey[a].tfkd[b] = (double)thekey[a].tnkd[b] / (double)web[b].wordsum * 100;//TFKD����
			}
			//	printf("key:%d article:%d TN:%d sum:%d TF:%.6f\n", a, b, thekey[a].tnkd[b], web[b].wordsum, thekey[a].tfkd[b]);
//			printf("%.6lf\n", thekey[a].tfkd[b]);

		}

	}
	for (int a = 1; a <= keysum; a++)  //ÿ�����ʵ�IDFK����
	{
		if (thekey[a].apperatimes == 0 || web_sum + 1 == thekey[a].apperatimes)
		{
			thekey[a].idfk = 0;
		}
		else
			thekey[a].idfk = log10((double)(web_sum + 1) / (double)thekey[a].apperatimes);
		//	printf("%.6lf\n", thekey[a].idfk);
	}
	int use = 0;//�ж�SIM����ĸ���
	for ( i = 0; i <= web_sum; i++)  //˫ѭ������ÿ����վ��SIM
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
	qsort(web, web_sum + 1, sizeof(web[0]), cmp); //����Ȼ�����
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
