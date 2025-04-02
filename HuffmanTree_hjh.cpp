#include<queue>
#include<cstdio>
#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;

struct Node{
    char id;
    int val;
    Node* ls;
    Node* rs;
    Node(char id,int val) : id(id), val(val), ls(nullptr), rs(nullptr) {}
};

struct Compare{
    bool operator()(Node* x,Node* y){
        return x->val > y->val;  
    }
};
Node* root = nullptr;

string ch;
unordered_map<char,int> dic;
unordered_map<char,string> code;
priority_queue<Node*,vector<Node*>,Compare> q;

void init(){
    cin >> ch;
    for(int i = 0;i < ch.length();i++)
        dic[ch[i]]++;
    for(unordered_map<char,int>::iterator it = dic.begin(); it != dic.end();it++)
        q.push(new Node(it->first,it->second));
    while(q.size() > 1){
    	Node* x = q.top();
    	q.pop();
    	Node* y = q.top();
    	q.pop();
    	Node* z = new Node(0,x->val + y->val);
    	z->ls = x,z->rs = y;
    	q.push(z);
	}
	root = q.top();
}

void Huffman(Node* root,string Code){
	if(root->ls == nullptr && root->rs == nullptr){
		code[root->id] = Code;
		return;
	}
	Huffman(root->ls,Code + "0");
	Huffman(root->rs,Code + "1");
}

int main(){
	// sample: AAAABBBBBAAAABBABABABCCDDDDEEF
    init();
    Huffman(root,"0");
	for(unordered_map<char,int>::iterator it = dic.begin(); it != dic.end();it++)
        cout << it->first << ": " << code[it->first] << '\n';
    return 0;
}
