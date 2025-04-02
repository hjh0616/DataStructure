#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include<functional> 
using namespace std;

template<typename T>
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
	    LinkedList();
	    ~LinkedList();
	
	    void push_front(const T& val);
	    void push_back(const T& val);
	    void remove(const T& val);
	    void find(const T& val) const;
	    void print() const;
	    void traverse(function<void(const T&)> func) const;
	
	private:
	    void clear();
};

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template<typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

template<typename T>
void LinkedList<T>::push_front(const T& val){
    Node* newNode = new Node(val);
    if(head == nullptr) head = tail = newNode;
    
	else{
        newNode->next = head;
        head = newNode;
    }
}

template<typename T>
void LinkedList<T>::push_back(const T& val){
    Node* newNode = new Node(val);
    if(tail == nullptr) head = tail = newNode;
    
	else{
        tail->next = newNode;
        tail = newNode;
    }
}

template<typename T>
void LinkedList<T>::remove(const T& val){
    if(head == nullptr) return;
    
    if(head->data == val){
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;
        return;
    }

    Node* current = head;
    while(current->next != nullptr && current->next->data != val) current = current->next;
    
    if(current->next == nullptr) return;

    Node* temp = current->next;
    current->next = current->next->next;
    if(current->next == nullptr) tail = current;
    delete temp;
}

template<typename T>
void LinkedList<T>::find(const T& val) const{
    Node* current = head;
    while(current != nullptr){
        if(current->data == val){
            cout << "Found!\n";
            return;
        }
        current = current->next;
    }
    cout << "Not Found!\n";
}

template<typename T>
void LinkedList<T>::print() const{
    Node* current = head;
    while(current != nullptr){
        cout << current->data;
        cout << ((current->next != nullptr) ? "->" : "\n");
        current = current->next;
    }
}

template<typename T>
void LinkedList<T>::traverse(function<void(const T&)> func) const{
    Node* current = head;
    while(current != nullptr){
        func(current->data);
        current = current->next;
    }
}

template<typename T>
void LinkedList<T>::clear(){
    Node* current = head;
    while(current != nullptr){
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr; 
}

template<typename Node>
bool HasCycle(Node* head){
    Node* fast = head;
    Node* slow = head;
    while(slow != nullptr && slow->next != nullptr){
        fast = fast->next;
        slow = slow->next->next;
        if(fast == slow) return true;
    }
    return false;
}

#endif 

