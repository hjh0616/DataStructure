#include<stack>
#include<cstdio>
#include<iostream>
using namespace std;

int read(){
	char c=' ';
	int v=0,x=1;
	while((c<'0')||(c>'9')){if(c=='-') x=-1;c=getchar();}
	while((c>='0')&&(c<='9')){v=(v<<1)+(v<<3)+c-'0';c=getchar();}
	return v*x;
}

struct status{
    int layer;
    char from,assistant,to;
};
int n;
stack<status> s;

int main(){
    n = read();
    s.push(status{n,'A','B','C'});
    while(!s.empty()){
        status S = s.top();
        s.pop();
        if(S.layer == 1) printf("%c->%c\n",S.from,S.to);
        else{
            s.push(status{S.layer-1,S.assistant,S.from,S.to});
            s.push(status{1,S.from,S.assistant,S.to});
            s.push(status{S.layer-1,S.from,S.to,S.assistant});
        }
    }
    return 0;
}


