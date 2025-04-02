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
bool vis[N];
int n, m, dis[N], head[N], nxt[N], v[N], w[N], cnt;
priority_queue<pair<int, int> > q;

void add(int x, int y, int z){
    nxt[++cnt] = head[x];
    v[cnt] = y;
    w[cnt] = z;
    head[x] = cnt;
}

void dijkstra(int s){
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(make_pair(0, s));
    while(!q.empty()){
        int x = q.top().second;
        q.pop();
        if(!vis[x]){
            vis[x] = true;
            for(int i = head[x]; i; i = nxt[i])
                if(dis[v[i]] > dis[x] + w[i]){
                    dis[v[i]] = dis[x] + w[i];
                    q.push(make_pair(-dis[v[i]], v[i]));
                }
        }
    }
    for(int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
}

int main(){
    n = read(), m = read();
    for(int i = 1; i <= m; i++){
        int x = read(), y = read(), z = read();
        add(x, y, z), add(y, x, z);
    }
    dijkstra(1);
    return 0;
}
