#include <bits/stdc++.h>

using namespace std;

// TODO: Decide which of these two is the month!
regex r1("([1-2]{1}\\d{3})\\/(\\d{2})\\/(\\d{2})");
regex r2("(\\d{2})\\/(\\d{2})\\/([1-2]{1}\\d{3})");
regex r3("(\\d{2})-(\\d{2})-([1-2]{1}\\d{3})");

// Output Format: YYYYMMDD

bool is_valid(int dd, int mm, int yyyy)
{
    if(mm < 1 || mm > 12)
        return false;

    if((mm == 2 && dd > 29) || dd < 1 || dd > 31)
        return false;

    return true;
}

class DateTransform
{
public:
    static vector<string> changeDateFormat(const vector<string>& dates)
    {
        vector<string> answer;

        for(auto d : dates)
        {
            smatch m; string s;

            int mm, dd, yyyy;

            if(regex_search(d, m, r1))
            {
                mm = stoi(m[2].str());
                dd = stoi(m[3].str());
                yyyy = stoi(m[1].str());

                if(!is_valid(dd, mm, yyyy)) continue;

                s = m[1].str() + m[2].str() + m[3].str();
            }

            else if(regex_search(d, m, r2))
            {
                mm = stoi(m[2].str());
                dd = stoi(m[1].str());
                yyyy = stoi(m[3].str());

                if(!is_valid(dd, mm, yyyy)) continue;

                s =  m[3].str() + m[2].str() + m[1].str();
            }

            else if(regex_search(d, m, r3))
            {
                mm = stoi(m[1].str());
                dd = stoi(m[2].str());
                yyyy = stoi(m[3].str());

                if(!is_valid(dd, mm, yyyy)) continue;

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
        // Good!
        "2010/03/30",
        "15/12/2016",
        "11-15-2012",

        // Bad!
        "20130720",
        "0001/89/13",
        "10/10/99",
        "25/25/1999"
    };

    for (auto const& fmt : DateTransform::changeDateFormat(dates))
        cout << fmt << endl;
}
#endif

