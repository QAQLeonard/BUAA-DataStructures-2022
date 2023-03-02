#include<stdio.h>

int n,i,u[100005],v[100005],tops,topa,top0;
char c[100005],sta[100005],ans[2*100005];

int main()
{
	int n=0;
	//freopen("exp.in","r",stdin);
	//freopen("exp.out","w",stdout);
	tops=-1;
	topa=-1;
	top0=-1;
	scanf("%d",&n);
	scanf("%s",c);
	ans[++topa]='_';
	for(int i=0; i<n; i++)
	{
		switch(c[i])
		{
			case '+':
				while(tops>=0&&sta[tops]=='*')
				{
					ans[++topa]=sta[tops--];
				}
				sta[++tops]=c[i];
				ans[++topa]='_';
				break;
			case '*':
				sta[++tops]=c[i];
				ans[++topa]='_';
				break;
			case '(':
				sta[++tops]=c[i];
				break;
			case ')':
				while(sta[tops]!='(')
				{
					ans[++topa]=sta[tops--];
				}
				tops--;
				break;
		}
	}

	while(tops>=0)
	{
		ans[++topa]=sta[tops--];
	}
	ans[++topa]='\0';
	printf("%s",ans);
	
	for(i=1; i<=topa; i++)
	{
		if(ans[i]=='_')
		{
			u[++top0]=1;
			v[top0]=1;
		}
		if(ans[i]=='*')
		{
			top0--;
			u[top0]=(u[top0+1]*v[top0]+u[top0]*v[top0+1]+u[top0]*u[top0+1])%19260817;
			v[top0]=v[top0]*v[top0+1]%19260817;
		}
		if(ans[i]=='+')
		{
			top0--;
			v[top0]=(u[top0+1]*v[top0]+u[top0]*v[top0+1]+v[top0]*v[top0+1])%19260817;
			u[top0]=u[top0]*u[top0+1]%19260817;
		}
	}
	printf("%d",7*u[0]);
}
