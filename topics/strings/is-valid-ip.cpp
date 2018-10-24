/**
 * Validate an IP Address
 * https://practice.geeksforgeeks.org/problems/validate-an-ip-address/1
 *
 * ---
 *
 * The issue with such questions is that the input sepc is lame af.
 *
 * There will always be cases that you left out.
 */
#include <bits/stdc++.h>

using namespace std;

int isValid(char *ip)
{
    bool is_valid = true;

    string oct;
    int octv; int octc = 0;

    istringstream stream(ip);
    while (getline(stream, oct, '.')) {
        int octv = atoi(oct.c_str());

        if (oct.length() == 0) return false;
        if (oct.length() > 1 and octv == 0) return false;
        if (oct.length() > 1 and oct[0] == '0') return false;

        if (octv < 0 or octv > 255) return false;

        octc++;
    }

    if (octc != 4) return false;

    return is_valid;
}

bool valid_ip_bad(string ip) {

    bool is_valid = true;

    vector<int> octets;

    int oct; char dot;

    istringstream stream(ip);

    while (stream) {
        stream >> oct >> dot;
        octets.push_back(oct);
    }

    // for(auto oct : octets) cout << oct << " "; cout << endl;

    if ((int) octets.size() != 4)
        return false;

    for(auto oct : octets) {
        if (oct < 0 or oct > 255)
            return false;
    }

    return is_valid;

}

int main() {

    string ip = "192.168.0.1";
    cout << "Enter  IP: ";
    cin >> ip;

    cout << "Is valid: " << valid_ip(ip);

    return 0;
}
