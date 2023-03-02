#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma GCC optimize ("O3")
#pragma once
#pragma pack (16)
char s[6380000];//�ֵ��ж����ַ���ɵ��ַ���
char s2[6380000];//ͣ�ô��ж����ַ���ɵ��ַ���
char s3[6380000];//�����ж����ַ���ɵ��ַ���
int web_sum = 1;//��վ�ĸ���
int keysum = 0;//�ؼ��ʵĸ���
char everyword[30];//����������getword�����ĵ���
int flag3[50000];//��¼ÿ���ؼ�����ÿ���ĵ����ǲ��ǵ�һ�γ��ֵ�flag��������¼DNK
int temp = 0, id = 0, p = 0, q = 0, i = 0;

struct keytimes  //ÿһ���ؼ��ʵ��������
{
	double tfkd[50000];//ÿһ���ؼ���i�ڵ�j���ĵ��е�TFDK
	int tnkd[50000];//ÿһ���ؼ���I�ڵ�J���ĵ��е�TNDK
	double idfk;//ÿһ���ؼ��ʵ�IDFK
	int apperatimes;//ÿһ���ؼ��ʣ���������ĵ��ĸ���
} thekey[2000];

struct website  //ÿһ����վ�����������
{
	char name[100];//��վ��
	double sim;//��վSIM
	int webpage;//��վ���
	int wordsum;//��վ�к��е��ʵĸ���
} web[10000];

struct mydict
{
	int son[26];
	int flag;
} trie[1500100];//�ֵ���


void insertdict()
{
	for ( i = 0; s[i]; i++)  //s[i]��Ϊ������
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
			if (p != 0)////�о��߼������⣿��Ӧ����-1�������ֵ���ĵ�����ȫ�ֵĻ�Ĭ����0.��longΪ����Ĭ��ÿ������0����l,lo,lon�����ǵ���
			{
				trie[p].flag = -1;//0�������ֵ��еĵ���
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
		//����dictionary���и�long��stopwords���и�longest�������Ļ���p�ͻ�ͣ�ڡ�g����λ�ã�
		//���ѡ�g����flag����0��Ȼ����ʵ��stopwords����û��long		
		else
		{
			if (p != 0)
			{
				trie[p].flag = 0;//-1�����Ǳ�ͣ���˵ĵ���
			}
			p = 0;
		}
	}
}

void insertkey(char *argv[], int i)
{
	int l = strlen(argv[i]);//����ĳ�argv[i][j]!='\0'
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
				trie[p].flag = ++keysum;//flag��Ϊ0��-1���ǹؼ��ʣ���flag��ֵ������Ӧ�Ĺؼ��ʵı��
			}
			p = 0;
		}
	}
}

int judgeword(char everyword[], int l)  //�ж���getword��ȡ�Ĵ��ǲ��ǹؼ��ʣ��ǵĻ��ͷ��ر��
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

int getword(char everyword[], FILE *fp)  //��article�ĵ���һ��������everyword��
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
		else if (c == '\f')    //�������ĵ�������Ҫ���õ���������ʵ�һ�γ��ֵ�flag����
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
	FILE *fp;//�������⼸���ļ�
	freopen("dictionary.txt", "rb", stdin);
	fread(s,  sizeof(char), 6375867, stdin);
	freopen("stopwords.txt", "rb", stdin);
	fread(s2, sizeof(char), 6375867, stdin);
	insertdict();//�����ֵ���
	temp = id = p = 0;
	insertstop();//����ͣ�ô���
	fp = fopen("article.txt", "r");
	temp = id = p = 0;
	for (int a = 2; a < argc; a++)  //�ѹؼ��ʲ����ȥ
	{
		insertkey(argv, i);
	}
	fgets(web[0].name, 10, fp);//�ѵ�һ�����ֶ���ȥ
	while (getword(everyword, fp) != EOF)
	{
		if (judgeword(everyword, strlen(everyword)) != 0)   //�ж�һ�����ǲ����ֵ�����ĵ���
		{
			if (judgeword(everyword, strlen(everyword)) > 0)  //�ǵĻ������ж��ǲ��ǹؼ���
			{
				int sign = judgeword(everyword, strlen(everyword)) - 1;//sign��0��ʼ
				if (flag3[sign] == 0)
				{
					thekey[sign].apperatimes++;//��¼�������������ĵ��г��ֹ�
					flag3[sign] = 1;//���ֹ����´ξͲ����ˣ������ظ�
				}
				thekey[sign].tnkd[web_sum]++;//tnd�������thekeysign��websum�������ͼ���
			}
			web[web_sum].wordsum++;//ֻҪ���ֵ���ĵ��ʣ��ĵ����������ۼ�
		}
	}
	for (int a = 0; a < web_sum; a++)  //��Ÿ�ֵ
	{
		web[a].webpage = a;
	}
	for (int a = 0; a < keysum; a++)  //����ÿ������k���ĵ�j���µ�TFKD
	{
		for (int b = 0; b < web_sum; b++)
		{
			if (web[b].wordsum == 0)  //���ĵ�ֱ�Ӿ�����
			{
				thekey[a].tfkd[b] = 0;
			}
			else
			{
				thekey[a].tfkd[b] = (double)thekey[a].tnkd[b] / (double)web[b].wordsum * 100;//TFKD����
			}
		}
	}
	for (int a = 0; a < keysum; a++)  //ÿ�����ʵ�IDFK����
	{
		thekey[a].idfk = log10((double)web_sum / (double)thekey[i].apperatimes);
	}
	int use = 0;//�ж�SIM����ĸ���
	for (int a = 0; a < web_sum; a++)  //˫ѭ������ÿ����վ��SIM
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
	qsort(web, web_sum + 1, sizeof(web[0]), cmp);//����Ȼ�����
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
