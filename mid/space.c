#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>


typedef struct AARERA
{
	int left;
	int right;
	int flag;
} Area;

int ccmp(const void *elem1,const void *elem2)
{
	Area *stu1 = (Area *)elem1;
	Area *stu2 = (Area *)elem2;
	return (*stu1).left-(*stu2).left;
}

int main()
{
	int area_num;
	scanf("%d",&area_num);
	Area area[area_num];
	int sum=0;
	Area area0[area_num];
	for(int i=0; i<area_num; i++)
	{
		scanf("%d %d",&area[i].left,&area[i].right);
		area[i].flag=1;
	}
	printf("\n");
		
	for(int i=0; i<area_num; i++)
	{
		if(area[i].flag==0) continue;
		for(int j=0; j<area_num; j++)
		{
			if(j==i) continue;
			if(area[i].left<=area[j].right+1&&area[i].left>=area[j].left&&area[j].flag)
			{
				//id=j;
				area[i].left=area[j].left;
				area[j].flag=0;
			}
			else if(area[i].right<=area[j].right&&area[i].right>=area[j].left-1&&area[j].flag)
			{
				//id=j;
				area[i].right=area[j].right;
				area[j].flag=0;
			}
			else if(area[i].right<=area[j].right&&area[i].left>=area[j].left&&area[j].flag)
			{
				//id=j;
				area[i].right=area[j].right;
				area[i].left=area[j].left;
				area[j].flag=0;
			}
			else if(area[i].right>=area[j].right&&area[i].left<=area[j].left)
			{
				area[j].flag=0;
			}
		}
		/*for(int i=0; i<area_num; i++)
		{
			if(area[i].flag)printf("%d %d\n",area[i].left,area[i].right);
		}
		printf("\n\n");*/
	}
	for(int i=0; i<area_num; i++)
	{
		if(area[i].flag)
		{
			area0[sum++]=area[i];
		}
	}
	qsort(area0,sum,sizeof(Area),ccmp);
	for(int i=0; i<sum; i++)
	{
		printf("%d %d\n",area0[i].left,area0[i].right);
	}
	return 0;
}
