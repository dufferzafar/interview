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

    struct Node* next;
};

// class SinglyLinkedList {
//     struct Node* head;
//     struct Node* tail;
// }


int main() {

    // Building a new linked list node
    //
    // Option 1:
    //
    // Node* head = new Node();
    // head->data = "Shadab";
    //
    // Option 2:
    //
    // Node n1{ "Shadab" };
    // Node* head = &n1;
    //
    // Option 3:
    //
    // Node* head = & Node { "Shadab" };
    //
    // (i want this, but it doesn't work)
    // (it avoids creating a named temporary - n1)
    // (is, in principle, similar to the make_pair() function?)
    //
    // Option 4:
    //
    // Add a constructor to the struct
    // (don't want to do this, doesn't scale)

    // Initialises the list in reverse order
    Node n3{ "Zafar",  NULL };
    Node n2{ "duffer", &n3  };
    Node n1{ "Shadab", &n2  };

    Node* head = &n1;

    // Print the list
    for(Node* p = head; p != NULL; p = p->next) {
        cout << '"' << p->data << '"'
             << (p->next != NULL ? " -> " : "\n");
    };

    return 0;
}
