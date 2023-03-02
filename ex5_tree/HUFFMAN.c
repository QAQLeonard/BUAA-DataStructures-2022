//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

typedef struct tnode  			//Huffman树结构
{
	char c;
	int weight;		//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} TreeNode,*Tree;


int Ccount[128]= {0};		//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数
Tree Root=NULL; 	//Huffman树的根节点
char HCode[128][MAXSIZE]= {{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式）
int Step=0;			//实验步骤
FILE *Src, *Obj;

void statCount();		//步骤1：统计文件中字符频率
void createHTree();		//步骤2：创建一个Huffman树，根节点为Root
void makeHCode();		//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 		//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();			//输出步骤1的结果
void print2(Tree p);	//输出步骤2的结果
void print3();			//输出步骤3的结果
void print4();			//输出步骤4的结果

void INSERT_TREE(Tree Root, int i);
Tree CREATE_TREE(int i);
void PREORDER_TREE(Tree Root,int top,char HUFFMANCODE[],int code);

int main()
{
	if((Src=fopen("input.txt","r"))==NULL)
	{
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL)
	{
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);		//输入当前实验步骤

	statCount();			//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1)?print1():1;   	//输出实验步骤1结果
	createHTree();			//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2)?print2(Root):2; 	//输出实验步骤2结果
	makeHCode();		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3)?print3():3;   	//输出实验步骤3结果
	(Step>=4)?atoHZIP(),print4():4;//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果

	fclose(Src);
	fclose(Obj);
	return 0;
}

//--------------------------------------------------------------------------------------------
//【实验步骤1】开始
void statCount()
{
	char ch;
	int a;
	Ccount[0]=1;
	while((ch=fgetc(Src))!=EOF)
	{
		a=ch;
		Ccount[a]++;
	}
}
//【实验步骤1】结束
void print1()
{
	printf("NUL:1\n");
	for(int i=1; i<127; i++)
	{
		if(Ccount[i]>0) printf("%c:%d\n",i,Ccount[i]);
	}
}
//--------------------------------------------------------------------------------------------

//【实验步骤2】开始
Tree CREATE_TREE(int i) //生成树
{
	Tree T = (Tree)malloc(sizeof(TreeNode));
	T->c = i;
	T->weight = Ccount[i];
	T->left = NULL;
	T->right = NULL;
	return T;
}
void bubbleSortPLUS(Tree a[], int n)
{
	int i,j,flag;
	Tree hold;
	for(i=0; i<n-1; i++)
	{
		flag=0;
		for(j=0; j<n-1-i; j++)
		{
			if((a[j]->weight>a[j+1]->weight)||(a[j]->weight==a[j+1]->weight&&a[j]->c>a[j+1]->c))
			{
				hold=a[j];
				a[j]=a[j + 1];
				a[j+1]=hold;
				flag=1;
			}
		}
		if(flag==0) break;
	}
}
void createHTree()
{
	Tree tree[1005];
	int tree_num=0;
	int top=0;
	for(int i=0; i<128; i++)
	{
		if(Ccount[i]>0)
		{
			Tree p=CREATE_TREE(i);
			tree[tree_num++]=p;
		}
	}


	bubbleSortPLUS(tree,tree_num);

	int tail=tree_num-1;
	while(tree_num>1)
	{

		//printf("top:%d tail:%d tree_num:%d\n",top,tail,tree_num);
		//int j=0;
		/*for(j=top; j<=tail; j++)
		{
			printf(" |%d %d| ",j,tree[j]->weight);
		}*/
		Tree p=(Tree)malloc(sizeof(TreeNode));
		p->weight=0;
		p->left=tree[top++];
		p->right=tree[top++];
		p->weight=tree[top-1]->weight+tree[top-2]->weight;
		tree_num-=1;
		int temp=top;


		while(temp<=tail&&tree[temp]->weight<=p->weight)
		{
			//printf("%d ",temp);
			temp++;
		}
		//printf("\nrnmd\n\n");
		for(int j=tail+1; j>temp; j--)
		{
			tree[j]=tree[j-1];
		}
		tree[temp]=p;
		tail++;
	}
	Root=tree[top];
}
//【实验步骤2】结束
void  print2(struct  tnode  *p)
{
	if(p  !=  NULL)
	{
		if((p->left==NULL)&&(p->right==NULL))
			switch(p->c)
			{
				case  0:
					printf("NUL  ");
					break;
				case  ' ':
					printf("SP  ");
					break;
				case  '\t':
					printf("TAB  ");
					break;
				case  '\n':
					printf("CR  ");
					break;
				default:
					printf("%c  ",p->c);
					break;
			}
		print2(p->left);
		print2(p->right);
	}
}
//--------------------------------------------------------------------------------------------

//【实验步骤3】开始
void makeHCode()
{
	char HUFFMANCODE[MAXSIZE];
	//memset(HUFFMANCODE,'\0',MAXSIZE);
	int top=-1;
	PREORDER_TREE(Root->left,top,HUFFMANCODE,0);
	PREORDER_TREE(Root->right,top,HUFFMANCODE,1);
}

void PREORDER_TREE(Tree Root,int top,char HUFFMANCODE[],int code) //前序遍历
{
	if (Root != NULL)
	{
		HUFFMANCODE[++top]=code+'0';
		if(Root->right==NULL&&Root->left==NULL)
		{
			int temp=Root->c;
			HUFFMANCODE[top+1]='\0';
			strcpy(HCode[temp],HUFFMANCODE);
		}
		PREORDER_TREE(Root->left,top,HUFFMANCODE,0);
		PREORDER_TREE(Root->right,top,HUFFMANCODE,1);
	}
}
//【实验步骤3】结束
void print3()
{
	for(int i=0; i<128; i++)
	{
		if(HCode[i][0] != 0)
		{
			switch(i)
			{
				case 0:
					printf("NUL:");
					break;
				case ' ':
					printf("SP:");
					break;
				case '\t':
					printf("TAB:");
					break;
				case '\n':
					printf("CR:");
					break;
				default:
					printf("%c:",i);
					break;
			}
			printf("%s\n",HCode[i]);
		}
	}
}
//--------------------------------------------------------------------------------------------

//【实验步骤4】开始
void atoHZIP()
{
	char ch;
	int temp;
	fseek(Src,0,SEEK_SET);
	unsigned char p=0x00;
	int j=0;
	while((ch=fgetc(Src))!=EOF)
	{
		temp=ch;
		int i=0;
		while(HCode[temp][i]!='\0')
		{
			p=p<<1;
			p|=HCode[temp][i]-'0';
			i++;
			j++;
			if(j==8)
			{
				fputc(p,Obj);
				printf("%x",p);
				p=0;
				j=0;
			}
		}
	}
	if(j!=0) while(j++<8) p=p<<1;
	fputc(p,Obj);
	printf("%x",p);
}
//【实验步骤4】结束
void print4()
{
	long int in_size, out_size;

	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);

	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
