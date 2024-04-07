/*
Defines classes for Hand, Rules & Judge!
*/

#include <string>
#include <sys/types.h>
#include <unordered_map>

// Should each hand be a separate class?
// So we can have a common interface for all hands?
// https://stackoverflow.com/questions/57346118/enum-class-constructor-c-how-to-pass-specific-value
enum class Hand { Rock = 1, Paper = 2, Scissors = 3, SIZE = 3 };

// Hand should be a class so this representation can stay close to it?
inline std::string to_string(Hand c) {
  switch (c) {
  case Hand::Rock:
    return "Rock";
  case Hand::Paper:
    return "Paper";
  case Hand::Scissors:
    return "Scissors";
  default: {
    // assert(0);
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

// Just for example, a ruleset where Rock always wins
template <typename HandT>
class RockWinsRules {
public:
  inline static const std::unordered_multimap<HandT, HandT> rules = {
      {HandT::Rock, /* beats */ HandT::Paper},
      {HandT::Rock, /* beats */ HandT::Scissors}};
};

template <typename HandT, typename RulesT>
class Judge {
public:
  static uint judge(HandT h1, HandT h2) {
    if (h1 == h2) {
      return 0;
    }
    auto it = RulesT::rules.find(h1);
    if (it != RulesT::rules.end() && it->second == h2) {
      return 1;
    } else {
      return 2;
    }
  }
};
