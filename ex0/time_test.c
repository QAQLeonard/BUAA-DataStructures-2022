#include<stdio.h>
#include<string.h>

int main()
{
	int a[100];
	
	memset(a,1,100*sizeof(int));
	memset(a,0,100*sizeof(int));

}
