/**
 * Playing with char* pointers.
 */

#include <bits/stdc++.h>
using namespace std;

int my_strlen(const char *s) {
    int l = 0;

    while(*s++ != '\0')
        l++;

    return l;
}

char* rot13(const char* s) {
    int len = my_strlen(s);
    char *r13 = new char[len];

    int i = 0;
    while(s[i] != '\0') {
        r13[i] = 'a' + (s[i] - 'a' + 13) % 26;
        i++;
    }

    r13[i] = '\0';

    return r13;
}

// Takes in a vector<string> - returns a char** array
char** vec2ch(int *cnt) {
    vector<string> VS {"abc", "def", "ghi"};

    int n = VS.size();

    char **ret = new char*[n];

    // Taking s by reference is important!
    for(auto &s : VS) {
        ret[(*cnt)++] = (char*) s.c_str();
    }

    return ret;
}

int main() {

    // Const needed because C++ 11
    const char *s = "shadab";

    // Simple functions that operat on a char*
    cout << s << "'s length: " << my_strlen(s) << endl;
    cout << s << "'s Rot 13: " << rot13(s) << endl;

    // Convert vector<string> to char**
    // cnt is required because there's no way of knowing
    // an array's length
    int cnt = 0; char** C = vec2ch(&cnt);

    // Print
    for(int i = 0; i < cnt; ++i)
        cout << C[i] << endl;

    // Manually declaring a char*
    const char** str = new const char*[3];
    str[0] = "foo"; str[1] = "bar"; str[2] = "baz";
    cout << str[0];

    return 0;
}
