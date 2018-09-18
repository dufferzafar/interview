#include <bits/stdc++.h>

using namespace std;


// Complete the checkMagazine function below.
void checkMagazine(vector<string> magazine, vector<string> note) {

    // Convert a vector of words to a set!
    // Mistake 2: Was using set instead of a multiset
    unordered_multiset<string> mag_set(begin(magazine), end(magazine));

    for (auto word : note) {

        auto pos = mag_set.find(word);

        // If the word is not in magazine
        if (pos == mag_set.end()) {
            cout << "No";
            return;
        }

        // Mistake 1: Was not marking the word as being used
        else {
            mag_set.erase(pos);
        }

    }

    cout << "Yes";
}


// https://www.hackerrank.com/challenges/ctci-ransom-note/forum/comments/190910
bool ransom_note_cleaner(vector<string> magazine, vector<string> ransom) {
    /*
        Working of [] operator:

        If it does not match key of any element in the map, new element is created.
        Default allocator calls default constructor,
        default "constructor" int() returns 0.

        Otherwise, you could manually check that key doesn't exist
        and create new element initialized with 0.
    */

    unordered_map<string, int> words;
    for (auto &it: magazine)
        words[it]++;

    for (auto &it: ransom) {
        if (words[it]>0)
            words[it]--;
        else
            return false;
    }
    return true;
}
