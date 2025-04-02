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
bool isBridge[N], vis[N];
int n, m, head[N], nxt[N], v[N], idx[N], cnt;
int clk, dfn[N], low[N], fa[N];

void add(int x, int y){
    nxt[cnt] = head[x];
    v[cnt] = y;
    idx[x]++;
    head[x] = cnt++;
}

void del(int i){
    idx[v[i]]--, idx[v[i^1]]--;
    v[i] = v[i ^ 1] = -1;
}

void tarjan(int u){
    vis[u] = true;
    dfn[u] = low[u] = ++clk;
    for(int i = head[u]; i; i = nxt[i])
        if(~v[i]){
            if(!vis[v[i]]){
                fa[v[i]] = u;
                tarjan(v[i]);
                low[u] = min(low[u], low[v[i]]);
                if(low[v[i]] > dfn[u]) isBridge[i] = true;
            } 
            else if(v[i] != fa[u]) low[u] = min(low[u], dfn[v[i]]);
        }
}

void fleury(int u){
    printf("%d ", u);
    memset(fa, 0, sizeof(fa));
    memset(vis, false, sizeof(vis));
    memset(isBridge, false, sizeof(isBridge));
    clk = 0, tarjan(u);
    for(int i = head[u]; i; i = nxt[i]){
    	if(~v[i] && (!isBridge[i] || idx[u] == 1)){
        	int tmp = v[i];
            del(i);
            fleury(tmp);
            return;
        }
	}
}

bool check(){
	tarjan(1);
	for(int i = 1; i <= n; i++)
		if(!vis[i] || idx[i] & 1) return false;
	return true;
}

int main(){
	memset(head, -1, sizeof(head));
    n = read(), m = read();
    for(int i = 1; i <= m; i++){
        int x = read(), y = read();
        add(x, y), add(y, x);
    }
    if(check()) fleury(1);
    else printf("-1");
    return 0;
}
