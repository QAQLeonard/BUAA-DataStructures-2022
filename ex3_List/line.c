#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct aNode
{
	int x;
	int y;
} Node;

typedef struct aLine
{
	Node node1;
	Node node2;
	int node_num;
} Line;

bool cmp(Node node1,Node node2)
{
	if(node1.x==node2.x&&node1.y==node2.y) return true;
	return false;
}
int main()
{
	int max_num=2;
	int max_id=0;
	int num;
	scanf("%d",&num);
	Line line[num];

	//int x1,y1,x2,y2;
	//scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

	for(int i=0; i<num; i++)
	{
		scanf("%d%d%d%d",&line[i].node1.x,&line[i].node1.y,&line[i].node2.x,&line[i].node2.y);
		line[i].node_num=2;
	}

	for(int i=0; i<num; i++)
	{
		if(line[i].node_num==0)
		{
			printf("ERROR!!!");
			continue;
		}
		for(int j=0; j<i; j++)
		{
			if(line[j].node_num==0) continue;
			if(cmp(line[j].node2,line[i].node1))
			{
				line[i].node1=line[j].node1;
				line[i].node_num=line[j].node_num+line[i].node_num-1;
				line[j].node_num=0;
			}
			else if(cmp(line[i].node2,line[j].node1))
			{
				line[i].node2=line[j].node2;
				line[i].node_num=line[i].node_num+line[j].node_num-1;
				line[j].node_num=0;
			}
		}

	}

	for(int i=0; i<num; i++)
	{

		if(max_num<line[i].node_num)
		{
			max_num=line[i].node_num;
			max_id=i;
		}
	}

	printf("%d %d %d\n",line[max_id].node_num-1,line[max_id].node1.x,line[max_id].node1.y);
	return 0;
}
