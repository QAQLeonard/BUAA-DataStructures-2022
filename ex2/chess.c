#include<stdio.h>
#include<stdbool.h>

int a[20][20];

bool check(int i,int j)
{

	if(i<=15&&j<=15&&a[i][j]==a[i+1][j+1]&&a[i][j]==a[i+2][j+2]&&a[i][j]==a[i+3][j+3]) 
	{
		if(i<15&&j<15&&a[i+4][j+4]==0) return true;
		if(i>0&&j>0&&a[i-1][j-1]==0) return true;
	}
	if(i<=15&&j>=3&&a[i][j]==a[i+1][j-1]&&a[i][j]==a[i+2][j-2]&&a[i][j]==a[i+3][j-3])
	{
		if(i<15&&j>3&&a[i+4][j-4]==0) return true;
		if(i>0&&j<18&&a[i-1][j+1]==0) return true;
	}  
	if(i<=15&&a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j]&&a[i][j]==a[i+3][j])
	{
		if(i<15&&a[i+4][j]==0) return true;
		if(i>0&&a[i-1][j]==0) return true;
	}
	//if(i>=3&&a[i][j]==a[i-1][j]&&a[i][j]==a[i-2][j]&&a[i][j]==a[i-3][j])  return true;
	if(j<=15&&a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2]&&a[i][j]==a[i][j+3])
	{
		if(j<14&&a[i][j+4]==0) return true;
		if(j>0&&a[i][j-1]==0) return true;
	}
	//if(j>=3&&a[i][j]==a[i][j-1]&&a[i][j]==a[i][j-2]&&a[i][j]==a[i][j-3])  return true;

	return false;
}

int main()
{
	for(int i=0;i<19;i++)
	{
		for(int j=0;j<19;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	
	
	for(int i=0;i<19;i++)
	{
		for(int j=0;j<19;j++)
		{
			if(a[i][j]!=0)
			{
				if(check(i,j))
				{
					printf("%d:%d,%d\n",a[i][j],i+1,j+1);
					return 0;
				}
			}
		}
	}
	
	printf("No");
	
	return 0;
}
