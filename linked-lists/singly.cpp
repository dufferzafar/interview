/**
 * Singly linked lists
 */

#include <iostream>         // cin, cout
#include <sstream>          // istringstream, ostringstream

#include <string>

#include "singly.h"

using namespace std;

int main() {

    // Test constructor, push_back
    SinglyLinkedList<string> LL {"push", "back"};

    // Test push_front
    LL.push_front("in"); LL.push_front("reverse");

    // Test print, operator<< with ostream
    cout << LL;

    // Test operator<< with ostringstream
    ostringstream os;
    os << LL; cout << os.str();

    // Test template with int
    SinglyLinkedList<int> LL_int {1,2,3,4,5};
    cout << LL_int;

    // Test operator>> with istringstream
    SinglyLinkedList<string> LL_stream;
    istringstream inp("this is a line");
    inp >> LL_stream; cout << LL_stream;

    // Test operator>> with istream
    // Enter a line and press ctrl+d (for EOF)
    // cin >> LL_stream; cout << LL_stream;

    SinglyLinkedList<char> LL_c;
    LL_c.pop_front();

    return 0;
}
