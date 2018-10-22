/**
 * LeetCode: 8. String to Integer (atoi)
 *
 * https://leetcode.com/problems/string-to-integer-atoi/description/
 *
 * ---
 *
 * It had so many edge cases that if it came in an exam, I'm pretty sure
 * I won't be able to do it.
 */

class Solution {
public:
    int myAtoi(string str) {

        int n = str.length();
        int num = 0;
        int sign = 1;

        int ch;
        int digit = 0;
        int zero = '0', nine = '9';

        bool have_sign = false;
        bool have_num = false;

        for(int i = 0; i < n; ++i) {

            if (str[i] == ' ' && !have_num && !have_sign)
                continue;
            else if (str[i] == '+' && !have_sign && !have_num) {
                sign = 1;
                have_sign = true;
                continue;
            }
            else if (str[i] == '-' && !have_sign && !have_num) {
                sign = -1;
                have_sign = true;
                continue;
            }

            ch = str[i];

            if (ch < zero or ch > nine)
                break;

            digit = ch - zero;

            if (num > (INT_MAX / 10) || (num == (INT_MAX / 10) && digit > 7)) {

                if (sign == -1)
                    return INT_MIN;
                else
                    return INT_MAX;
            }

            num = (num * 10) + digit;

            have_num = true;
        }

        return sign * num;
    }
};
