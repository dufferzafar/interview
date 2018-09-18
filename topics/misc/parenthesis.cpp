/*
    Check if parenthesis are balanced.

    Uses STL Stack.
*/

#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main() {

    cout << "Enter a string: ";
    string str; cin >> str;

    stack <char> S;
    bool premature = false;

    // for (size_t i = 0; i < str.length(); ++i) {
    for (auto s = str.begin(); s < str.end() && !premature; ++s) {

        switch (*s) {
            case '(':
                S.push('(');
                break;
            case ')':
                if (!S.empty() && (S.top() == '('))
                    S.pop();
                else
                    premature = true;
                break;
        }

    }

    cout << endl
         << "Parenthesis are " << (S.empty() && !premature ? "" : "not ") << "balanced!";

    return 0;
}
