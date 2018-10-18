/*

    Generate all permutations of a string
    =====================================

Todo

    * Return a vector instead of printing.

    * Deal with repeating characters.

*/

#include <iostream>
#include <string>

using namespace std;

// TODO: Better variable names
void perm_help(string inp, string solution) {
    // Could be simplified?
    if ( !inp.length() )
    {
        if ( solution.length() )
            cout << solution;
        else
            return;
    }

    // Meat of the code
    for(size_t i = 0; i < inp.length(); ++i)
    {
        // Remove i-th character from inp

        // Append i-th character to prefix

        // Recurse down
        perm_help(inp, solution + inp[i]);

        // Add i-th character back to inp
    }
}

////////////////////////////

void permutations(string inp) {
    perm_help(inp, "");
}

////////////////////////////

int main() {

    permutations("AHI");

    return 0;
}
