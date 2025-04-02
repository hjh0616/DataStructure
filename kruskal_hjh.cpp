#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int read(){
	char c=' ';
	int v=0,x=1;
	while((c<'0')||(c>'9')){if(c=='-') x=-1;c=getchar();}
	while((c>='0')&&(c<='9')){v=(v<<1)+(v<<3)+c-'0';c=getchar();}
	return v*x;
}

const int N = 100010;
struct Edge{
    int u, v, w;
    Edge() : u(0), v(0), w(0) {}
    Edge(int a, int b, int c) : u(a), v(b), w(c) {}
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
}e[N];
bool vis[N];
int n, m, fa[N], cnt, res;

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void kruskal(){
    sort(e + 1, e + m + 1);
    for(int i = 1; i <= n; i++)
        fa[i] = i;
    for(int i = 1; i <= m; i++){
        if(cnt == n - 1) break;
        int fx = find(e[i].u), fy = find(e[i].v);
        if(fx != fy){
            cnt++;
			res += e[i].w;
            fa[fx] = fy;
        }
    }
    if(cnt == n - 1) printf("%d", res);
    else printf("-1");
}

int main(){
    n = read(), m = read();
    for(int i = 1; i <= m; i++){
        int x = read(), y = read(), z = read();
        e[i] = Edge(x, y, z);
    }
    kruskal();
    return 0;
}
