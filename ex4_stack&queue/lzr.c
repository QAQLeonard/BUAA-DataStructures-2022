#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
struct s {
	char a;
	int line;
};
struct s N;
struct s judge(struct s out[],char m,char n,int len){
	int i,cnt=0;
	struct s right[200],left;
	for(i=len;i>=0;i--){
		if(out[i].a==n){
			right[cnt]=out[i];
			cnt++;
		} 
		else if(out[i].a==m){
			cnt--;
			if(cnt>=0){
				right[cnt]=N;
			}
			else left=out[i];
		}
	}
	if(cnt>=0) return right[0];
	else return left;
}
int main(){
	N.a='\0';
	N.line=-1;
	FILE *in;
	in=fopen("example.c","r");
	int i=1,j,k=0,state=0;
	struct s out[205];
	char buf[205];
	while(fgets(buf,1024,in)!=NULL){
		printf("%s\n",buf);
		if(buf[0]=='\n') continue;
		int length=strlen(buf);
		for(j=0;j<length;j++){
			if(buf[j]=='\"'){
				j++; 
				while(buf[j]!='\"') j++;
			}
			else if(buf[j]=='\''){
				j++;
				while(buf[j]!='\'') j++;
			}
			else if(buf[j]=='/'&&buf[j+1]=='*'){
				state=1;
			}
			else if(buf[j]=='*'&&buf[j+1]=='/'){
				state=0;
			}
			else if(buf[j]=='/'&&buf[j+1]=='/')
			continue;
			if(buf[j]=='('||buf[j]==')'||buf[j]=='{'||buf[j]=='}'){
				if(state==0){
				out[k].a=buf[j];
				out[k].line=i;
				k++;
				}
			}
		}
		i++;
	}
	int cnt=0,flag=0;
	struct s left[200],small,big;
	for(i=0;i<k;i++){
		if(out[i].a=='('){
			left[cnt]=out[i];
			cnt++;
		} 
		else if(out[i].a==')'){
			if(cnt>0){
				cnt--;
				left[cnt]=N;
			}
		}
		if((out[i].a=='{'||out[i].a=='}')&&cnt!=0){
			flag=1;
			break;
		}
	}
	if(flag==1){
		printf("without maching '%c' at line %d",left[0].a,left[0].line);
		return 0;
	}
	else{
		small=judge(out,'(',')',k);
		big=judge(out,'{','}',k);
		if(small.a==N.a&&big.a==N.a&&small.line==N.line&&big.line==N.line){
			for(i=0;i<k;i++)
			printf("%c",out[i].a);
		}
		else if(small.a!=N.a&&small.line!=N.line)
		printf("without maching '%c' at line %d",small.a,small.line);
		else
		printf("without maching '%c' at line %d",big.a,big.line);
	}
	fclose(in);
	return 0;
}
