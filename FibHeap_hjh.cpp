#include<cmath>
#include<cstdio>
#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;

struct Node{
    int val;
    int degree;
    Node* fa;
    Node* child;
    Node* left;
    Node* right;
    bool mark;
    Node(int v) : val(v), degree(0), fa(nullptr), child(nullptr), left(this), right(this), mark(false) {}
};

const int MinVal = -1e8;

class FibHeap{
private:
    Node* Min;
    int cnt;
    unordered_map<int, vector<Node*> > pos;

    void link(Node* x,Node* y){ 
        x->left->right = x->right;
        x->right->left = x->left;
        x->fa = y;

        if(y->child == nullptr){
            y->child = x;
            x->left = x->right = x;
        }
        else{
            x->left = y->child;
            x->right = y->child->right;
            y->child->right->left = x;
            y->child->right = x;
        }
        y->degree++;
        x->mark = false;
    }

    void consolidate(){
        int Max = log2(cnt) + 1;
        vector<Node*> dt(Max, nullptr), rt;

        if(Min == nullptr) return;
        Node* current = Min;
        do{
            rt.push_back(current);
            current = current->right;
        }while(current != Min);

        for(Node* current : rt){
            Node* x = current;
            int d = x->degree;
            while(dt[d] != nullptr){
                Node* y = dt[d];
                if(x->val < y->val) swap(x,y);
                link(x, y);
                dt[d++] = nullptr;
            }
            dt[d] = x;
        }

        Min = nullptr;
        for(Node* current : dt)
            if(current != nullptr && (Min == nullptr || Min->val > current->val)) Min = current;
    }

    void cut(Node* x, Node* y){
        if(x->right == x) y->child = nullptr;
        else{
            x->left->right = x->right;
            x->right->left = x->left;
            if(y->child == x) y->child = x->right;
        }

        y->degree--;
        x->left = Min;
        x->right = Min->right;
        Min->right = x;
        Min->right->left =x; 
    }

    void cascadingCut(Node* x){
        Node* y = x->fa;
        if(y != nullptr){
            if(!y->mark) y->mark = true;
            else{
                cut(x, y);
                cascadingCut(y);
            }
        }
    }

public:
    FibHeap() : Min(nullptr), cnt(0) {}

    void insert(int val){
        Node* newNode = new Node(val);
        if(Min == nullptr) Min = newNode;
        else{
            newNode->left = Min;
            newNode->right = Min->right;
            Min->right->left = newNode;
            Min->right = newNode;
            if(newNode->val < Min->val) Min = newNode;
        }
        pos[val].push_back(newNode);
        cnt++;
    }

    void merge(FibHeap &other){
        if(Min == nullptr){
            Min = other.Min;
            return;
        }    
        if(other.Min == nullptr) return;

        Min->right->left = other.Min->left;
        other.Min->left->right = Min->right;
        Min->right = other.Min;
        other.Min->left = Min;
        if(other.Min->val < Min->val) Min = other.Min;

        cnt += other.cnt;
        other.Min = nullptr, other.cnt = 0;
	    for(auto &tmp : other.pos)
	        pos[tmp.first].insert(pos[tmp.first].end(), tmp.second.begin(), tmp.second.end());
	    other.pos.clear(); 
    }

    int getMin(){
        return Min == nullptr ? -1 : Min->val;
    }

    int extractMin(){
        if(Min == nullptr) return -1;
        if(Min->child != nullptr){
            Node* child = Min->child;
            do{
                child->fa = nullptr;
                child = child -> right;
            }while(child != Min->child);

            if(Min->right != Min){
	            Min->left->right = Min->child;
	            Min->child->left = Min->left;
            	Min->right->left = Min->child->left;
	            Min->child->left->right = Min->right;
			}
        }
        Node* tmp = Min;
        int res = tmp->val;
        if(Min == Min->right) Min = nullptr;
        else{
        	Min->left->right = Min->right;
        	Min->right->left = Min->left;
            Min = Min->right;
            consolidate();
        }
        cnt--;
        pos[tmp->val].pop_back();
        delete tmp;
        return res;
    }
    
    void decreaseKey(int key, int val){
        if(key < val) return;
        if(pos[key].empty()) return;
        
        Node* x = pos[key].back();
        Node* y = x->fa;
        x->val = val;
        if(y != nullptr && x->val < y->val){
            cut(x, y);
            cascadingCut(y);
        }
        if(x->val < Min->val) Min = x;
        
        pos[val].push_back(x);
        pos[key].pop_back();
        if(pos[key].empty()) pos.erase(key);
    }

    void del(int key){
        decreaseKey(key, MinVal);
        extractMin();
    }

}T1, T2;

int main(){
    T1.insert(1);
    T1.insert(2);
    T1.insert(3);
    printf("%d\n",T1.getMin());
    T1.insert(4);
    printf("%d\n",T1.extractMin());
    printf("%d\n",T1.getMin());
    T1.decreaseKey(2,1);
    printf("%d\n",T1.extractMin());
    printf("%d\n",T1.getMin());
    T2.insert(1);
    T1.merge(T2);
    printf("%d\n",T1.getMin());
    T1.del(1);
    printf("%d\n",T1.getMin());
    return 0;
}
