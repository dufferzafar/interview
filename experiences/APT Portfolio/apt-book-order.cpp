#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

enum Side { BID = 0, ASK};

// TODO: Could make another regex
regex r1("(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)");

class OrderBook
{

public:
    uint getPrice(Side side, uint level) {
        return prices_[side][level];
    }

    uint getQuantity(Side side, uint level) {
        return quantities_[side][level];
    }
    uint getNumOrders(Side side, uint level) {
        return orders_[side][level];
    }

    void setup(string inp)
    {
        string lvl;
        istringstream stream(inp);

        string::size_type pos = 0;
        while((pos = inp.find("||", pos)) != string::npos) {
            inp.replace(pos, 2, "");
            pos += 1;
        }

        int lc = 0;
        while (getline(stream, lvl, ';'))
        {
            smatch m; string s;
            int o, bid, ask, q;

            if(regex_search(lvl, m, r1))
            {
                o = stoi(m[1].str());
                bid = stoi(m[2].str());
                ask = stoi(m[3].str());
                q = stoi(m[4].str());
            }

            lc++;
        }
    }

    vector<uint> prices_[2];
    vector<uint> quantities_[2];
    vector<uint> orders_[2];
};

#ifndef RunTests
int main()
{

    // \\s+pBID\\s+pASK\\s+
    string s = "1 100 101 2; 12 99 103 8; 16 97 104 3";

    OrderBook OB;
    OB.setup(s);

    string s = "1      1     100 || 101 2   1; 12 99 103 8; 16 97 104 3";

    OrderBook OB;
    OB.setup(s);


    return 0;
}
#endif
