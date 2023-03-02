#include<stdio.h>

void insert_list(int a[],int *n,int i,int item)
{
	for(int j=*n-1;j>i-1;j--)
	{
		a[j+1]=a[j];
	}
	a[i]=item;
	(*n)++;
}

void select_sort(int a[],int n)
{
	int d;
	int temp;
	for(int i=0;i<n-1;i++)
	{
		d=i;
		for(int j=i+1;j<n;j++)
		{
			if(a[j]<a[d]) d=j;
		}
		if(d!=i)
		{
			temp=a[d];
			a[d]=a[i];
			a[i]=temp;
		}
	}
}

void delete_item2(int a[],int *n,int item)
{
	int k=0;
	for(int i=0;i<*n;i++)
	{
		if(a[i]==item) k++;
		else a[i-k]=a[i];
	}
	(*n)-=k;
	
}

void purge(int a[],int *n)
{
	int k=0;
	if(*n>1)
	{
		for(int i=1;i<*n;i++)
		{
			if(a[i]!=a[k]) 
			{
				k++;
				a[k]=a[i];
			}
		}
		(*n)=k+1;
	}
}


void insert_item(int a[],int *n,int item)
{
	if(item>=a[*n-1]) a[(*n)++]=item;
	else
	{
		int i=0;
		while(a[i]<=item)
		{i++;}
		insert_list(a,n,i+1,item);
	}
}






int main()
{
	
	
	
	return 0;
}
