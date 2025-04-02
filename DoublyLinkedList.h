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

    // ����ڵ㵽����ͷ��
    void insertAtHead(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;  // ����Ϊ��ʱ��ͷβָ���½ڵ�
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // ����ڵ㵽����β��
    void insertAtTail(T value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;  // ����Ϊ��ʱ��ͷβָ���½ڵ�
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // �������м����ڵ㣬pos ��0��ʼ��������ʾ���뵽�� pos ��λ��
    void insertAtPosition(int pos, T value) {
        if (pos < 0) {
            std::cout << "Position must be non-negative." << std::endl;
            return;
        }

        if (pos == 0) {
            insertAtHead(value);  // �����ͷ�����룬ֱ�ӵ���ͷ�����뺯��
            return;
        }

        Node* current = head;
        int index = 0;

        // ��������Ѱ�Ҳ���λ��
        while (current != nullptr && index < pos - 1) {
            current = current->next;
            index++;
        }

        if (current == nullptr) {
            std::cout << "Position out of range, inserting at tail." << std::endl;
            insertAtTail(value);  // ���λ�ó��������ȣ�����뵽β��
        } else {
            Node* newNode = new Node(value);
            newNode->next = current->next;
            newNode->prev = current;

            if (current->next != nullptr) {
                current->next->prev = newNode;
            } else {
                tail = newNode;  // �������λ����β��������βָ��
            }

            current->next = newNode;
        }
    }

    // ɾ�������е�ĳ��ֵ
    bool remove(T value) {
        if (head == nullptr) {
            return false; // ����Ϊ��
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;

            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;  // ��������Ϊ�գ�βָ��ҲҪ����
            }

            delete temp;
            return true;
        }

        Node* current = head;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        if (current == nullptr) {
            return false;  // ֵ��������������
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;  // ���ɾ���������һ���ڵ㣬����βָ��
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }

        delete current;
        return true;
    }

    // �����������
    void printForward() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // �����������
    void printBackward() {
        Node* current = tail;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->prev;
        }
        std::cout << "nullptr" << std::endl;
    }

    // �����������ͷ������ڴ�
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

    // ����Ԫ�ص�β��
    list.insertAtTail(40);
    list.insertAtTail(50);

    // ���м����
    list.insertAtPosition(2, 25);

    // �������
    list.printForward();  // �����30 -> 20 -> 25 -> 10 -> 40 -> 50 -> nullptr

    // �������
    list.printBackward();  // �����50 -> 40 -> 10 -> 25 -> 20 -> 30 -> nullptr

    // ɾ��Ԫ��
    list.remove(25);
    list.printForward();  // �����30 -> 20 -> 10 -> 40 -> 50 -> nullptr

    return 0;
}

