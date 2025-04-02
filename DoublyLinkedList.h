#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // 插入节点到链表头部
    void insertAtHead(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;  // 链表为空时，头尾指向新节点
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // 插入节点到链表尾部
    void insertAtTail(T value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;  // 链表为空时，头尾指向新节点
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // 在链表中间插入节点，pos 从0开始计数，表示插入到第 pos 个位置
    void insertAtPosition(int pos, T value) {
        if (pos < 0) {
            std::cout << "Position must be non-negative." << std::endl;
            return;
        }

        if (pos == 0) {
            insertAtHead(value);  // 如果是头部插入，直接调用头部插入函数
            return;
        }

        Node* current = head;
        int index = 0;

        // 遍历链表寻找插入位置
        while (current != nullptr && index < pos - 1) {
            current = current->next;
            index++;
        }

        if (current == nullptr) {
            std::cout << "Position out of range, inserting at tail." << std::endl;
            insertAtTail(value);  // 如果位置超出链表长度，则插入到尾部
        } else {
            Node* newNode = new Node(value);
            newNode->next = current->next;
            newNode->prev = current;

            if (current->next != nullptr) {
                current->next->prev = newNode;
            } else {
                tail = newNode;  // 如果插入位置是尾部，更新尾指针
            }

            current->next = newNode;
        }
    }

    // 删除链表中的某个值
    bool remove(T value) {
        if (head == nullptr) {
            return false; // 链表为空
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;

            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;  // 如果链表变为空，尾指针也要更新
            }

            delete temp;
            return true;
        }

        Node* current = head;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        if (current == nullptr) {
            return false;  // 值不存在于链表中
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;  // 如果删除的是最后一个节点，更新尾指针
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }

        delete current;
        return true;
    }

    // 正向遍历链表
    void printForward() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // 反向遍历链表
    void printBackward() {
        Node* current = tail;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->prev;
        }
        std::cout << "nullptr" << std::endl;
    }

    // 析构函数，释放链表内存
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList<int> list;

    list.insertAtHead(10);
    list.insertAtHead(20);
    list.insertAtHead(30);

    // 插入元素到尾部
    list.insertAtTail(40);
    list.insertAtTail(50);

    // 在中间插入
    list.insertAtPosition(2, 25);

    // 正向遍历
    list.printForward();  // 输出：30 -> 20 -> 25 -> 10 -> 40 -> 50 -> nullptr

    // 反向遍历
    list.printBackward();  // 输出：50 -> 40 -> 10 -> 25 -> 20 -> 30 -> nullptr

    // 删除元素
    list.remove(25);
    list.printForward();  // 输出：30 -> 20 -> 10 -> 40 -> 50 -> nullptr

    return 0;
}

