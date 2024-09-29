#include <iostream>
#include <queue>
#include <utility>
#include <tuple>
#include <math.h>
// #include <deque>
#include <optional>
using namespace std;

/*
We are building a component of a monitoring system, so we need to implement a queue-like data structure supporing the following operations:
1. Add a value to the back of the queue.
2. Remove a value from the front of the queue.
3. Get a mean value of all elements in the queue.

Now, we receive the updates to the same data structure from two different streams: incremental and snapshot.
The incremental stream contains the same updates as we had before: just single add/remove updates.
The snapshot stream contains updates with all the elements present in the queue at a specific point of time.

Additionally, each update (both incremental and snapshot) contains a sequence number.
Whenever there is a new incremental update, the sequence number is incremented by 1, so each incremental message has a unique sequence number.
A sequence number in a snapshot update means that the snapshot contains a correct state of the queue after applying all incremental updates
with sequence numbers less than or equal to the snapshot's sequence number.

We need the snapshot updates, because sometimes we lose some messages.
We want to use both incremental and snapshot updates to know what the current state of the queue is.
*/

class MyQueue{

private:
  std::deque<int> Q;
  std::deque<tuple<bool, int, long long>> outorder;
  // ooom;
  long long sum{0};
  // seqnum = 0 means an empty queue, all updates have seqnum > 0
  long long seqnum{0}, newseqnum{0};

public:

  // void applySnapshot(const std::deque<int>& snapshot, const long long& snap_seqnum)
  void applySnapshot(const std::vector<int>& snapshot, const long long& snap_seqnum)
  {
    // snapshot is older
    if (snap_seqnum <= seqnum)
      return;

    Q.clear();
    sum = 0;

    for (const auto& i : snapshot)
    {
      sum += i;
      Q.push_back(i);
    }

    seqnum = snap_seqnum;

    // 
    if (seqnum == newseqnum)
    {
      // Drain newer into Q
      while (!outorder.empty())
      {
        auto f = outorder.front();

      }
    }
  };

  void applyIncremental()
  {
    
  }

  long long getSeqnum() const {
    return seqnum;
  }

  void add(const int& val, const long long& incr_seqnum)
  {
    // snum = 7, (15)
    if (incr_seqnum > seqnum + 1)
    {
      outorder.emplace_back(true, val, incr_seqnum);
      return;
    }

    // incr_seqnum = seqnum + 1;
    Q.push_back(val);
    sum += val;
    seqnum = incr_seqnum;
  };

  void remove(const long long& incr_seqnum)
  {
    if (Q.empty())
    {
      return;
    }
    sum -= Q.front();
    Q.pop_front();
    seqnum = incr_seqnum;
  };

  // could later use expected as well
  std::optional<double> getMean() const
  {
    if (Q.empty())
    {
      return nullopt;
    }
    // cout << sum << "  " << Q.size() << endl;
    return static_cast<double>(sum) / Q.size();
  };

};

void assert(double actual, double expected)
{
  if (std::fabs(actual - expected) < 0.001)
  {
    cout << "ASSERT PASSED" << endl;
    return;
  }
  cout << "ASSERT FAILED: actual = " << actual << " expected = " << expected << endl;
}

int main() {
  MyQueue MQ;
  MQ.add(10, 1);
  MQ.add(11, 2);
  MQ.add(12, 3);
  MQ.add(13, 4);

  auto mn = MQ.getMean();
  assert(mn.value(), 11.5);

  vector<int> snap{11,12,13,14,15};
  MQ.applySnapshot(snap, 7);

  mn = MQ.getMean();
  assert(mn.value(), 13);

  return 0;
}
