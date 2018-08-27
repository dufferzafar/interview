/**
 * Singly linked lists
 */

#include <iostream>
#include <string>


// What other namespaces exist?
using namespace std;

// Per-node information
struct Node {
    string data;

    Node* next;
};

class SinglyLinkedList {
    Node* head; Node* tail;
};

void print_list(const Node* p) {
    for(; p != NULL; p = p->next) {
        cout << '"' << p->data << '"'
             << (p->next != NULL ? " -> " : "\n");
    };
}

int main() {

    // Initialize the list in reverse order
    Node n3{ "Zafar",  NULL };
    Node n2{ "duffer", &n3  };
    Node n1{ "Shadab", &n2  };

    print_list(&n1);

    // Initialize the list in forward order
    // Node n1, n2, n3;
    n1 = (Node){ "Shadab", &n2 };
    n2 = (Node){ "duffer", &n3 };
    n3 = (Node){ "Zafar", NULL };

    print_list(&n1);

    // Initialize with only head pointer
    Node* head = new Node{ "Shadab" };
    head->next = new Node{ "duffer" };
    head->next->next = new Node{ "Zafar" };

    print_list(head);

    return 0;
}
