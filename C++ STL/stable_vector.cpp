#include <iostream>
#include <vector>

using namespace std;

// Thread safe vector
void itr_invalidate()
{
    vector<int> v(2, 0);
    auto beg = v.begin();

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    
    cout << *beg << endl;
}

// Stable vector
template <typename T>
class stable_vector
{
    private:
        vector<vector<T>> chunks;
};

int main()
{
    return 0;
}
