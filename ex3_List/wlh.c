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
	char code[1000];//��ŵ�һ�λ�õ�����
	char truecode[1000];//��ž�����������������
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
	struct loop *head;//����ͷ
	struct loop *mid;//Ϊ�ڵ�����ռ���м����
	struct loop *temp;//ɾ���ڵ����õı���
	mid = (struct loop *)malloc(sizeof(struct loop));
	head = mima;
	mima->letter = code[0]; //��ʼ����һ������
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
	mima->next = head;//���ɻ�
	//for (int i = 0; i < j; i++)
	//{
	//	printf("%c", code[i]);
	//}//������
	//printf("\n");
	struct loop *pointer;
	int o = 1;
	for (int i = 0; i < j; i++)
	{
		char c;
		if (i == 0)  //��һ����������
		{
			c = mima->next->letter;//ɾ����һ��
			mima->next = mima->next->next;
			for (int p = 1; p < c; p++)
			{
				mima = mima->next;
			}//�ߵ������ַ���ǰһ��
			truecode[c] = mima->next->letter;//�ŵ�����������������
			//mima->next=mima->next->next;
		}
		else if (i == j - 1)
		{
			truecode[mima->letter] = code[0];//���һ��ֱ�Ӵ�
		}
		else
		{
			temp = mima->next;//
			c = temp->letter;
			mima->next = mima->next->next;
//����һ����Ϊ���
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
	}//������
	return 0;
}
