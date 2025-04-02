#include<stack>
#include<cstdio>
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

int n,a[810975];
stack<pair<int,int> > s;

int partition(int low,int high){
    int pivot = a[high],i = low - 1;   
	   
    for(int j = low;j < high;j++)
        if(a[j] < pivot) swap(a[++i], a[j]);

    swap(a[i + 1],a[high]);
    return i + 1;  
}

void quick_sort(){
    s.push(make_pair(1,n));
    /*if(low < high){
        int pos = partition(low, high);
        quicksort(low,pos - 1);
        quicksort(pos + 1,high);
    }*/
    while(!s.empty()){
        int low = s.top().first;
        int high = s.top().second;
        s.pop();
        if(low < high){
            int pos = partition(low, high);
            s.push(make_pair(pos + 1,high));
            s.push(make_pair(low,pos - 1));
        }
    }
}

int main(){
    n = read();
	for(int i = 1;i <= n;i++)
		a[i] = read();
		
	quick_sort();
	
	for(int i = 1;i <= n;i++)
		printf("%d ",a[i]);
    return 0;
}


