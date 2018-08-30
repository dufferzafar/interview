/**
 * Find the node where two linked lists merge
 *
 * https://hackerrank.com/challenges/find-the-merge-point-of-two-joined-linked-lists/
 *
 * Constraints:
 *
 *    1. Lists will merge
 *    2. head1 != head2
 *    3. head1, head2 != null
 *
 * Methods:
 *
 *    1. Length                :  What if length is equal? What if cycles?
 *    2. Hash data             :  What if two nodes have same data?
 *    3. Hash pointer address  :  Exposes some implementation detail
 */

#include <iostream>

#include <unordered_set>

#include "singly.h"

/**
 * @brief      Use the fact that nodes have unique addresses
 *
 * @return     Data of merge node
 */
template <typename T>
int find_merge_node_set(Node<T>* head1, Node<T>* head2) {
    unordered_set< Node<T>* > S;

    // Insert the entire first list
    for(auto h1 = head1; h1; h1 = h1->next) {
        S.insert(h1);
    }

    // Insert the second list, after checking?
    for(auto h2 = head2; h2; h2 = h2->next) {
        if (S.count(h2))
            return h2->data;
    }

    // If the lists merge at some point
    // control will never reach here
    return -1;
}

int main() {

    SinglyLinkedList<int> LL1{1,2,3,4};
    SinglyLinkedList<int> LL2{6,5};

    cout << LL1 << LL2;

    // Create merge node
    LL2.tail->next = LL1.tail;

    // Should print 4
    cout << "Data of merge node: " << find_merge_node_set(LL1.head, LL2.head);

    return 0;
}

///////////////////////////////////////////////////////////////

/**
 * @brief      Use lengths of two lists to find merge node
 *
 *             Only works when:
 *
 *                1.  Lists have no cycles
 *                2.  Length of lists is different
 *
 * @return     Data of merge node
 */
template <typename T>
int find_merge_node_length(Node<T>* head1, Node<T>* head2) {

    // Find lengths of both lists
    int l1 = 0, l2 = 0;
    for(auto h1 = head1; h1; h1 = h1->next, ++l1);
    for(auto h2 = head1; h2; h2 = h2->next, ++l2);

    // Find which list is longer
    int diff = 0;
    auto L = head1;
    if (l1 > l2) {
        diff = l1 - l2;
        L = head1;
    } else {
        diff = l2 - l1;
        L = head2;
    }

    // Move till the difference becomes 0
    for(; diff >= 0; --diff, L = L->next);

    cout << L->data;
}
