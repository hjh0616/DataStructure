#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
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

class Splay{
private:
    struct Node{
        int val, size, cnt;
        Node *ls, *rs, *fa;
        Node(int v) : val(v), size(1), cnt(1), ls(nullptr), rs(nullptr), fa(nullptr) {}
    };
    Node* root;

    void pushup(Node* x){
        if(x != nullptr) x->size = x->cnt;
        if(x->ls != nullptr) x->size += x->ls->size;
        if(x->rs != nullptr) x->size += x->rs->size;
    }

    void rotate(Node* x){
        Node* y = x->fa;
        Node* z = y->fa;
        if(z != nullptr){
            if(y == z->ls) z->ls = x;
            else z->rs =x;
        }
        else root = x;
        x->fa = z;

        if(x == y->ls){
            y->ls = x->rs;
            if(x->rs != nullptr) x->rs->fa = y;
            x->rs = y;
        }
        else{
            y->rs = x->ls;
            if(x->ls != nullptr) x->ls->fa = y;
            x->ls = y;
        }
        y->fa = x;

        pushup(y);
        pushup(x);
    }

    void splay(Node* x){
        while(x->fa != nullptr){
            Node* y = x->fa;
            Node* z = y->fa;
            if(z != nullptr){
                if((y == x->fa) == (z == y->fa)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
    }

    Node* find(int val){
        Node* cur = root;
        while(cur != nullptr){
            if(cur->val == val){
                splay(cur);
                return cur;
            }
            if(cur->val > val) cur = cur->ls;
            if(cur->val < val) cur = cur->rs;
        }
        return nullptr;
    }

    Node* getPre(Node* x){
        if(x == nullptr || x->ls == nullptr) return nullptr;
        x = x->ls;
        while(x->rs != nullptr) x = x->rs;
        return x;
    }

    Node* getSuc(Node* x){
        if(x == nullptr || x->rs == nullptr) return nullptr;
        x = x->rs;
        while(x->ls != nullptr) x = x->ls;
        return x;
    }
    
    void print(Node* x){
    	if(x->ls != nullptr){
    		printf("%d ls %d\n", x->val, x->ls->val);
    		print(x->ls);
		}
		if(x->rs != nullptr){
    		printf("%d rs %d\n", x->val, x->rs->val);
    		print(x->rs);
		}
	}

public:
    Splay() : root(nullptr) {}

    void insert(int val){
        if(root == nullptr){
            root = new Node(val);
            return;
        }
        Node* cur = root;
        Node* fa = nullptr;
        while(cur != nullptr){
            if(cur->val == val){
                cur->cnt++;
                pushup(cur);
                splay(cur);
                return;
            }
            fa = cur;
            if(cur->val > val) cur = cur->ls;
            else cur = cur->rs;
        }
        Node* newNode = new Node(val);
        newNode->fa = fa;
        if (fa->val > val) fa->ls = newNode;
        else fa->rs = newNode;
        pushup(fa);
        splay(newNode);
    }

    void erase(int val){
        Node* x = find(val);
        if(x == nullptr) return;
        if(x->cnt){
            x->cnt--;
            pushup(x);
            return;
        }
        splay(x);
        if(x->ls == nullptr){
            root = x->rs;
            if(root != nullptr) root->fa = nullptr;
        }
        else if(x->rs == nullptr){
            root = x->ls;
            if(root != nullptr) root->fa = nullptr;
        }
        else{
            Node* pre = getPre(x);
            splay(pre);
            pre->rs = x->rs;
            if(x->rs != nullptr) x->rs->fa = pre;
            pushup(pre);
        }
        delete x;
    }

    int rank(int val) {
        Node* node = find(val);
        if (!node) return -1; 
        int rank = (node->ls ? node->ls->size : 0) + 1;
        return rank;
    }

    int kth(int k) {
        Node* cur = root;
        while(cur) {
            int leftSize = cur->ls ? cur->ls->size : 0;
            if(k <= leftSize) cur = cur->ls;
            else if(k > leftSize + cur->cnt){
                k -= leftSize + cur->cnt;
                cur = cur->rs;
            } 
            else{
                splay(cur);
                return cur->val;
            }
        }
        return -1; 
    }

    int getPre(int val){
        insert(val); 
        Node* pre = getPre(root);
        erase(val); 
        return pre ? pre->val : -1;
    }

    int getSuc(int val){
        insert(val); 
        Node* suc = getSuc(root);
        erase(val); 
        return suc ? suc->val : -1;
    }

	void print(){
		print(root);
	}

}T;

int main(){
	int n = read();
	for(int i = 1; i <= n; i++) 
		T.insert(i);
	printf("%d \n", T.kth(1));
	T.print();
    return 0;
}
