#include<cstdio>
#include<iostream>
using namespace std;

template <typename T>
class DoublyLinkedList{
private:
    struct Node{
        T data;
        Node* pre;
        Node* next;
        Node(T val) : data(val), pre(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_front(T val){
        Node* newNode = new Node(val);
        if(head == nullptr) head = tail = newNode; 
        else{
            newNode->next = head;
            head->pre = newNode;
            head = newNode;
        }
    }

    void push_back(T val){
        Node* newNode = new Node(val);
        if(tail == nullptr) head = tail = newNode;  
        else{
            newNode->pre = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    void insert(T key,T val){
        Node* current = head;

        while(current != nullptr && current->data != key) current = current->next;

        if(current == nullptr) return;

        Node* newNode = new Node(val);
        newNode->next = current->next;
        newNode->pre = current;

        if(current->next != nullptr) current->next->pre = newNode;
        else tail = newNode;  

        current->next = newNode;
    }

    void remove(T val){
        if(head == nullptr) return;

        if(head->data == val){
            Node* temp = head;
            head = head->next;
            if(head != nullptr) head->pre = nullptr;
            else tail = nullptr; 
            delete temp;
            return;
        }

        Node* current = head;
        while(current != nullptr && current->data != val) current = current->next;

        if(current == nullptr) return; 

        if (current->next != nullptr) current->next->pre = current->pre;
        else tail = current->pre;

        if (current->pre != nullptr) current->pre->next = current->next;

        delete current;
        return;
    }

    void print_front(){
        Node* current = head;
        while(current != nullptr){
            cout << current->data;
        	cout << ((current->next != nullptr) ? "->" : "\n");
            current = current->next;
        }
    }

    void print_back(){
        Node* current = tail;
        while(current != nullptr){
            cout << current->data;
        	cout << ((current->pre != nullptr) ? "->" : "\n");
            current = current->pre;
        }
    }

    ~DoublyLinkedList(){
        Node* current = head;
        while(current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main(){
    DoublyLinkedList<string> list;

    list.push_front("AAA");
    list.push_front("BBB");
    list.push_front("CCC");

    list.push_back("DDD");
    list.push_back("EEE");

    list.insert("AAA","FFF");
    list.insert("EEE","GGG");

    list.print_front();  
    list.print_back(); 
    
    list.remove("GGG");
    list.remove("AAA");
    list.print_back();

    return 0;
}

