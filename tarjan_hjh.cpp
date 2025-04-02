#include<stack>
#include<cstdio>
#include<vector>
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

stack<int> s;
vector<bool> inStack;
vector<int> dfn, low;
vector<vector<int> > graph, scc;
int n, m, clk;

void add(int x, int y){
    graph[x].push_back(y);
}

void tarjan(int u){
    dfn[u] = low[u] = ++clk;
    s.push(u);
    inStack[u] = true;
    for(auto v : graph[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(inStack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]){
        vector<int> Scc;
        while(1){
            int top = s.top();
            s.pop();
            Scc.push_back(top);
            inStack[top] = false;
            if(top == u) break;
        }
        scc.push_back(Scc);
    }
}

int main(){
    n = read(), m = read();
    graph.resize(n + 1);
    dfn.resize(n + 1, 0);
    low.resize(n + 1, 0);
    inStack.resize(n + 1, false);
    for(int i = 1; i <= m; i++){
        int x = read(), y = read();
        add(x, y);
    }
    for(int i = 1; i <= n; i++)
        if(!dfn[i]) tarjan(i);
    for(auto& Scc : scc){
        for(auto v : Scc)
            printf("%d ", v);
        putchar('\n');
    }
    return 0;
}
