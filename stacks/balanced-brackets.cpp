#include <bits/stdc++.h>

using namespace std;

string isBalanced(string s) {

    // Pairs of brackets
    map<char, char> brackets = {
        {'[', ']'},
        {'{', '}'},
        {'(', ')'},
    };

    stack<char> stk;

    for (auto c : s) {

        if (brackets.count(c))              // c is an opening bracket
            stk.push(c);

        // Mistake 1: Was not checking for empty stack - when first character itself is a closing bracket!
        else if (!stk.empty() &&
                 c == brackets[stk.top()])  // c is a closing bracket
            stk.pop();                      // and is used correctly

        else
            return "NO";                    // c is a closing bracket used incorrectly!

    }

    // If the stack is empty - then brackets are balanced
    return (stk.empty() ? "YES" : "NO");
}
