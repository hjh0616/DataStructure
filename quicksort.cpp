#include<cstdio>
#include<iostream>
using namespace std;

int read(){
	char c=' ';
	int v=0,x=1;
	while((c<'0')||(c>'9')){if(c=='-') x=-1;c=getchar();}
	while((c>='0')&&(c<='9')){v=(v<<1)+(v<<3)+c-'0';c=getchar();}
	return v*x;
}

int n,a[810975];

int partition(int low,int high){
    int pivot = a[high],i = low - 1;   
	   
    for(int j = low;j < high;j++)
        if(a[j] < pivot) swap(a[++i], a[j]);

    swap(a[i + 1],a[high]);
    return i + 1;  
}

void quicksort(int low,int high){
    if(low < high){
        int pos = partition(low, high);
        quicksort(low,pos - 1);
        quicksort(pos + 1,high);
    }
}

int main(){
    n = read();
	for(int i = 1;i <= n;i++)
		a[i] = read();
		
	quicksort(1,n);
	
	for(int i = 1;i <= n;i++)
		printf("%d ",a[i]);
    return 0;
}


