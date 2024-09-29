/**
Problem: Given multiple Parquet files, implement an out-of-memory merge join.

banknifty -> fut1, fut2, fut3 -> flat files

fut1.parquet (1M) -> ORDERS/EXECS for this particular future?

User -> start_time -> end_time, Give me all trades in order of timestamp from fut1, fut2, fut3.

using PF = ParquetFileIterator;

ParquetFileIterator operator++(PF f1, PF f2, Pf f3);
{
  // Sort the input files in order of timestamps
  // Merge & Sort - O(n) + O(nlgn)
  
  // Out of memory merge join
  priority_queue<pair<Trade, PF>, Comparator> heap(3);
  
  heap.insert(*f1.begin(), f1.begin());
  heap.insert(*f2.begin());
  heap.insert(*f3.begin());
  
  if (!heap.empty())
  {
    auto [trade, itr] = heap.top(); 
    heap.pop();
    
    heap.insert(*itr++)
    
  }
  else
  {
    return PF::end();
  }

}
**/

int main()
{
  
  return 0;
}

/**
Implement an out of memory sorted merge iterator for multiple parquet files.
**/

#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include <arrow/io/file.h>
#include <parquet/file_reader.h>
#include <parquet/stream_reader.h>

struct Trade {
  int timestamp{};
  int qty{};
  double price{};
  std::string symbol;
};

class MergedParquet {
public:
  MergedParquet(const std::vector<std::string> &file_paths) {
    for (const auto &path : file_paths) {
      if (!path.empty()) {
        auto file_reader = parquet::ParquetFileReader::OpenFile(path, false);
        auto stream = std::make_shared<parquet::StreamReader>(file_reader);

        // Rows in the stream are indexed from 0
        if (stream->current_row() < stream->num_rows()) {
          // Read the first row
          Trade trade;
          *stream >> trade.timestamp >> trade.qty >> trade.price >>
              trade.symbol;

          // Will have to read/skip all the fields before calling EndRow()
          stream->EndRow();

          // Add the trade to heap - uses timestamp to compare
          heap.emplace(trade, stream);
        }
      }
    }
  }

  class iterator {

  private:
    MergedParquet *mp;
    Trade current_trade;
    bool end;

  public:
    iterator(MergedParquet *parent, bool isEnd = false)
        : mp(parent), end(isEnd) {
      if (!end && (mp != nullptr) && !mp->heap.empty()) {
        current_trade = mp->heap.top().first;
      } else {
        end = true;
      }
    }

    iterator &operator++() {
      if ((mp != nullptr) && !mp->heap.empty()) {
        // Pop the trade with smallest timestamp
        auto [current_trade, stream] = mp->heap.top();
        mp->heap.pop();

        // Read the next trade from the corresponding stream
        if (stream->current_row() < stream->num_rows()) {
          Trade new_trade;
          *stream >> new_trade.timestamp >> new_trade.qty >> new_trade.price >>
              new_trade.symbol;
          stream->EndRow();
          mp->heap.emplace(new_trade, stream);
        }
      } else {
        end = true;
      }
      return *this;
    }

    bool operator==(const iterator &other) const {
      return mp == other.mp && end == other.end;
    }

    const Trade &operator*() const { return current_trade; }
  };

  iterator begin() { return {this}; }

  iterator end() { return {this, true}; }

private:
  using Item = std::pair<Trade, std::shared_ptr<parquet::StreamReader>>;
  class TimeStampComparator {
  public:
    bool operator()(const Item &lhs, const Item &rhs) {
      return lhs.first.timestamp > rhs.first.timestamp;
    }
  };
  std::priority_queue<Item, std::vector<Item>, TimeStampComparator> heap;
};

int main() {
  std::vector<std::string> file_paths = {"file1.parquet", "file2.parquet",
                                         "file3.parquet"};

  // Showcase the use of the merged iterator
  MergedParquet merged(file_paths);
  for (MergedParquet::iterator it = merged.begin(); it != merged.end(); ++it) {
    const Trade &trade = *it;
    std::cout << "Trade timestamp: " << trade.timestamp << std::endl;
    // std::cout << trade; // print other fields!
  }

  return 0;
}
