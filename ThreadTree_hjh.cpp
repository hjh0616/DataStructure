#include<stack>
#include<cstdio>
#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;

struct Node{
    char id;
    Node* ls;
    Node* rs;
    Node* fa;
    bool Ls,Rs; // true->pre,nxt
    Node(char val) : id(val), ls(nullptr), rs(nullptr), fa(nullptr), Ls(false), Rs(false) {}
};
Node* root = nullptr;
Node* pre = nullptr;

string ch;
stack<Node*> s; 

void init(){
    int pos = 0;
    Node* current = nullptr;
    while(pos < ch.length()){
        if(ch[pos] >= 'A' && ch[pos] <= 'Z'){
            Node* newNode = new Node(ch[pos]);
            if(root == nullptr) root = newNode;
            if(!s.empty()){
                Node* fa = s.top();
                (fa->ls == nullptr)?(fa->ls = newNode):(fa->rs = newNode);
                newNode->fa = fa;
            }
            current = newNode;
        }
        if(ch[pos] == '(') s.push(current);
        if(ch[pos] == ')') s.pop();
        pos++;
    }
}

void PreThread(Node* current,Node* &pre){
    if(current == nullptr) return;
    if(current->ls == nullptr) current->ls = pre,current->Ls = true;
    if(pre != nullptr && pre->rs == nullptr) pre->rs = current,pre->Rs = true;
    pre = current;
    if(!current->Ls) PreThread(current->ls,pre);
    if(!current->Rs) PreThread(current->rs,pre);
}

void InThread(Node* current,Node* &pre){
    if(current == nullptr) return;
    InThread(current->ls,pre);
    if(current->ls == nullptr) current->ls = pre,current->Ls = true;
    if(pre != nullptr && pre->rs == nullptr) pre->rs = current,pre->Rs = true;
    pre = current;
    InThread(current->rs,pre);
}

void PostThread(Node* current,Node* &pre){
    if(current == nullptr) return;
    PostThread(current->ls,pre);
    PostThread(current->rs,pre);
    if(current->ls == nullptr) current->ls = pre,current->Ls = true;
    if(pre != nullptr && pre->rs == nullptr) pre->rs = current,pre->Rs = true;
    pre = current;
}

void PreOrder(){
    Node* current = root;
    while(current != nullptr){
        printf("%c ", current->id);
        if(!current->Ls && current->ls != nullptr) current = current->ls;
        else current = current->rs;
    }
    putchar('\n');
}

void InOrder(){
    Node* current = root;
    while(current != nullptr && !current->Ls) current = current->ls;
    while(current != nullptr){
        printf("%c ", current->id);
        if(current->Rs) current = current->rs;
        else{
            current = current->rs;
            while(current != nullptr && !current->Ls) current = current->ls;
        }
    }
    putchar('\n');
}

void PostOrder(){
    Node* current = root;
    Node* pre = nullptr;
    while(current != nullptr){
        while(current->ls != pre) current = current->ls;
        while(current != nullptr && current->Rs){
            printf("%c ",current->id);
            pre = current;
            current = current->rs;
        }
        if(current == root){
            printf("%c ",current->id);
            return;
        }
        while(current != nullptr && current->rs == pre){
            printf("%c ",current->id);
            pre = current;
            current = current->fa;
        }
        if(current != nullptr && !current->Rs) current = current->rs;
    }
}

int main(){
    // sample: A(B(C,D),E(F,G(H,I)))
    cin >> ch;
    init();
    //PreThread(root,pre),PreOrder();
    //InThread(root,pre),InOrder();
    PostThread(root,pre),PostOrder();
    return 0;
}
