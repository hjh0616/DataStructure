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

const int INF = 1e9 + 7;
vector<vector<int> > dis;
int n, m;

int main(){
    n = read(), m = read();
    dis.resize(n + 1);
    for(int i = 1; i <= n; i++)
    	dis[i].resize(n + 1);
    for(int i = 1; i <= n; i++)
    	fill(dis[i].begin(), dis[i].end(), INF);
    for(int i = 1; i <= n; i++)
    	dis[i][i] = 0;
    for(int i = 1; i <= m; i++){
    	int x = read(), y = read(), z = read();
    	dis[x][y] = min(dis[x][y], z);
    	dis[y][x] = min(dis[y][x], z);
	}
	for(int k = 1; k <= n; k++)	
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
			printf("%d ", dis[i][j]);
		putchar('\n');
	}
    return 0;
}
