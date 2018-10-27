#include <bits/stdc++.h>

using namespace std;

// TODO: Decide which of these two is the month!
regex r1("([1-2]{1}\\d{3})\\/(\\d{2})\\/(\\d{2})");
regex r2("(\\d{2})\\/(\\d{2})\\/([1-2]{1}\\d{3})");
regex r3("(\\d{2})-(\\d{2})-([1-2]{1}\\d{3})");

// 2010/03/30
// 15/12/2016
// 11-15-2012
// 20130720

// Output Format: YYYYMMDD

class DateTransform
{
public:
    static vector<string> changeDateFormat(const vector<string>& dates)
    {
        vector<string> answer;

        for(auto d : dates)
        {
            smatch m; string s;

            int mm, dd;
            // int yyyy;

            if(regex_search(d, m, r1))
            {
                mm = stoi(m[2].str());
                dd = stoi(m[3].str());

                if(mm < 1 || mm > 12) continue;
                if(dd < 1 || dd > 31) continue;

                s =  m[1].str() + m[2].str() + m[3].str();
            }

            else if(regex_search(d, m, r2))
            {
                mm = stoi(m[2].str());
                dd = stoi(m[1].str());

                if(mm < 1 || mm > 12) continue;
                if(dd < 1 || dd > 31) continue;

                s =  m[3].str() + m[2].str() + m[1].str();
            }

            else if(regex_search(d, m, r3))
            {
                mm = stoi(m[1].str());
                dd = stoi(m[2].str());

                if(mm < 1 || mm > 12) continue;
                if(dd < 1 || dd > 31) continue;

                s =  m[3].str() + m[1].str() + m[2].str();
            }

            if (!s.empty()) answer.push_back(s);
        }

        return answer;
    }
};

#ifndef RunTests
int main()
{
    vector<string> dates = {
        "2010/03/30",
        "15/12/2016",
        "11-15-2012",
        "20130720",
        ""
    };

    for (auto const& fmt : DateTransform::changeDateFormat(dates))
        cout << fmt << endl;
}
#endif

