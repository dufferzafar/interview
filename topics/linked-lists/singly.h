/**
 * Singly linked lists
 *
 * Function defintions are included in the header file itself.
 */

#include <iostream>         // istream, ostream
#include <stdexcept>        // underflow_error

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
public:
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

    SinglyLinkedList() {
        SetNull();
    }

    SinglyLinkedList(initializer_list<T> init) {
        SetNull();

        for (auto &s : init)
            push_back(s);
    }

    ////////////////////////////////////////////////////////////

    // TODO: public access to head, tail pointers?

    // Notice that 'const' is placed at the end to denote
    // that this function won't modify state?
    void print(ostream& out, const Node<T>* p) const {
        for(; p != nullptr; p = p->next) {

            out << '"' << p->data << '"'
                 << (p->next != nullptr ? " -> " : "\n");
        }
    }

    // ostream is a superclass of iostream & ostringstream
    // LL is marked 'const' to ensure it won't be modified
    friend ostream& operator<<(ostream& out, const SinglyLinkedList<T>& LL) {
        LL.print(out, LL.head);
        return out;
    }

    ////////////////////////////////////////////////////////////

    // LL is *not* marked 'const' as it has to modified
    friend istream& operator>>(istream& inp, SinglyLinkedList<T>& LL) {
        string word;
        while(inp >> word)
            LL.push_back(word);

        return inp;
    }

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

    ////////////////////////////////////////////////////////////

    // Should return data of the node being popped?
    void pop_front() {
        if (!head)
            throw underflow_error("List is empty");
    }

    void pop_back() {
        Node<T>* p = head;

        while(p != tail)   // Alternative: for(; p != tail; p = p->next);
            p = p->next;   // but p can't be declared in loop, because scope

        tail = p;
    }

};
