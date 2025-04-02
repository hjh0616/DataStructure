#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

template <typename T>

class LinkedList{
private:
    struct Node{
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr) , tail(nullptr) {}

    void push_front(T value){
        Node* newNode = new Node(value);
        if(head == nullptr) head = tail = newNode; 
        else{
            newNode->next = head;
            head = newNode;
        }
    }
    
    void push_back(T value){
        Node* newNode = new Node(value);
        if(tail == nullptr) head = tail = newNode;  
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }

    void find(T value){
        Node* current = head;
        while(current != nullptr){
            if(current->data == value){
                cout<<"Found!\n";
                return;
            }
            current = current->next;
        }
        cout<<"Not Found!\n";
    }

    void remove(T value){
        if(head == nullptr) return;
        if(head->data == value){
            Node* temp = head;
            head = head->next;
            if(head == nullptr) tail = nullptr;
            delete temp;
            return;
        }
        Node* current = head;
        while(current->next != nullptr && current->next->data != value)
            current = current->next;
        if(current->next == nullptr) return;
        Node* temp = current->next;
        current->next = current->next->next;
        if(current->next == nullptr) tail = current;
        delete temp;
    }

    void print(){
        Node* current = head;
        while(current != nullptr){
            cout<<current->data;
            cout<<((current->next != nullptr) ? "->" : "\n");
            current = current->next;
        }
    }

    bool hasCycle(){
        Node* slow = head;
        Node* fast = head;
        while(fast != nullptr && fast->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true; 
        }
        return false; 
    }

    ~LinkedList(){
        Node* current = head;
        while(current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList<string> list;
    list.push_front("AAA");
    list.push_front("BBB");
    list.push_back("CCC");
    list.find("AAA");
    list.print();
    list.remove("AAA");
    list.find("AAA");
    list.print();
    return 0;
}

