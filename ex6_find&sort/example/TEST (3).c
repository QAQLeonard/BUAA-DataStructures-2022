#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int selectsort(int n,int num[]);
int bubblesort(int n,int num[]);
int treesort(int n,int num[]);
int bisort(int n,int num[],int hold[]);
int quicksort(int num[],int left, int right, int ans);
int adjust(int num[],int i,int n,int cnt);
void swap(int *a, int *b);
int main()
{
	int n,op,i,j,ans=0;
	int num[105],hold[105];
	scanf("%d %d", &n, &op);
	for(i=0;i<=n-1;i++)
		scanf("%d", &num[i]);
	switch(op)
	{
		case 1 :	ans=selectsort(n,num);	break;
		case 2 :	ans=bubblesort(n,num);	break;
		case 3 :	ans=treesort(n,num);	break;
		case 4 :	ans=bisort(n,num,hold);	break;
		case 5 :	ans=quicksort(num,0,n-1,ans);	break;
	}
	for(i=0;i<=n-1;i++)
		printf("%d ", num[i]);
	printf("\n%d\n", ans);
	return 0;
}
int selectsort(int n,int num[])
{
	int cnt=0,i,j,min,temp;
	for(i=0;i<n-1;i++)
	{
		min=num[i],temp=i;
		for(j=i+1;j<=n-1;j++)
		{
			cnt++;
			if(num[j]<min)
			{
				min=num[j];
				temp=j;
			}
		}
		num[temp]=num[i];
		num[i]=min;
	}
	return cnt; 
}
int bubblesort(int n,int num[])
{
	int i,j,cnt=0,flag=0,temp;
	for(i=0;i<n-1;i++)
	{
		flag=0;
		for(j=0;j<n-i-1;j++)
		{
			cnt++;
			if(num[j]>num[j+1])
			{
				temp=num[j];
				num[j]=num[j+1];
				num[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0)	break;
	}
	return cnt;
}
int treesort(int n,int num[])
{
	int i,cnt=0,temp;
	for(i=n/2-1;i>=0;i--)
		cnt=adjust(num,i,n,cnt);
	for(i=n-1;i>=1;i--)
	{
		temp=num[i];
		num[i]=num[0];
		num[0]=temp;
		cnt=adjust(num,0,i,cnt);
	}
	return cnt;
}
int adjust(int num[],int i,int n,int cnt)
{
	int j,temp;
	j=2*i+1,temp=num[i];
	while(j<n)
	{
		cnt++;
		if(j<n-1&&num[j]<num[j+1])
			j++;
		if(temp>=num[j])
			break;
		num[(j-1)/2]=num[j];
		j=j*2+1;
	}
	num[(j-1)/2]=temp;
	return cnt;
}
int bisort(int n, int num[],int hold[])
{
    int cnt=0;
    int i=1;
	cnt=mSort(num,hold,0,n-1,cnt);
	return cnt; 
}
int mSort(int num[], int hold[], int left, int right,int cnt)
{
    int mid;
    if(left<right)
	{
        mid=(left+right)/2;
        cnt=mSort(num,hold,left,mid,cnt);
        cnt=mSort(num,hold,mid+1,right,cnt);
        cnt=merge(num,hold,left,mid,right,cnt);
    }
    return cnt;
}
int merge(int x[],int hold[],int left,int leftend,int rightend,int cnt)
{
	int i=left,j=leftend+1,q=left;
    while(i<=leftend && j<=rightend)
    {
        cnt++;
		if(x[i]<=x[j]) 
            hold[q++]=x[i++];
        else
            hold[q++]=x[j++];
    }
    while(i<=leftend)
        hold[q++]=x[i++];
    while(j<=rightend)
        hold[q++]=x[j++];
    for(i=left;i<=rightend;i++)
        x[i]=hold[i];
    return cnt;
}
int quicksort(int k[],int left,int right,int ans)
{     
    int i,last,temp;
    if(left<right)
	{
        last=left; 
        for(i=left+1;i<=right;i++)
        {
            ans++;
			if(k[i]<k[left])
                swap(&k[++last],&k[i]);
        }
        swap(&k[left],&k[last]);
        ans=quicksort(k,left,last-1,ans); 
        ans=quicksort(k,last+1,right,ans);   
    }
    return ans;
}
void swap(int *a, int *b)
{
	int temp=0;
	temp = *a;
	*a = *b;
	*b = temp;
}

