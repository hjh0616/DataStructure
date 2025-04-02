#include<stack>
#include<cstdio>
#include<vector>
#include<iostream>
using namespace std;

int read(){
	char c=' ';
	int v=0,x=1;
	while((c<'0')||(c>'9')){if(c=='-') x=-1;c=getchar();}
	while((c>='0')&&(c<='9')){v=(v<<1)+(v<<3)+(c^48);c=getchar();}
	return v*x;
}

struct Opt{
    char opt;
    double val; // opt = '$'
};
string eq;
vector<Opt> v;
stack<double> s1;
stack<char> s2;

void init(){
    int pos = 0;
    while(pos < eq.length()){
        if(eq[pos] >= '0' && eq[pos] <= '9'){
            int tmp = 0;
            while(eq[pos] >= '0' && eq[pos] <= '9' && pos < eq.length())
                tmp = (tmp << 1) + (tmp << 3) + (eq[pos++] ^ 48);
            v.push_back(Opt{'$',1.0 * tmp});
        }
        if(eq[pos] < '0' || eq[pos] > '9') v.push_back(Opt{eq[pos++],0});
    }
    //for(int i = 0;i < v.size();i++)
    //    printf("%c %d\n",v[i].opt,v[i].val);
}

void Pop(){
    char opt = s2.top();
    s2.pop();
    double y = s1.top();
    s1.pop();
    double x = s1.top();
    s1.pop();
    if(opt == '+') s1.push(x + y);
    if(opt == '-') s1.push(x - y);
    if(opt == '*') s1.push(x * y);
    if(opt == '/') s1.push(x / y);
    printf("%c ",opt);
}

void rePolish(){
    for(int i = 0;i < v.size();i++){
        if(v[i].opt == '$'){
            s1.push(v[i].val);
            printf("%.0lf ",v[i].val);
        }
        else{
            if(v[i].opt == '(') s2.push('(');
            if(v[i].opt == '+' || v[i].opt == '-'){
                while(!s2.empty() && s2.top()!='(') Pop();
                s2.push(v[i].opt);
            }
            if(v[i].opt == '*' || v[i].opt == '/'){
                while(!s2.empty() && s2.top() != '(' && s2.top() != '+' && s2.top() != '-') Pop();
                s2.push(v[i].opt);
            }
            if(v[i].opt == ')'){
                while(!s2.empty() && s2.top() != '(') Pop();
                s2.pop();
            }
        }
    }
    while(!s2.empty()) Pop();
    printf("\n%lf\n",s1.top());
}

int main(){
    // sample:((15/3)*(6-4)+8*(7-3))/2
    cin >> eq;
    init();
    rePolish();
    return 0;
}
