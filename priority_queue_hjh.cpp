#include<queue>
#include<cstdio>
#include<vector>
#include<iostream>
#define ls (rt<<1)
#define rs (rt<<1|1)
#define fa (rt>>1)
using namespace std;

int read(){
	char c=' ';
	int v=0,x=1;
	while((c<'0')||(c>'9')){if(c=='-') x=-1;c=getchar();}
	while((c>='0')&&(c<='9')){v=(v<<1)+(v<<3)+(c^48);c=getchar();}
	return v*x;
}

struct priority_queue{
    int n;
    vector<int> v;

    void init(){
        n = read();
        v.push_back(0); //
        for(int i = 1;i <= n;i++)
           v.push_back(read());
        build();
    }

    void down(int rt){
        int pos = rt;
        if(ls <= n && v[pos] > v[ls]) pos = ls;
        if(rs <= n && v[pos] > v[rs]) pos = rs;
        if(pos != rt) swap(v[rt],v[pos]),down(pos);
    }

    void up(int rt){
        if(v[rt] < v[fa]){
            swap(v[rt],v[fa]);
            up(fa);
        }
    }

    void build(){
        for(int i = n;i;i--)
            down(i);
    }

    void push(int x){
        v.push_back(x);
        n++;
        up(n);
    }

    void pop(){
        if(!n) return;
        v[1] = v[n--];
        v.pop_back();
        down(1);
    }

    int top(){
        return v[1];
    }
}q;

int main(){
    q.init();
    int T = read();
    while(T--){
        int x = read();
        if(x == 1) q.push(read());
        if(x == 2) q.pop();
        if(x == 3) printf("%d\n",q.top());
    }
    return 0;
}
