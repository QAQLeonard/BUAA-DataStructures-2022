//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {			//Huffman树结构
	char c;		
	int weight;		//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};		//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 	//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;			//实验步骤 
FILE *Src, *Obj;
	
void statCount();		//步骤1：统计文件中字符频率
void createHTree();		//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();		//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 		//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();			//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();			//输出步骤3的结果
void print4();			//输出步骤4的结果

int main()
{
        if((Src=fopen("input.txt","r"))==NULL) {
	        fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1; 
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
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

//【实验步骤1】开始 
void statCount()
{
char c;
	Ccount[0]=1;
	while((c=fgetc(Src))!=EOF)
	{
		if(c!='\n')
			Ccount[c]++;
	}

	
}



//【实验步骤1】结束

//【实验步骤2】开始
void createHTree()
{
struct tnode *p=NULL, *tree[1005],*temp=NULL;
	int i,j=0,k;
	for(i=0;i<128;i++)
	{
		if(Ccount[i]!=0)
		{
			p=(struct tnode*)malloc(sizeof(struct tnode));
			p->c=i,p->weight=Ccount[i];
			p->left=p->right=NULL;
			tree[j++]=p;	
		}
	}
	for(i=0,j=j-1;i<=j;i++)
	{
		for(k=0;k<=j-i-1;k++)
		{
			if(tree[k]->weight<tree[k+1]->weight)
			{
				temp=tree[k];
				tree[k]=tree[k+1];
				tree[k+1]=temp;
			}
			else if(tree[k]->weight==tree[k+1]->weight)
			{
				if(tree[k]->c<tree[k+1]->c)
				{
					temp=tree[k];
					tree[k]=tree[k+1];
					tree[k+1]=temp;
				}
			}
		}
	}
	for(j;j>0;)
	{
		p=(struct tnode*)malloc(sizeof(struct tnode));
		p->left=p->right=NULL;
		p->left=tree[j],p->right=tree[j-1];
		p->weight=p->left->weight+p->right->weight;
		j-=2;
		for(i=0;i<=j;i++)
			if(p->weight>=tree[i]->weight)	break;
		for(k=j+1;k>i;k--)
			tree[k]=tree[k-1];
		tree[i]=p;
		j++;
	} 
	Root=tree[0];

	
}



//【实验步骤2】结束

//【实验步骤3】开始
void makeHCode()
{
int level=0;
	struct tnode *p=Root;
	char Huffman[1005]={0};
	frontorder(p,'0',0,Huffman);
} 
void frontorder(struct tnode *p,char code,int level,char Huffman[])
{
	if(level!=0)
		Huffman[level-1]=code;
	if(p->left==NULL&&p->right==NULL)
	{
		Huffman[level]='\0';
		strcpy(HCode[p->c],Huffman);
	}
	else
	{
		frontorder(p->left,'0',level+1,Huffman);
		frontorder(p->right,'1',level+1,Huffman);
	}
}




//【实验步骤3】结束

//【实验步骤4】开始
void atoHZIP()
{
unsigned char *pc,hc=0;
	int c=0,i=0;
	fseek(Src,0,SEEK_SET);
	do{
		c=fgetc(Src);
		if(c==EOF)	c=0;
		for(pc=HCode[c];*pc!='\0';pc++)
		{
			hc=(hc<<1)|(*pc-'0');
			i++;
			if(i==8)
			{
				fputc(hc,Obj);
				printf("%x", hc); 
				i=0;
			}
		}
		if(c==0&&i!=0)
		{
			while(i++<8)	hc=(hc<<1);
			fputc(hc,Obj);
		}
	}while(c);

	
}



//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

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

