#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

// Drawdown is defined as the difference between some trade price for a symbol
// and some later trade price for the same symbol.
struct Trade {
  std::uint64_t timestamp;
  std::string symbol;
  double price;
};

// Would subscribe to trade events and pass each executed trade by to the
// provided functional object
void for_each_live_trade(const std::function<void(const Trade &)> &);

// Sends provided alert to Trade Ops team (would make them panic)
void send_alert_to_ops(std::string_view message);

// Provides threshold per symbol
double get_threshold(const std::string &symbol);

///////////////////////////////////////////////

class Monitor {

private:
  // Keep track of maximum prices
  std::unordered_map<std::string, double> maxPx;
//   std::unordered_set<std::string> alertSent;

  // std::unordered_map<std::string, pair<double, bool>> maxPx;

public:
  // Implement a callback function
  void callback(const Trade &trade) {
    // Keep track of max price so far
    if (maxPx.find(trade.symbol) != maxPx.end()) {
      maxPx[trade.symbol] = std::max(maxPx[trade.symbol], trade.price);
    } else {
      maxPx[trade.symbol] = trade.price;
      // maxPx.emplace(trade.symbol, false);
      // maxPx.emplace_hint(const_iterator pos, Args &&args...)
    }

    double drawdown = maxPx[trade.symbol] - trade.price;

    // When the current drawdown breaches the threshold
    if (drawdown > get_threshold(trade.symbol)) {
      if (!alertSent.contains(trade.symbol)) {
        // Decide when to send the alert
        send_alert_to_ops("ALERT!");
        alertSent.insert(trade.symbol);
      }
    }
  }
};

////////////////////////////////////////////////

// #include <monitor.h>
// #include <test_impl.h>

double get_threshold(const std::string &symbol) { return 5; }

// Could move these into a class of their own!
bool was_alert_called = false;
void send_alert_to_ops(std::string_view msg) { was_alert_called = true; }

// monitor_tests.cpp
void assert_true(const bool cond) {
  std::cout << (cond ? "SUCCESS" : "FAIL") << std::endl;
}

// fwd decl for test
// void callback(const Trade& trade);
class Monitor;

// threshold: 5
// symbols: [AAPL]
// prices: [100, 96]
// verify: no alert is sent
void test_1() {
  was_alert_called = false;

  Monitor m;
  auto t1 = Trade{0, "AAPL", 100};
  m.callback(t1);

  auto t2 = Trade{0, "AAPL", 96};
  m.callback(t2);

  assert_true(was_alert_called == false);
}

// threshold: 5
// symbols: [AAPL]
// prices: [90, 86]
// verify: no alert is sent
void test_2() {
  was_alert_called = false;

  Monitor m;

  auto t1 = Trade{0, "AAPL", 90};
  m.callback(t1);

  auto t2 = Trade{0, "AAPL", 84};
  m.callback(t2);

  assert_true(was_alert_called);
}

int main() {
  test_1();
  test_2();
  return 0;
}
// // monitor.cpp
// int main() {

//   for_each_live_trade(callback);
//   return 0;
// }
