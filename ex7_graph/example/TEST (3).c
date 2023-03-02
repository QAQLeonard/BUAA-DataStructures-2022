#include<stdio.h>
#include<stdlib.h>
int f[10005]={0};
struct bian
{
	int id;
	int u,v,w;
	int flag;
};
struct bian a[10005];
int cmp1(const void*a,const void*b)
{
	struct bian s1,s2;
	s1=*(struct bian*)a,s2=*(struct bian*)b;
	return s1.w-s2.w;
}
int cmp2(const void*a,const void*b)
{
	struct bian s1,s2;
	s1=*(struct bian*)a,s2=*(struct bian*)b;
	return s1.id-s2.id;
}
int find(int x)
{
	if(f[x]==0)	return x;
	else
		return f[x]=find(f[x]);
}
int main()
{
	int n,m,i,j,ans=0;
	scanf("%d %d", &n, &m);
	for(i=0;i<=m-1;i++)
		scanf("%d %d %d %d", &a[i].id, &a[i].u, &a[i].v, &a[i].w);
	qsort(a,m,sizeof(a[0]),cmp1);
	for(i=0;i<=m-1;i++)
	{
		int xx=find(a[i].u);
		int yy=find(a[i].v);
		if(xx!=yy)
		{
			f[xx]=yy;
			a[i].flag=1;
			ans+=a[i].w;
		}
	}
	printf("%d\n", ans);
	qsort(a,m,sizeof(a[0]),cmp2);
	for(i=0;i<=m-1;i++)
		if(a[i].flag)
			printf("%d ", a[i].id);
	return 0;
} 

