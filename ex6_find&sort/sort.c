#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ans=0;


void adjust(int k[],int i,int n)
{
	int j,temp;
	temp=k[i];
	j=2*i+1;
	while(j<n)
	{
		if(j<n-1 && k[j]<k[j+1]) j++;
		ans++;
		if(temp>=k[j]) break;
		k[(j-1)/2]=k[j];
		j=2*j+1;
	}
	k[(j-1)/2]=temp;
}

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;

}

void merge(int x[],int tmp[],int left,int leftend,int rightend)
{
	int i=left, j=leftend+1, q=left;
	while(i<=leftend && j<=rightend)
	{
		ans++;
		if(x[i]<=x[j]) tmp[q++]=x[i++];
		else tmp[q++]=x[j++];
	}
	while(i<=leftend)
	{
		tmp[q++]=x[i++];
	}
	while(j<=rightend)
	{
		tmp[q++]=x[j++];
	}
	for(i=left; i<=rightend; i++)
	{
		x[i]=tmp[i];
	}

}

void mergeSort(int arr[], int temp[], int left, int right)
{
	if (left<right)
	{
		int center=(left+right)/2;
		mergeSort(arr,temp,left,center);
		mergeSort(arr,temp,center+1,right);
		merge(arr,temp,left,center,right);
	}
}

void quickSort(int k[ ],int left,int right)

{
	int i, last;
	if(left<right)
	{
		last=left;
		for(i=left+1; i<=right; i++)
		{
			ans++;
			if(k[i]<k[left]) swap(&k[++last],&k[i]);
		}
		swap(&k[left],&k[last]);
		quickSort(k,left,last-1);
		quickSort(k,last+1,right);
	}
}

void Sort(int arr[],int num,int op)
{
	switch(op)
	{
		case 1://selectsort
		{
			int min = 0;
			for(int i=0; i<num-1; i++)
			{
				min=i;
				for(int j=i+1; j<num; j++)
				{
					ans++;
					if(arr[min]>arr[j])
					{
						min=j;
					}
				}
				int temp = arr[min];
				arr[min] = arr[i];
				arr[i] = temp;
			}
			break;
		}

		case 2://bubblesort
		{
			int hold,flag;
			for(int i=0; i<num-1; i++)
			{
				flag=0;
				for(int j=0; j<num-1-i; j++)
				{
					ans++;
					if(arr[j]>arr[j + 1])
					{
						hold=arr[j];
						arr[j]=arr[j + 1];
						arr[j+1]=hold;
						flag=1;
					}
				}
				if(flag==0) break;
			}
			break;
		}

		case 3:
		{
			for(int i=num/2-1; i>=0; i--)
			{
				adjust(arr,i,num);
			}
			for(int j=num-1; j>0; j--)
			{
				int temp=arr[0];
				arr[0]=arr[j];
				arr[j]=temp;//将堆顶元素与末尾元素进行交换
				adjust(arr,0,j);//重新对堆进行调整
			}
			break;
		}

		case 4:
		{
			int temp[num];
			memset(temp,0,sizeof(temp));
			mergeSort(arr,temp,0,num-1);
			break;
		}
		case 5:
		{
			quickSort(arr,0,num-1);
		}
		break;
	}
}

int main()
{
	int num=0,op=0;
	scanf("%d %d",&num,&op);
	int arr[num];
	for(int i=0;i<num;i++)
	{
		scanf("%d",&arr[i]);
	}
	Sort(arr,num,op);
	for(int i=0;i<num-1;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("%d\n%d",arr[num-1],ans);
	return 0;
}
