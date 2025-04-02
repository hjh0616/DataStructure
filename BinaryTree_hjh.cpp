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
    Node(char val) : id(val), ls(nullptr), rs(nullptr) {}
};
Node* root = nullptr;

string ch;
stack<Node*> s; 
vector<char> Pre;
vector<char> In;
vector<char> Post;
unordered_map<char,int> Inorder;

void init(){
    // sample: A(B(C,D),E(F,G(H,I)))
    int pos = 0;
    Node* current = nullptr;
    while(pos < ch.length()){
        if(ch[pos] >= 'A' && ch[pos] <= 'Z'){
            Node* newNode = new Node(ch[pos]);
            if(root == nullptr) root = newNode;
            if(!s.empty()){
                Node* fa = s.top();
                (fa->ls == nullptr)?(fa->ls = newNode):(fa->rs = newNode);
            }
            current = newNode;
        }
        if(ch[pos] == '(') s.push(current);
        if(ch[pos] == ')') s.pop();
        pos++;
    }
}

void PreOrder(){
	Pre.clear();
    s.push(root);
    while(!s.empty()){
        Node* current = s.top();
        s.pop();
    	//printf("%c ",current->id);
        Pre.push_back(current->id);
        if(current->rs != nullptr) s.push(current->rs);
        if(current->ls != nullptr) s.push(current->ls);
    }
    for(int i = 0;i < Pre.size();i++)
        printf("%c ",Pre[i]);
    putchar('\n');
}

void InOrder(){
	In.clear();
	Node* current = root;
	while(current != nullptr || !s.empty()){
		if(current != nullptr){
			s.push(current);
			current = current->ls;
		}
		else{
			current = s.top();
			s.pop();
			//printf("%c ",current->id);
            In.push_back(current->id);
			current = current->rs;
		}
	}
    for(int i = 0;i < In.size();i++)
        printf("%c ",In[i]);
	putchar('\n');
}

void PostOrder(){
	Post.clear();
	Node* current = root;
	Node* lst = nullptr;
	while(current != nullptr || !s.empty()){
		while(current != nullptr){
			s.push(current);
			current = current->ls;
		}
		Node* now = s.top();
		if(now->rs == nullptr || now->rs == lst){
			//printf("%c ",now->id);
            Post.push_back(now->id);
			s.pop();
			lst = now;
		}
		else current = now->rs;
	}
    for(int i = 0;i < Post.size();i++)
        printf("%c ",Post[i]);
	putchar('\n');
}

void Order(){
    cin >> ch;
    init();
    PreOrder();
    InOrder();
    PostOrder();
}

Node* PreIntoPost(int l,int r,int L,int R){
    if(l > r || L > R) return nullptr;
    Node* current = new Node(Pre[l]);
    current->ls = PreIntoPost(l + 1,l + Inorder[Pre[l]] - L,L,Inorder[Pre[l]] - 1);
    current->rs = PreIntoPost(l + Inorder[Pre[l]] - L + 1,r,Inorder[Pre[l]] + 1,R);
    return current;
}

Node* PostIntoPre(int l,int r,int L,int R){
    if(l > r || L > R) return nullptr;
    Node* current = new Node(Post[r]);
    current->ls = PostIntoPre(l,l + Inorder[Post[r]] - L - 1,L,Inorder[Post[r]] - 1);
    current->rs = PostIntoPre(l + Inorder[Post[r]] - L,r - 1,Inorder[Post[r]] + 1,R);
    return current;
}

void Rebuild(){
    for(int i = 0;i < In.size();i++)
        Inorder[In[i]] = i;
    root = PreIntoPost(0,Pre.size() - 1,0,In.size() - 1);
    PostOrder();
    root = PostIntoPre(0,Post.size() - 1,0,In.size() - 1);
    PreOrder();
}

int main(){
    // sample: A(B(C,D),E(F,G(H,I)))
    // Order: PreOrder, InOrder, PostOrder
	// Rebuild: PreIntoPost, PostIntoPre 
    Order();
    Rebuild();
    return 0;
}
