#include<stdio.h>
#include<stdlib.h>

typedef struct APeople
{
	int enter_time;
	int left_time;
} People;

int main()
{
	int period_num=0;
	int n=0;
	int print_num=0;
	scanf("%d",&period_num);
	int people[period_num];
	int people_num=0;
	int top=-1;
	//printf("%d\n",period_num);
//printf("0");
	for(int i=0; i<period_num; i++)
	{
		scanf("%d",&people[i]);
		people_num+=people[i];
	}
	People queue[people_num];
	//printf("read in success\n");

	int window_num=3;
	int period=0;
	int remain=0;
//printf("%d\n",people_num);
	while(print_num<people_num)
	{
		if(period<period_num)
		{
			remain+=people[period];

			for(int j=n; j<n+people[period]; j++)
			{
				queue[j].enter_time=period;
			}

			n+=people[period];
		}

			while(remain>=7*window_num&&window_num<5){window_num++;}
			
		//printf("period:%d left_num:%d window_num:%d\n",period,remain,window_num);
		for(int j=0; j<window_num&&remain>0; j++)
		{
			queue[++top].left_time=period;
			remain--;
			printf("%d : %d\n",top+1,queue[top].left_time-queue[top].enter_time);
			print_num++;
		}
		period++;
		while(remain<7*window_num&&window_num>3){window_num--;}
	}
}
