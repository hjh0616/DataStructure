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

int n, m;
vector<int> w, v, c ,dp;
vector<int> c1;
vector<vector<int> > w1, v1;

void init(){
    n = read(), m = read();
    w.resize(n + 1);
    v.resize(n + 1);
    c.resize(n + 1);
    dp.assign(m + 1, 0);
    for(int i = 1; i <= n; i++)
        w[i] = read();
    for(int i = 1; i <= n; i++) 
        v[i] = read();
    for(int i = 1; i <= n; i++)
        c[i] = read();
}

void Init(){
    n = read(), m = read();
    c1.resize(n + 1);
    w1.resize(n + 1);
    v1.resize(n + 1);
    dp.assign(m + 1, 0);
    for(int i = 1; i <= n; i++){
        c1[i] = read();
        w1[i].resize(c1[i] + 1);
        v1[i].resize(c1[i] + 1);
        for(int j = 1; j <= c1[i]; j++)
            w1[i][j] = read();
        for(int j = 1; j <= c1[i]; j++)
            v1[i][j] = read();
    }
}

void knapsack01(){
    init();
    for(int i = 1; i <= n; i++)
        for(int j = m; j >= w[i]; j--)  
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    printf("%d ", dp[m]);
}

void knapsackComplete(){
    init();
    for(int i = 1; i <= n; i++)
        for(int j = w[i]; j <= m; j++)  
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    printf("%d ", dp[m]);
}

void knapsackMulti(){
    init();
    for(int i = 1; i <= n; i++)
        for(int j = m; j >= w[i]; j--)  
            for(int k = 1; k <= c[i] && k * w[i] <= j; k++)
                dp[j] = max(dp[j], dp[j - k * w[i]] + k * v[i]);
    printf("%d ", dp[m]);
}

void knapsackGrouped(){
    Init();
    for(int i = 1; i <= n; i++)
        for(int j = m; j >= 0; j--)
            for(int k = 1; k <= c1[i]; k++)
                if(j >= w1[i][k]) dp[j] = max(dp[j], dp[j - w1[i][k]] + v1[i][k]);
    printf("%d ", dp[m]);
}

int main(){
    knapsack01();
    knapsackComplete();
    knapsackMulti();
    knapsackGrouped();
    return 0;
}
