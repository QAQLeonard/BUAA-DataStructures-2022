#include<stdio.h>

int main()
{
	int n,m,max=0;
	scanf("%d",&n);
	int a[n];
	int ans[n];
	int j,k,flag=1;
	for(int i=0; i<n; i++)
	{
		scanf("%d",&m);
		a[i]=m;
		if(m>max)
		{
			max=m;
		}

	}
	for(int i=0; i<n; i++)
	{
		if(a[i]==max)
		{
			ans[i]=0;
			//System.out.print("chao");
		}
		else
		{
			j=i;
			k=i;
			flag=1;
			while(flag==1)
			{
				if(j>0) j--;
				if(k<n-1) k++;
				if(a[j]>a[i]&&a[k]<=a[i])
				{
					flag=0;
					ans[i]=a[j];
				}
				else if(a[j]<=a[i]&&a[k]>a[i])
				{
					flag=0;
					ans[i]=a[k];

				}
				else if(a[j]>a[i]&&a[k]>a[i])
				{
					flag=0;
					ans[i]=a[k];
				}
			}
		}
	}
	for(int i=0; i<n-1; i++)
	{
		printf("%d ",ans[i]);
	}
	printf("%d",ans[n-1]);
}
