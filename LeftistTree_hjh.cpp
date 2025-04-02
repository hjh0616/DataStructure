#include<queue>
#include<cstdio>
#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;

int read(){
	char c=' ';
	int v=0,x=1;
	while((c<'0')||(c>'9')){if(c=='-') x=-1;c=getchar();}
	while((c>='0')&&(c<='9')){v=(v<<1)+(v<<3)+c-'0';c=getchar();}
	return v*x;
}

struct Node {
    int val;
    int dis;
    Node* ls;
    Node* rs;
    Node(int val) : val(val), dis(0), ls(nullptr), rs(nullptr){}
};

class LeftistTree {
private:
    unordered_map<int, Node*> rt;
    unordered_map<int, int> fa;
    int n,T;

    int find(int x){
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }

    Node* merge(Node* x, Node* y){
        if(!x) return y;
        if(!y) return x;
        if(x->val > y->val) swap(x,y);
        x->rs = merge(x->rs,y);
        if(x->ls == nullptr || (x->rs != nullptr && x->ls->dis < x->rs->dis)) swap(x->ls,x->rs);
        x->dis = x->rs ? x->rs->dis + 1 : 0;
        return x;
    }

    void pop(Node* &root){
        if(root == nullptr) return;
        Node* tmp = merge(root->ls, root->rs);
        delete root;
        root = tmp;
    }

public:
    void query(int x){
        if(rt[find(x)] == nullptr) printf("-1\n");
        else printf("%d\n",rt[find(x)]->val);
    }

    void del(int x){
        if(rt[find(x)] != nullptr) pop(rt[find(x)]);
    }
    
    void merge(int x,int y){
        int fx = find(x),fy = find(y);
        if(fx != fy){
            rt[fx] = merge(rt[fx],rt[fy]);
            fa[fy] = fx;
        }
    }
    
	void build() {
        queue<int> q;
        for(int i = 1;i <= n;i++)
            q.push(i); 
        while(q.size() > 1){
            int x = q.front(); 
			q.pop();  
            int y = q.front(); 
			q.pop(); 
            merge(x,y);  
            q.push(find(x));  
        }
    }
    
    void work(){
        while(T--){
            int op = read();
            if(op == 1){
                int x = read(),y = read();
                merge(x,y);
            }
            else{
                int x = read();
                (op == 2)?query(x):del(x);
            }
        }
    }

    LeftistTree(int n,int T) : n(n), T(T){
        for(int i = 1;i <= n; i++){
            fa[i] = i;
            int val = read();
            rt[i] = new Node(val);
        }
        build();
        work();
    }
};

int main() {
    int n = read(),T = read();
    LeftistTree lt(n,T);
    return 0;
}
