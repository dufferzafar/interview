/**
 * Singly linked lists
 */

#include <iostream>
#include <string>


// What other namespaces exist?
using namespace std;

// TODO: Generalize the string type with a template?
struct Node {
    string data;
    Node* next;
};

class SinglyLinkedList {
    Node* head = nullptr;
    Node* tail = nullptr;

    size_t _size = 0;

public:

    size_t size() {
        return _size;
    }

    void print(const Node* p) {
        for(; p != nullptr; p = p->next) {

            cout << '"' << p->data << '"'
                 << (p->next != nullptr ? " -> " : "\n");
        }
    }

    void print() {
        print(head);
    }

    // TODO: Should return a pointer to the newly added node?
    void push_back(string data) {
        // new is required to ensure that node
        // isn't freed as soon as the function exits
        Node* n = new Node{data, nullptr};

        _size++;

        if (head == nullptr)
            head = n;
        else
            tail->next = n;

        tail = n;
    }

};


int main() {

    SinglyLinkedList LL;

    LL.push_back("Shadab");
    LL.push_back("duffer");
    LL.push_back("Zafar");

    LL.print();

    return 0;
}
