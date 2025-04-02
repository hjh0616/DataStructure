#include<stack>
#include<cstdio>
#include<vector>
#include<iostream>
using namespace std;

class AVLTree{
private:
    struct Node{
        int val;
        int height;
        int size;
        Node* left;
        Node* right;
        Node(int v) : val(v), height(1), size(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    int getHeight(Node* rt){
        return rt == nullptr ? 0 : rt->height;
    }

    int getSize(Node* rt){
        return rt == nullptr ? 0 : rt->size;
    }

    int getBalance(Node* rt){
        return rt == nullptr ? 0 : getHeight(rt->left) - getHeight(rt->right);
    }
    
    int getMin(){
        Node* current = root;
        while(current->left != nullptr) current = current->left;
        return current->val;
    }

    Node* Rrotate(Node* rt){
        Node* ls = rt->left;
        Node* rs = ls->right;
        ls->right = rt;
        rt->left = rs;
        rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
        ls->height = max(getHeight(ls->left), getHeight(rt->right)) + 1;
        rt->size = getSize(rt->left) + getSize(rt->right) + 1;
        ls->size = getSize(ls->left) + getSize(ls->right) + 1;
        return ls;  
    }

    Node* Lrotate(Node* rt){
        Node* rs = rt->right;
        Node* ls = rs->left;
        rs->left = rt;
        rt->right = ls;
        rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
        rs->height = max(getHeight(rs->left), getHeight(rs->right)) + 1;
        rt->size = getSize(rt->left) + getSize(rt->right) + 1;
        rs->size = getSize(rs->left) + getSize(rs->right) + 1;
        return rs;  
    }

    Node* insert(Node* rt, int val){
        if(rt == nullptr) return new Node(val);
        if(val < rt->val) rt->left = insert(rt->left, val);
        else if(val > rt->val) rt->right = insert(rt->right, val);
        else return rt;  
        rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
        rt->size = getSize(rt->left) + getSize(rt->right) + 1;
        
        int bal = getBalance(rt);
        if(bal > 1 && val < rt->left->val) return Rrotate(rt);
        if(bal < -1 && val > rt->right->val) return Lrotate(rt);
        if(bal > 1 && val > rt->left->val){
            rt->left = Lrotate(rt->left);
            return Rrotate(rt);
        }
        if(bal < -1 && val < rt->right->val){
            rt->right = Rrotate(rt->right);
            return Lrotate(rt);
        }
        return rt;  
    }

    Node* getLs(Node* rt){
        Node* current = rt;
        while(current->left != nullptr) current = current->left;
        return current;
    }

    Node* del(Node* rt, int val){
        if(rt == nullptr) return rt;
        if(val < rt->val) rt->left = del(rt->left, val);
        else if (val > rt->val) rt->right = del(rt->right, val);
        else{
            if((rt->left == nullptr) || (rt->right == nullptr)){
                Node* tmp = rt->left ? rt->left : rt->right;
                if(tmp == nullptr){
                    tmp = rt;
                    rt = nullptr;
                } 
                else *rt = *tmp;
                delete tmp;
            } 
            else{
                Node* temp = getLs(rt->right);
                rt->val = temp->val;
                rt->right = del(rt->right, temp->val);
            }
        }

        if (rt == nullptr) return rt;
        rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
        rt->size = getSize(rt->left) + getSize(rt->right) + 1;

        int bal = getBalance(rt);
        if(bal > 1 && getBalance(rt->left) >= 0) return Rrotate(rt);
        if(bal > 1 && getBalance(rt->left) < 0){
            rt->left = Lrotate(rt->left);
            return Rrotate(rt);
        }
        if(bal < -1 && getBalance(rt->right) <= 0) return Lrotate(rt);
        if(bal < -1 && getBalance(rt->right) > 0){
            rt->right = Rrotate(rt->right);
            return Lrotate(rt);
        }

        return rt;
    }

    int rank(Node* rt, int key){
        if(rt == nullptr) return 0;
        if(key < rt->val) return rank(rt->left, key);
        if(key == rt->val) return getSize(rt->left);
        if(key > rt->val) return getSize(rt->left) + rank(rt->right, key) + 1;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int val){
        root = insert(root, val);
    }

    void del(int val){
        root = del(root, val);
    }

    int query(){
        return getMin();
    }

    int rank(int key){
        return rank(root, key) + 1;
    }
    
    int count(int l, int r){
    	return rank(r) - rank(l - 1);
	}
}T;


int main(){
    T.insert(1);
    T.insert(2);
    T.insert(3);
    T.insert(5);
    T.insert(6);
    printf("%d\n", T.query());
    printf("%d\n", T.rank(3));
    printf("%d\n", T.rank(4));
    printf("%d\n", T.count(3, 5));
    T.del(1);
    T.del(2);
    printf("%d\n", T.query());
    return 0;
}
