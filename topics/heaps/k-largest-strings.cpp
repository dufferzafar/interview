/**
 * Find the k largest strings in a stream.
 *
 * EPI problem: Heap Bootcamp
 *
 * Finding k largest elements is isomorphic to
 * removing n-k smallest elements.
 *
 * And since such an operation is supported by a min heap
 * that is what we use.
 *
 * ---
 *
 * What other methods are possible?
 */

#include <iostream>         // cout
#include <sstream>          // istringstream

#include <string>
#include <vector>

#include <queue>            // priority_queue
#include <functional>       // std::function

using namespace std;

// Even though a vector is returned by value - no copying will be performed!
// TODO: Learn about move semantics & other optimizations mentioned here:
// https://stackoverflow.com/questions/8384234/
vector<string> k_largest(int k, istringstream& iss) {

    // Take time to understand each part of this construction and why it is required
    priority_queue< string, vector<string>, function<bool(string, string)> >
        heap(

            [](const string& a, const string& b) {
                // min-heap requires > comparison
                return a.length() > b.length();
            }

        );

    // Process word by word
    string word;
    while(iss >> word) {

        // The heap isn't full yet
        if (heap.size() < k) {
            heap.push(word);
            continue;
        }

        // Only insert if word is actually large
        if ( word.length() > heap.top().length() ) {
            heap.pop();         // extract_min          O(log k)
            heap.push(word);    // insert & heapify     O(log k)
        }

        // Loop invariant:
        //      At any iteration, the heap contains k-largest strings seen so far.
    }

    // Convert the heap into an array so it can be sent back
    // Heaps don't support standard iterators
    // so, it needs to be destroyed :/
    vector<string> largest(k);
    while ( !heap.empty() ) {
        largest.push_back(heap.top());
        heap.pop();
    }

    return largest;
}

int main() {

    int k = 3;
    istringstream iss("This is a line which contains some text as a single sentence of a few words.");

    // Print the k-largest ones
    for (string s : k_largest(k, iss))
        cout << s << "\n";

}
