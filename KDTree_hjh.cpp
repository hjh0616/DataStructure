#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
#define inf (9999)
using namespace std;
struct Point{
    int x, y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
    bool operator<(const Point &other) const {
        return (x == other.x) ? (y < other.y) : (x < other.x);
    }
    void print(){
        printf("%d %d\n", x, y);
    }
};
class KDTree{
private:
    struct Node{
        Point point;
        Node* left;
        Node* right;
        Node(Point p) : point(p), left(nullptr), right(nullptr) {}
    };
    Node* root;

    int getdis(Point a, Point b){
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
    
    Node* build(vector<Point> &points, int l, int r, int dep){
        if(l > r) return nullptr;
        int dim = dep & 1, mid = l + (r - l >> 1);
        nth_element(points.begin() + l, points.begin() + mid, points.begin() + r + 1, [dim](const Point &a, const Point &b){return (!dim) ? (a < b) : (b < a);});
        Node* cur = new Node(points[mid]);
        cur->left = build(points, l , mid - 1, dep + 1);
        cur->right = build(points, mid + 1, r, dep + 1);
        return cur;
    }

    Node* insert(Node* cur, Point point, int dep){
        if(cur == nullptr) return new Node(point);
        int dim = dep & 1;
        if((!dim && point.x < cur->point.x) || (dim && point.y < cur->point.y)) cur->left = insert(cur->left, point, dep + 1);
        else cur->right = insert(cur->right, point, dep + 1);
        return cur;
    }

    Point getNearest(Node* cur, Point point, int dep){
        if(cur == nullptr) return Point(inf, inf);
        Point res = cur->point;
        int dis = getdis(res, point), dim = dep & 1;
        Node *nxt = nullptr, *other = nullptr;
        if((!dim && point.x < cur->point.x) || (dim && point.y < cur->point.y)) nxt = cur->left, other = cur -> right;
        else nxt = cur-> right, other = cur -> left;

        Point tar = getNearest(nxt, point, dep + 1);
        if(getdis(tar, point) < dis) res = tar, dis = getdis(tar, point);
        int Dis = (!dim) ? abs(cur->point.x - point.x) : abs(cur->point.y - point.y);
        if(Dis * Dis < dis){
            tar = getNearest(other, point, dep + 1);
            if(getdis(tar, point) < dis) res = tar, dis = getdis(tar, point);
        }
        return res;
    }

    void getNearestK(Node* cur, Point point, int dep, int k, priority_queue<pair<int, Point> > &q){
        if(cur == nullptr) return;
        int dis = getdis(cur->point, point), dim = dep & 1;
        if(q.size() < k) q.push(make_pair(dis, cur->point));
        else if(dis < q.top().first){
            q.pop();
            q.push(make_pair(dis, cur->point));
        }
        Node *nxt = nullptr, *other = nullptr;
        if((!dim && point.x < cur->point.x) || (dim && point.y < cur->point.y)) nxt = cur->left, other = cur -> right;
        else nxt = cur-> right, other = cur -> left;

        getNearestK(nxt, point, dep + 1, k, q);
        if(q.size() < k || (!dim && (cur->point.x - point.x) * (cur->point.x - point.x) < q.top().first) 
        || (dim && (cur->point.y - point.y) * (cur->point.y - point.y) < q.top().first)) getNearestK(other, point, dep + 1, k, q);
    }

public:
    KDTree() : root(nullptr) {}
    
    void build(vector<Point> &points){
        root = build(points, 0, points.size() - 1, 0);
    }

    void insert(Point point){
        root = insert(root, point, 0);
    }

    Point getNearest(Point point){
        return getNearest(root, point, 0);
    }

    vector<Point> getNearestK(Point point, int k){
        priority_queue<pair<int, Point> > q;
        vector<Point> v;
        getNearestK(root, point, 0, k, q);
        while(!q.empty()){
            v.push_back(q.top().second);
            q.pop();
        }
        reverse(v.begin(),v.end());
        return v;
    }
}T;

int main(){
	vector<Point> points = {Point(3, 6), Point(2, 7), Point(17, 15)};
	T.build(points);
	T.getNearest(Point(10, 5)).print();
	T.insert(Point(6, 12));
	T.insert(Point(9, 1));
	T.getNearest(Point(10, 5)).print();
	T.insert(Point(10, 19));
	vector<Point> v = T.getNearestK(Point(10, 5), 3);
    for(auto p : v)
        p.print();
    return 0;
}
