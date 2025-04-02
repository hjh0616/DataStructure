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

const int INF = 998244353;
vector<int> v, nxt, cap, flow;
vector<int> head, level, cur;
int n, m, cnt, S, T;

void add(int x, int y, int z){
    nxt[cnt] = head[x];
    v[cnt] = y;
    cap[cnt] = z;
    flow[cnt] = 0;
    head[x] = cnt++;
}

bool bfs(){
    queue<int> q;
    level.assign(n + 1, -1);
    level[S] = 0;
    q.push(S);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = head[u]; ~i; i = nxt[i])
            if(!~level[v[i]] && flow[i] < cap[i]){
                level[v[i]] = level[u] + 1;
                q.push(v[i]);
            }
    }
    return ~level[T];
}

int dfs(int u,int f){
    if(u == T) return f;
    for(int &i = cur[u]; ~i; i = nxt[i])
        if(level[v[i]] == level[u] + 1 && flow[i] < cap[i]){
            int res = dfs(v[i], min(f, cap[i] - flow[i]));
            if(res){
                flow[i] += res;
                flow[i ^ 1] -= res;
                return res;
            }
        }
    return 0;
}

int main(){
    n = read(), m = read(), S = read(), T = read();
    head.assign(n + 1, -1);
    cur.resize(n + 1);
    v.resize(m << 1);
    nxt.resize(m << 1);
    cap.resize(m << 1);
    flow.resize(m << 1);
    for(int i = 1; i <= m; i++){
        int x = read(), y = read(), z = read();
        add(x, y, z), add(y, x, 0);
    }
    int ans = 0;
    while(bfs()){
        for(int i = 1; i <= n; i++)
            cur[i] = head[i];
        int res = 0;
        while(res = dfs(S, INF)) ans += res;
    }
    printf("%d", ans);
    return 0;
}
