#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

float arr[30]= {0};
char ch[300];

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
	printf("0%c0ERROR in ISP!!!!\n",ch2);
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
	int head=0;
	int tail;
	float temp;
	midtop=-1;
	while(fgets(ch,300,stdin)!=NULL)
	{
		head=0;
		tail=strlen(ch)-1;
		if(ch[head]>='a'&&ch[head]<='z'&&ch[head+1]=='=')//赋值语句
		{
			midtop=-1;
			suftop=-1;
			
			for(int i=head+2; i<tail&&ch[i]!='\0'; i++)
			{
				if(ch[i]==' ') continue;
				if((ch[i]>'z'||ch[i]<'a')&&(ch[i]>'9'||ch[i]<'0'))//既非常量也非变量,为运算符
				{
					mid[++midtop].CalCh=ch[i];
					mid[midtop].flag=cal;
				}
				else//常量或者变量
				{
					if(ch[i]<='z'&&ch[i]>='a')
					{
						temp=arr[ch[i]-'a'];
					}
					else
					{
						temp=0;
						for(int j=i; ch[j]<='9'&&ch[j]>='0'; j++)
						{
							temp*=10;
							temp+=ch[j]-'0';
							i++;
						}
						i--;
					}
					mid[++midtop].Num=temp;
					mid[midtop].flag=number;
					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				}
			}
			mid[++midtop].CalCh='#';
			mid[midtop].flag=cal;

			POSTFIX(mid,suf);
			/*for(int k=0; !(suf[k].flag==cal&&suf[k].CalCh=='#'); k++)
			{
				if(suf[k].flag==number) printf("%lf",suf[k].Num);
				else printf("%c",suf[k].CalCh);
			}
			printf("\n");*/
			float ans=EVAL(suf);
			
			//printf("%.3f",ans);
			arr[ch[head]-'a']=ans;
			//printf("%.3f\n",arr[ch[head]-'a']);
			continue;
		}
		else if(ch[head]=='p'&&ch[head+1]=='r')
		{
			head+=6;
			while(head<tail-2)
			{
				printf("%.3f ",arr[ch[head]-'a']);
				head+=2;
			}
			printf("%.3f\n",arr[ch[head]-'a']);
		}
		else if(ch[head]=='e'&&ch[head+1]=='x') return 0;
	}


	return 0;
}
