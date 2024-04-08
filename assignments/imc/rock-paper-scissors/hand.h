/*
Defines classes for Hand, Rules & Judge!
*/

#include <string>
#include <sys/types.h>
#include <unordered_map>

#include <cassert>
#include <iostream>

// Should each hand be a separate class?
// So we can have a common interface for all hands?
enum class Hand { Rock = 1, Paper = 2, Scissors = 3, SIZE = 4 };

// Or hand could be a class that mimics an enum but this representation can stay close to it?
inline std::string to_string(Hand c) {
  switch (c) {
  case Hand::Rock:
    return "Rock 🪨";
  case Hand::Paper:
    return "Paper 📰";
  case Hand::Scissors:
    return "Scissors ✂️";
  default: {
    // TODO: What is the right thing to do in this case?
    // TODO: This should be handled in the Hand() constructor so it possible to create a Hand that's not in the enum!
    assert(0);
    return "";
  }
  }
}

template <typename HandT>
class ClassicRules {
public:
  // C++17 inline static -
  // https://en.cppreference.com/w/cpp/language/static#Static_data_members
  inline static const std::unordered_multimap<HandT, HandT> rules = {
      {HandT::Rock, /* beats */ HandT::Scissors},
      {HandT::Paper, /* beats */ HandT::Rock},
      {HandT::Scissors, /* beats */ HandT::Paper}};
};

template <typename HandT, typename RulesT>
class Judge {
public:
  static uint judge(HandT h1, HandT h2) {
    if (h1 == h2) {
      return 0;
    }
    auto range = RulesT::rules.equal_range(h1);
    for (auto it = range.first; it != range.second; ++it) {
      if (it->second == h2) {
        return 1;
      }
    }
    return 2;
  }
};
