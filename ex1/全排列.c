#include<stdio.h>
#include <string.h>

int jiecheng(int n){
    int i,ans=1;
    for(i=1;i<=n;i++){
        ans*=i;
    }
    return ans;

}

int main()
{
	
	int i,j;
	int a[10];
	memset(a, 0, sizeof(a));
	int n;
	scanf("%d",&n);
    for(i=0;i<n;i++)
	{
        a[i]=i+1;
    }
    
    for(i=0;i<n-1;i++)//���˳������ 
	{
		printf("%d ",a[i]);
	}
	printf("%d\n",a[i]);
	
    for(i=1;i<jiecheng(n);i++)
	{
        for(i=n-2;i>=0;i--)//�ҵ�a[k1]<a[k1+1]������k1 
		{
		    if(a[i]<a[i+1])
		        break;
		}
		
		int k1=i;
		int temp_low=i+1;
		for(i=k1+1;i<n;i++)//�ҵ�����k1��ͬʱa[temp_low]>a[k1]��a[temp_low]��С��temp_low 
		{
		    if(a[i]>a[k1]&&a[i]<a[temp_low])
		        temp_low=i;
		}
		
		int temp;//��a[k1]��a[temp_low]��������...a[k1]a[k1+1]...a[temp_low]...a[n-1]--->...a[temp_low]a[k1+1]...a[k1]...a[n-1]
		temp=a[k1];
		a[k1]=a[temp_low];
		a[temp_low]=temp;
		
		for(j=k1+1,i=n-1;i>j;i--,j++)//��a[k1+1]��a[n-1]֮���������� 
		{
		    temp=a[i];
		    a[i]=a[j];
		    a[j]=temp;
		}
        
		for(i=0;i<n-1;i++)//������� 
		{
			printf("%d ",a[i]);
		}
		printf("%d\n",a[i]);
    }
}
