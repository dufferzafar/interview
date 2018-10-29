
# LeetCode - Easy - Strings

## 709. To Lower Case

https://leetcode.com/problems/to-lower-case/description/

Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.

```cpp
class Solution {
public:
    string toLowerCase(string str) {
     
        if (str.empty()) return str;
        
        for(auto &ch : str) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = (char) ch - 'A' + 'a';
            }
        }
        
        return str;
    }
};
```

##  13. Roman to Integer

https://leetcode.com/problems/roman-to-integer/description/


```cpp
class Solution {
    map<char, int> val {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };
    
public:
    int romanToInt(string s) {
        int n = s.length();
        int v = 0;
        
        if (!n) return v;
        
        char last = s[n-1];
        v = val[last];
        
        // The trick is to start from right.
        for(int i = n-2; i >= 0; --i) {
            if (val[s[i]] < val[last])
                v -= val[s[i]];
            else
                v += val[s[i]];

            last = s[i];    
        }
        
        return v;
    }
};
```
