#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
// #include <cctype>
using namespace std;

struct Job {
    int job_id;
    int time;
    int nxt_id;
};

struct Chain {
    int sjob;
    int ljob;
    int njobs;
    int time;

    string format_time(int seconds) const {
        int hours = seconds / 3600;
        seconds %= 3600;
        int minutes = seconds / 60;
        seconds %= 60;
        ostringstream ss;
        ss << setw(2) << setfill('0') << hours << ":"
           << setw(2) << setfill('0') << minutes << ":"
           << setw(2) << setfill('0') << seconds;
        return ss.str();
    }
};

bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

int main() {
    string line, hdr;

    // Read the header line
    unordered_map<string, int> hdrMap;
    istringstream hdrStream(hdr);
    getline(cin, hdr);
    string fieldName;
    int hidx = 0;
    while (getline(hdrStream, fieldName, ',')) {
      fieldName.erase(remove(fieldName.begin(), fieldName.end(), ' '),
                      fieldName.end());
      hdrMap[fieldName] = hidx++;
    }

    if (hdrMap.size() != 3 || hdrMap.find("job_id") == hdrMap.end() ||
        hdrMap.find("runtime_in_seconds") == hdrMap.end() || hdrMap.find("nxt_id") == hdrMap.end()) {
        cerr << "Error: Incorrect header fields" << endl;
        return 1;
    }

    unordered_set<int> existingJobIds;
    unordered_map<int, Job> jobs;
    vector<Chain> chains;

    // Read job details from standard input
    while (getline(cin, line)) {
        if (line.empty()) continue;  // Skip empty lines

        istringstream ss(line);
        string field;
        Job job;
        vector<string> fields(3);

        for (int i = 0; i < 3 && getline(ss, field, ','); i++) {
            fields[i] = field;
        }

        if (fields.size() < 3) {
            cerr << "Error: Missing fields in data row" << endl;
            return 1;
        }

        try {
            if (!isNumber(fields[hdrMap["job_id"]]) 
                || !isNumber(fields[hdrMap["runtime_in_seconds"]]) 
                || !isNumber(fields[hdrMap["nxt_id"]])) {
                cerr << "Error: Non-integer values in fields" << endl;
                return 1;
            }

            job.job_id = stoi(fields[hdrMap["job_id"]]);
            job.time = stoi(fields[hdrMap["runtime_in_seconds"]]);
            job.nxt_id = stoi(fields[hdrMap["nxt_id"]]);

            if (existingJobIds.find(job.job_id) != existingJobIds.end()) {
                cerr << "Error: Duplicate job_id detected" << endl;
                return 1;
            }
            existingJobIds.insert(job.job_id);

            jobs[job.job_id] = job;
        } catch (...) {
            cerr << "Error: Malformed input processing" << endl;
            return 1;
        }
    }

    // Identify and construct chains
    unordered_map<int, bool> isNotStart;
    for (const auto& entry : jobs) {
        if (entry.second.nxt_id != 0) {
            if (jobs.find(entry.second.nxt_id) == jobs.end()) {
                cerr << "Error: nxt_id points to a non-existent job" << endl;
                return 1;
            }
            isNotStart[entry.second.nxt_id] = true;
        }
    }

    for (const auto& entry : jobs) {
        if (isNotStart.find(entry.first) == isNotStart.end()) { // Start of a chain
            int cid = entry.first;
            Chain chain;
            chain.sjob = cid;
            chain.time = 0;
            chain.njobs = 0;

            while (cid != 0) {
                chain.time += jobs[cid].time;
                chain.njobs++;
                chain.ljob = cid;
                cid = jobs[cid].nxt_id;
            }

            chains.push_back(chain);
        }
    }

    // Sort chains by total runtime descending
    sort(chains.begin(), chains.end(), [](const Chain& a, const Chain& b) {
        return a.time > b.time;
    });

    // Output the chains
    for (const auto& chain : chains) {
        cout << "sjob: " << chain.sjob << "\n";
        cout << "ljob: " << chain.ljob << "\n";
        cout << "njobs: " << chain.njobs << "\n";
        cout << "job_chain_runtime: " << chain.format_time(chain.time) << "\n";
        cout << "average_job_time: " << chain.format_time(chain.time / chain.njobs) << "\n\n";
    }

    return 0;
}
