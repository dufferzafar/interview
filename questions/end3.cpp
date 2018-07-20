/*
    Every number ending with 3 has a number consisting of all 1s that it perfectly divides.
*/

#include <iostream>

using namespace std;

int main() {

    unsigned int ans = 1;
    unsigned int num3;

    cout << "Enter a number ending with 3: ";
    cin >> num3;

    if (num3 % 10 != 3) {
        cerr << num3 << " doesn't end with 3" << endl;
        return 1;
    }

    // TODO: Quickly starts to "hang"; better way?

    // Keep appending 1s till the answer becomes divisble by the given number.
    while (ans % num3) {
        ans = 10 * ans + 1;
    }

    cout << num3 << " perfectly divides " << ans;

    return 0;
}
