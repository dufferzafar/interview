/**
 * Reversal of a singly linked list
 *
 * Turned out to be surprisingly tricky.
 *
 * At first, I started with 2 pointers
 * then moved to 3.
 *
 * This was asked to me in Zomato's interview
 * on 27th September 2015
 */

#include <iostream>

#include "singly.h"


int main() {

    SinglyLinkedList<int> LL{1,2,3,4,5,6,7};

    // TODO: Handle empty case
    auto p1 = LL.head;
    auto p2 = LL.head;
    auto p3 = LL.head;

    // TODO: merge!
    // if(hare->next) {
    //     hare = hare->next;
    // }

    while(p3) {
        p2->next = p1;
        p1 = p2;
        p2 = p3;

        p3 = p3->next;
    }


    return 0;
}
