#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define visible_number 126-32+1
#define beg_c 32
#define end_c 126
char key[100], code_table[100];
typedef struct character
{
    char code;
    struct character *next;
} LinkList;

LinkList *creat(int n)//生成长度为n的链表
{
    int i;
    LinkList *head, *node, *end;
    head = (LinkList *)malloc(sizeof(LinkList));
    end = head;
    for(i=0; i<n; i++)
    {
        node = (LinkList *)malloc(sizeof(LinkList));
        node->code = key[i];//将key中的字母顺序填入
        end->next = node;
        end = node;
    }
    end->next = NULL;
    return head;
}

void set_table()
{
    int i, j, len_key=0, flag;
    char temp[40];
    gets(temp);
    for(i=0; temp[i]!='\0'; i++)//去掉密钥中的重复字符
    {
        flag = 0;
        for(j=0; j<len_key; j++)
        {
            if(key[j]==temp[i])
            {
                flag = 1;
            }
        }
        if(flag==0)
        {
            key[len_key] = temp[i];
            len_key++;
        }
    }
    //补全剩余字符
    for(i=beg_c; i<=end_c; i++)
    {
        flag = 0;
        for(j=0; j<len_key; j++)
        {
            if(key[j]==i)
            {
                flag = 1;
            }
        }
        if(flag==0)
        {
            key[len_key] = i;
            len_key++;
        }
    }
    // for(i=0; i<95; i++)
    // {
    //     printf("%c", key[i]);
    // }
}

LinkList *create_circle(char key[])//将链表首尾相接成环，返回的circle为环的起始位置
{
    LinkList *circle, *head, *end;
    int i=0;
    circle = creat(visible_number);
    head = circle;
    end = circle;
    while(i<visible_number&&end!=NULL)
    {
        end = end->next;
        i++;
    }
    circle = circle->next;
    end->next = circle;
    free(head);
    return circle;
}

void find_code(LinkList* circle)
{
    int i, j;
    char hold;
    LinkList *beg, *end, *del;
    beg = circle;
    end = circle;
    hold = beg->code;
    for(i=0; i<visible_number-1; i++)
    {
        while(end->next!=beg)
        {
            end = end->next;
        }
        del = beg;
        end->next = beg->next;
        for(j=0; j<(del->code); j++)
        {
            beg = beg->next;
            end = end->next;
        }
        code_table[del->code-beg_c] = beg->code;
        // printf("%c", code_table[del->code-beg_c]);
        free(del);
    }
    code_table[beg->code-beg_c] = hold;
    return;
}

FILE *in, *out;

int main()
{
    in=fopen("in.txt", "r");
    out=fopen("in_crpyt.txt", "w");
    LinkList *circle;
    int i;
    char c;
    set_table();
    circle = create_circle(key);
    find_code(circle);
    
    while((c=fgetc(in))!=EOF)
    {
        fputc(code_table[c-beg_c], out);
    }

    // for(i=0; i<visible_number; i++)
    // {
    //     printf("%c", code_table[i]);
    // }

    // LinkList *t;
    // t = circle;
    // while(t!=NULL)
    // {
    //     printf("%c", t->code);
    //     t = t->next;
    // }
    return 0;
}