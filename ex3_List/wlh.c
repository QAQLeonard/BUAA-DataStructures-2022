#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct loop
{
	char letter;
	struct loop *next;
};
int letter[1000];

int main()
{
	//FILE *in, *out;
	//in = fopen("in.txt", "r");
	//out = fopen("in_crpyt.txt", "w");
	char str[1000];
	char code[1000];//存放第一次获得的密码
	char truecode[1000];//存放经过加密真正的密码
	gets(str);
	int len = strlen(str);
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (letter[str[i]] == 0)
		{
			letter[str[i]] = 1;
			code[j++] = str[i];
		}
	}
	//code[j]='\0';
	//printf("%s\n",code);
	for (int k = 32; k <= 126; k++)
	{
		if (letter[k] == 0)
		{
			code[j++] = k;
		}
	}
	code[j] = '\0';
	printf("%s\n",code);
	struct loop *mima = (struct loop *)malloc(sizeof(struct loop));
	struct loop *head;//链表头
	struct loop *mid;//为节点申请空间的中间变量
	struct loop *temp;//删除节点所用的变量
	mid = (struct loop *)malloc(sizeof(struct loop));
	head = mima;
	mima->letter = code[0]; //初始化第一个密码
	mima->next = mid;
	mima = mima->next;
	for (int i = 1; i < j - 1; i++)
	{
		mid = (struct loop *)malloc(sizeof(struct loop));
		mima->letter = code[i];
		mima->next = mid;
		mima = mima->next;
	}

	mima->letter = code[j - 1];
	mima->next = head;//连成环
	//for (int i = 0; i < j; i++)
	//{
	//	printf("%c", code[i]);
	//}//测试用
	//printf("\n");
	struct loop *pointer;
	int o = 1;
	for (int i = 0; i < j; i++)
	{
		char c;
		if (i == 0)  //第一个单独处理
		{
			c = mima->next->letter;//删除第一个
			mima->next = mima->next->next;
			for (int p = 1; p < c; p++)
			{
				mima = mima->next;
			}//走到加密字符的前一个
			truecode[c] = mima->next->letter;//放到真正的密码数组中
			//mima->next=mima->next->next;
		}
		else if (i == j - 1)
		{
			truecode[mima->letter] = code[0];//最后一个直接存
		}
		else
		{
			temp = mima->next;//
			c = temp->letter;
			mima->next = mima->next->next;
//从下一个作为起点
			for (int p = 1; p < c; p++)
			{
				mima = mima->next;
			}
			temp = mima->next;
			truecode[c] = temp->letter;
			temp = NULL;
		}
	};

	truecode[127]='\0';
	for (int i = 32; i <= 126; i++)
	{
		printf("%c", truecode[i]);
	}//测试用
	return 0;
}
