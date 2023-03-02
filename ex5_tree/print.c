#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define Switch 0
#define Computer 1
#define Printer 2

typedef struct ADEVICE
{
	int ID;
	int type;
	int depth;
	struct ADEVICE *port[8];
	struct ADEVICE *father;
} DEVICENODE,*Device;

void initialize_port(Device d[])
{
	for(int m=0; m<8; m++)
	{
		d[m]=NULL;
	}
}

DEVICENODE *printer[20];
int printer_num=0;

void PREORDER_TREE(Device ROOT) //前序获得打印机的地址
{
	if (ROOT != NULL)
	{
		//printf("%d %d\n",ROOT->ID,ROOT->type);
		if(ROOT->type==Printer)
		{
			printer[printer_num++]=ROOT;
			//printf("rnmd\n");
			//printf("%d %d\n",ROOT->ID,ROOT->type);
		}
		else if(ROOT->type==Switch)
		{
			//printf("yes!\n");

			for(int i=0; i<8; i++)
			{
				//if(ROOT->port[i]==NULL) printf("yes!\n");
				PREORDER_TREE(ROOT->port[i]);
			}
		}
	}
}

int DISTANCE(Device end_c,Device end_p)//获取两叶节点之间的距离
{
	int distance=0;
	int delta_depth=end_c->depth-end_p->depth;
	if(delta_depth>0)
	{
		distance+=delta_depth;
		while(delta_depth--)
		{
			end_c=end_c->father;
		}
	}
	else if(delta_depth<0)
	{
		delta_depth=-delta_depth;
		distance+=delta_depth;
		while(delta_depth--)
		{
			end_p=end_p->father;
		}
	}

	while(end_c!=end_p)
	{
		distance+=2;
		end_c=end_c->father;
		end_p=end_p->father;
	}

	return distance;
}

int main()
{
	int device_num,ID0;
	int id,type,fid,num;
	int distance=0,min_printer_ID=0,min_distance=1000;

	scanf("%d %d",&device_num,&ID0);

	Device device[device_num];

	FILE *fin;
	fin=fopen("in.txt", "r");

	for(int i=0; i<device_num; i++)//存储为树
	{
		fscanf(fin,"%d %d %d %d",&id,&type,&fid,&num);
		Device p = (Device)malloc(sizeof(DEVICENODE));
		p->ID=id;
		p->type=type;
		initialize_port(p->port);
		if(id!=0)
		{
			p->father=device[fid];
			p->father->port[num]=p;
			p->depth=p->father->depth+1;
		}
		else
		{
			p->father=NULL;
			p->depth=0;
		}
		device[i]=p;
	}

	//printf("success\n");
	PREORDER_TREE(device[0]);//前序获得打印机位置

	//printf("%d\n",printer_num);
	for(int i=0; i<printer_num; i++)//计算距离
	{
		Device end_c=device[ID0];
		Device end_p=printer[i];
		distance=DISTANCE(end_c,end_p);
		if(distance<min_distance)
		{
			min_distance=distance;
			min_printer_ID=i;
		}
	}

	printf("%d ",printer[min_printer_ID]->ID);
	int head=0,tail=min_distance-2;
	Device switcher[min_distance-1];
	
	Device end_c=device[ID0];
	Device end_p=printer[min_printer_ID];
	int delta_depth=end_c->depth-end_p->depth;
	if(delta_depth>0)//电脑在打印机下面 
	{
		while(delta_depth--)
		{
			switcher[head++]=end_c->father;
			end_c=end_c->father;
		}
	}
	else if(delta_depth<0)//打印机在电脑下面
	{
		delta_depth=-delta_depth;
		while(delta_depth--)
		{
			switcher[tail--]=end_p->father;
			end_p=end_p->father;
		}
	}

	while(end_c!=end_p)
	{
		switcher[head++]=end_c->father;
		switcher[tail--]=end_p->father;
		end_c=end_c->father;
		end_p=end_p->father;
	}
	
	for(int i=0;i<min_distance-1;i++)
	{
		printf("%d ",switcher[i]->ID);
	}
	return 0;
}
