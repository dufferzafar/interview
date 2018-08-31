/*

    Generate all permutations of a string
    =====================================

TODO:
-----

    * Return a vector instead of printing.

    * Deal with repeating characters.

*/

#include <iostream>
#include <string>

using namespace std;

// TODO: Better variable names
void perm_help(string str, string prefix)
{
    // Could be simplified?
    if ( !str.length() )
    {
        if ( prefix.length() )
            cout << prefix;
        else
            return;
    }

    // Meat of the code
    for(size_t i = 0; i < str.length(); ++i)
    {
        // Remove i-th character from str

        // Append i-th character to prefix

        // Recurse down
        perm_help(str, prefix + str[i]);

        // Add i-th character back to str
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
