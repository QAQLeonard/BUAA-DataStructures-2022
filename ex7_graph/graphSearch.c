#include<stdio.h>
#include<string.h>
int a[101][101],book[101],n,sum;

void dfs(int i)
{
	int j;
	printf("%d ", i);
	sum++;
	if(sum==n)	return;
	for(j=0; j<=n-1; j++)
	{
		if(book[j]==0&&a[i][j]==1)
		{
			book[j]=1;
			dfs(j);
		}
	}
	return;
}

void bfs(int i)
{
	int head=0,tail=-1,queue[10001],temp,j;
	queue[++tail]=i,book[i]=1;
	while(head<=tail)
	{
		temp=queue[head++];
		printf("%d ", temp);
		for(j=0; j<=n-1; j++)
		{
			if(book[j]==0&&a[temp][j]==1)
			{
				queue[++tail]=j;
				book[j]=1;
			}
		}
	}
	return;
}
int main()
{
	int m=0;
	int u,v;
	int op;
	scanf("%d %d",&n,&m);
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d", &u, &v);
		a[u][v]=a[v][u]=1;
	}
	scanf("%d",&op);

	sum=0,book[0]=1;
	dfs(0);
	printf("\n");
	memset(book,0,sizeof(book));
	
	bfs(0);
	memset(book,0,sizeof(book));
	printf("\n");
	
	for(int i=0; i<=n-1; i++)
	{
		a[i][op]=a[op][i]=0;
	}
	
	sum=0,book[0]=1;
	dfs(0);
	printf("\n");
	memset(book,0,sizeof(book));
	bfs(0);
	printf("\n");
	return 0;
	printf("\n");

	return 0;
}
