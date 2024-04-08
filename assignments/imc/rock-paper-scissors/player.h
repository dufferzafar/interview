/*
Defines classes for Player & various choice strategies - naive, random, human!
*/

#include <iostream>
#include <string>
#include <variant>
#include <random>

#include "hand.h"

namespace ChoiceStrategy {

// All strategies have a static method choice that returns a Hand
// static is just used to indicate that there's no state in the class (yet!)
// if the requirement changes, we can remove static and make it a member function

template <typename HandT>
class Naive {
public:
  static HandT choice() { return HandT(1); }
};

template <typename HandT>
class Random {
private:
  static int randrange(int low, int high) {
    static std::default_random_engine re{};
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid{};
    return uid(re, Dist::param_type{low, high});
  }
public:
  static HandT choice() {
    return HandT(randrange(1, static_cast<int>(HandT::SIZE)-1));
  }
};

// Could be templated on the input console to provide input reading functionality
// template<typename ConsoleT>
template <typename HandT>
class Human {
public:
  static HandT choice() {
    std::cout << "\nWhat hand do you want to choose?\n";
    for (int i = 1; i < static_cast<int>(HandT::SIZE); i++) {
      std::cout << "[" << i << "] - " << to_string(HandT(i)) << "   ";
    }
    std::cout << "\n";
    uint choice;
    std::cin >> choice;
    return HandT(choice);
  }
};
} // namespace ChoiceStrategy

namespace Player {

template <typename HandT, typename ChoiceStrategyT>
class BasePlayer {
private:
  std::string name;

public:
  BasePlayer(std::string_view name) : name(name){};

  HandT choice() { return ChoiceStrategyT::choice(); };

  inline friend std::ostream &operator<<(std::ostream &os,
                                         const BasePlayer &player) {
    os << player.name;
    return os;
  }
};

// This is our Public API!
using Human = BasePlayer<Hand, ChoiceStrategy::Human<Hand>>;
using RandomBot = BasePlayer<Hand, ChoiceStrategy::Random<Hand>>;
using NaiveBot = BasePlayer<Hand, ChoiceStrategy::Naive<Hand>>;

using Variant = std::variant<NaiveBot, RandomBot, Human>;

} // namespace Player
