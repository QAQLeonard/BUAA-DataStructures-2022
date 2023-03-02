#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MaxTreeSize 100

int word_num = 0;

typedef struct TreeNode 
{
    char word[20];
    int times;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode,*Tree;

Tree CREATE_TREE(char word[]) //生成树
{
    Tree T = (Tree)malloc(sizeof(TreeNode));
    strcpy(T->word,word);
    T->lchild = NULL;
    T->rchild = NULL;
    return T;
}

void INSERT_TREE(Tree *ROOT, char word[]) 
{
    if ((*ROOT) == NULL) 
    {
        (*ROOT) = CREATE_TREE(word);
        (*ROOT)->times=1;
        word_num++;
    } 
    else if (strcmp(word,(*ROOT)->word)<0) //必须插入左子树的某要求
    {
        INSERT_TREE(&((*ROOT)->lchild), word);
    } 
    else if (strcmp(word,(*ROOT)->word)>0) //必须插入右子树的某要求
    {
        INSERT_TREE(&((*ROOT)->rchild), word);
    }
    else
    {
        (*ROOT)->times++;
    }
}


void INORDER_TREE(Tree ROOT) 
{
    if (ROOT != NULL) 
    {
        INORDER_TREE(ROOT->lchild);
        printf("%s %d\n", ROOT->word,ROOT->times);
        INORDER_TREE(ROOT->rchild);
    }
}

int main()
{
    char buffer[20];
    char ch;
    FILE *fp;
    fp=fopen("article.txt","r");
    Tree ROOT = NULL;
    int i=0;
    bool flag1 = false;
    while((ch=fgetc(fp))!=EOF)
    {
        //printf("%c",ch);
        if(ch>='a'&&ch<='z')
        {
            buffer[i]=ch;
            i++;
            flag1 = true;
        }
        else if(ch>='A'&&ch<='Z')
        {
            buffer[i]=ch-'A'+'a';
            i++;
            flag1 = true;
        }
        else 
        {           
            buffer[i]='\0';           
            //printf("%s",buffer);            
            if(flag1&&i!=0)
            {
                INSERT_TREE(&ROOT,buffer);
            }
			i=0;
            flag1 = false;
            memset(buffer,'\0',20);           
        }
    }
    fclose(fp);
	//printf("%d",word_num);
	//printf("creat success\n");
	
	if(ROOT!=NULL)	printf("%s", ROOT->word);
	if(ROOT->rchild!=NULL)	printf(" %s", ROOT->rchild->word);
	if(ROOT->rchild->rchild!=NULL)	printf(" %s", ROOT->rchild->rchild->word);
	printf("\n");
	
    INORDER_TREE(ROOT);
    return 0;
}















