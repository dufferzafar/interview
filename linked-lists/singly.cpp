/**
 * Singly linked lists
 */

#include <iostream>
#include <string>


// What other namespaces exist?
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class SinglyLinkedList {
    Node<T>* head;
    Node<T>* tail;

    size_t _size;

    // What is this pattern called?
    // Bo Qian explained it in some video
    // Bitcoin's codebase also uses these SetNull type functions
    void SetNull() {
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

public:

    SinglyLinkedList() {
        SetNull();
    }

    SinglyLinkedList(initializer_list<T> init) {
        SetNull();

        for (auto &s : init)
            push_back(s);
    }

    ////////////////////////////////////////////////////////////

    // TODO: const reference?
    size_t size() {
        return _size;
    }

    void print(const Node<T>* p) {
        for(; p != nullptr; p = p->next) {

            cout << '"' << p->data << '"'
                 << (p->next != nullptr ? " -> " : "\n");
        }
    }

    void print() {
        print(head);
    }

    ////////////////////////////////////////////////////////////

    // TODO: Should return a pointer to the newly added node?
    void push_back(T data) {
        // new is required to ensure that node
        // isn't freed as soon as the function exits
        Node<T>* n = new Node<T>{data, nullptr};

        _size++;

        if (head == nullptr)
            head = n;
        else
            tail->next = n;

        tail = n;
    }

    void push_front(T data) {
        Node<T>* n = new Node<T>{data, nullptr};

        _size++;

        if (head == nullptr) {
            tail = n;
        } else {
            n->next = head;
        }

        head = n;
    }

};


int main() {

    // Implicitly uses the push_back methods
    SinglyLinkedList<string> LL {"Shadab", "duffer", "Zafar"};
    LL.push_front("Shadab"); LL.push_front("duffer"); LL.push_front("Zafar");
    cout << LL;

    SinglyLinkedList<int> LL_int {1,2,3,4,5};
    cout << LL_int;

    return 0;
}
