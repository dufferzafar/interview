/*

    Find if a number is palindromic.

*/

#include <iostream>
#include <math.h>

using namespace std;

int main() {

    int num;

    cout << "Enter a number: ";
    cin >> num;

    int num_digits  = floor(log10(num)) + 1;
    // Will overflow easily. Better way?
    int div = pow(10, num_digits - 1);

    bool ispalin = true;
    while (num) {
        int first = num / div;
        int last  = num % 10;

        ispalin &= (first == last);

        num = (num % div) / 10;
        div /= 100;
    }

    if (ispalin) {
        cout << num << " is a palindrome." ;
    }

    return 0;
}
