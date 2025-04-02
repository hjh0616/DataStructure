#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
string s, t;
int n, m, p[N];
int main(){
    cin >> s >> t;
    n = s.length(), m = t.length();
    s = s + '#' + t;
    for(int i = 1; i < n + m + 1; i++){
        int j = p[i - 1];
        while(j && s[i] != s[j]) j = p[j - 1];
        if(s[i] == s[j]) j++;
        p[i] = j;
    }
    for(int i = n + 1; i < n + m + 1; i++)
        if(p[i] == n) printf("%d ", i - n * 2);
    return 0;
}
