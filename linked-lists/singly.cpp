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

    // Building a new linked list now
    Node* head = new Node();
    head->data = "Shadab";

    head->next = new Node();
    head->next->data = "duffer";

    head->next->next = new Node();
    head->next->next->data = "Zafar";

    // Print the list
    for(Node* p = head; p != NULL; p = p->next) {
        cout << '"' << p->data << '"'
             << (p->next != NULL ? " -> " : "\n");
    };

    return 0;
}
