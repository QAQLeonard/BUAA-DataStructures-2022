#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define number 0
#define cal 1
float maths(float a,float b,char ch)
{
	switch(ch)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		default:
			printf("ERROR in MATH!!!!\n");
			return 0;
	}
	
}

typedef struct ASTACK
{
	float Num;
	char CalCh;
	int flag;
} Stack;

float ISP(char ch1,char ch2)
{
	switch(ch2)
	{
		case '(':
			return -1;
		case ')':
			if(ch1=='(') return 0;
			return 1;
		case '*':
			if(ch1=='*'||ch1=='/'||ch1=='%'||ch1==')') return 1;
			return -1;
		case '/':
			if(ch1=='*'||ch1=='/'||ch1=='%'||ch1==')') return 1;
			return -1;
		case '%':
			if(ch1=='*'||ch1=='/'||ch1=='%'||ch1==')') return 1;
			return -1;
		case '+':
			if(ch1=='('||ch1=='#') return -1;
			return 1;//+
		case '-':
			if(ch1=='('||ch1=='#') return -1;
			return 1;//-
		case '#':
			if(ch1=='#') return 0;
			return 1;
	}
	printf("ERROR in ISP!!!!\n");
	return 0;
}

float EVAL(Stack suf[])
{
	int topsuf=-1,topans=-1;
	Stack s0=suf[++topsuf];
	float ans[100];
	while(!(s0.flag==cal&&s0.CalCh=='#'))
	{
		//if(suf[top].flag==number) printf("%d",suf[top].Num);
		///else printf("%c",suf[top].CalCh);

		if(s0.flag==number)
		{
			ans[++topans]=s0.Num;
			s0=suf[++topsuf];
			continue;
		}
		else
		{
			//printf("%d%c%d\n",suf[topsuf-2].Num,suf[topsuf].CalCh,suf[topsuf-1].Num);
			ans[topans-1]=maths(ans[topans-1],ans[topans],suf[topsuf].CalCh);
			topans-=1;
			//printf("ans[%d]=%d\n",topans,ans[topans]);
			s0=suf[++topsuf];
			continue;
		}
	}
	if(topans!=0) printf("ERROR in EVAL!!!\n");
	return ans[0];
}

void POSTFIX(Stack mid[],Stack suf[])
{
	//printf("enter\n");
	int midtop0=-1,suftop0=-1,tptop0=-1;
	Stack tp[100];
	Stack s;
	tp[++tptop0].CalCh='#';
	tp[tptop0].flag=cal;
	while(1)
	{
		s=mid[++midtop0];
		if(s.flag==number) suf[++suftop0]=s;
		else
		{
			if(s.CalCh=='#')
			{
				while(tptop0>0)
				{
					suf[++suftop0]=tp[tptop0--];
				}
				suf[++suftop0].CalCh='#';
				suf[suftop0].flag=cal;
				break;
			}
			else if(s.CalCh==')')
			{
				while(tp[tptop0].CalCh!='(')
				{
					suf[++suftop0]=tp[tptop0--];
				}
				tptop0--;
			}
			else
			{
				while(ISP(tp[tptop0].CalCh,s.CalCh)>=0&&tptop0>0)
				{
					suf[++suftop0]=tp[tptop0--];
				}
				tp[++tptop0]=s;
			}
		}
	}
}
Stack mid[100];
Stack suf[100];
Stack calch[100];
int midtop=-1,suftop=-1;
int main()
{
	//printf("exe run\n");
	char ch[700];
	fgets(ch,700,stdin);
	int length=strlen(ch);
	int temp;
	int j;
	midtop=-1;
	for(int i=0; i<length-1&&ch[i]!='='; i++) //???????????????????
	{
		if(ch[i]==' ') continue;
		if(ch[i]>'9'||ch[i]<'0')
		{
			mid[++midtop].CalCh=ch[i];
			mid[midtop].flag=cal;
		}
		else
		{
			temp=0;
			for(j=i; ch[j]<='9'&&ch[j]>='0'; j++)
			{
				temp*=10;
				temp+=ch[j]-'0';
			}
			mid[++midtop].Num=temp;
			mid[midtop].flag=number;
			i=j-1;
		}
	}
	mid[++midtop].CalCh='#';
	mid[midtop].flag=cal;


	POSTFIX(mid,suf);
	
	for(int k=0; !(suf[k].flag==cal&&suf[k].CalCh=='#'); k++)
	{
		if(suf[k].flag==number) printf("%lf",suf[k].Num);
		else printf("%c",suf[k].CalCh);
	}
	printf("\n");
	
	float ans=EVAL(suf);
	printf("%.2f",ans);

	return 0;
}
