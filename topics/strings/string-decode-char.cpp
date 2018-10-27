/**
 * Microsoft IIT Roorkee & IIT Kanpur (mittal!)
 *
 * Decode the string - inplace!

 * Given a character array number is mapped to corresponding alphabet and “_” is mapped to space.

 * If there is “#” after “#” it is number. There will be no “_” and “#” returned string.
 *
 * Sample Input  - 3 2 20_21 # 1 # 2_#11 4 @11
 * Sample Output - CBT U12 22D@H
 *
 * -----
 *
 * Learnings:
 *
 * 1. String literals are const char*
 * 2. They can't be modified - as they're stored in a read-only location (.TEXT / .DATA section?)
 * 3. char s[] is equivalent to char *s
 *
 */

#include <bits/stdc++.h>
using namespace std;

char* decode(char* s) {

    int i = 0, j = 0;
    bool num = false;

    while(s[i] != '\0') {

        if(s[i] == ' ') {
            i++;
        }

        else if (s[i] == '_') {
            s[j++] = ' ';
            i++;
        }

        else if (s[i] == '#') {
            num = true;
            i++;
        }

        else if (isdigit(s[i])) {

            string n;
            while(isdigit(s[i])) {
                n += s[i];
                i++;
            }

            if (num) {
                for(auto c : n)
                    s[j++] = c;
                num = false;
            }
            else
                s[j++] = 'A' + atoi(n.c_str()) - 1;
        }

        else {
            s[j++] = s[i++];
        }

    }

    s[j] = '\0';

    return s;
}



int main() {

    char s[] = "3 2 20_21 # 1 # 2_#11 4 @11";
    cout << s << endl;

    char* d = decode(s);
    cout << d << endl;

    // Gives: CBT U12 11D@K

    return 0;
}
