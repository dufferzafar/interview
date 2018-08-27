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

    // Initialises the list in reverse order
    Node n3{ "Zafar",  NULL };
    Node n2{ "duffer", &n3  };
    Node n1{ "Shadab", &n2  };

    print_list(&n1);

    // Initialises the list in forward order
    Node n1, n2, n3;
    n1 = (Node){ "Shadab", &n2 };
    n2 = (Node){ "duffer", &n3 };
    n3 = (Node){ "Zafar", NULL };

    print_list(&n1);

    return 0;
}
