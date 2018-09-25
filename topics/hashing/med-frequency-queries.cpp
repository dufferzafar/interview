/**
 * https://www.hackerrank.com/challenges/frequency-queries/
 */
#include <bits/stdc++.h>

using namespace std;

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int>> queries) {

    vector<int> ans;

    unordered_map<long, long> fwd;   // fwd map: number -> freq

    // What if we only kept track of how many numbers there are of a particular frequency
    // Rather than keeping which numbers those are!?

    unordered_map<long, long > bwd;  // bwd map: freq -> count

    // long freq;

    for (auto query : queries) {
        long operation = query[0];
        long operand = query[1];

        switch(operation) {
            case 1: // Insert

                // if (freq && bwd.count(freq))
                bwd[fwd[operand]] -= 1;
                fwd[operand] += 1;
                bwd[fwd[operand]] += 1;

                break;

            case 2: // Delete

                // Just NOP if it doesn't already exist
                if (fwd.count(operand) && fwd[operand] > 0) {
                    bwd[fwd[operand]] -= 1;
                    fwd[operand] -= 1;
                    bwd[fwd[operand]] += 1;
                }

                break;

            case 3: // Check freq

                // If an integer with specified frequency exists
                // if (bwd[operand] > 0)
                if (bwd.count(operand) && bwd[operand] > 0)
                    ans.push_back(1);
                else
                    ans.push_back(0);

                break;
        }
    }

    return ans;
}
