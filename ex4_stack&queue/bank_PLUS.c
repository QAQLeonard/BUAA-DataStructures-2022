#include<stdio.h>
int a[10005];
int main()
{
	int head=1,tail=1,i,n,m,num=3;
	int remain=0;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &m);
		while(m--)	tail++;
		remain=tail-head;
		
		while(remain>=7*num&&num<5)	num++;
		if(remain>=num)	head+=num;
		else	head=tail;
		remain=tail-head;
		while(remain<7*num&&num>3)	num--;
		for(i=head;i<tail;i++)	a[i]++;
	}
	while(head!=tail)
	{
		remain=tail-head;
		if(remain>=num)	head+=num;
		else	head=tail;
		remain=tail-head;
		while(remain<7*num&&num>3)	num--;
		for(i=head;i<tail;i++)	a[i]++;
	}
	for(i=1;i<tail;i++)
		printf("%d : %d\n", i, a[i]);
	return 0;
}
