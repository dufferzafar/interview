/*
Defines classes for Player & various choice strategies - naive, random, human!
*/

#include <iostream>
#include <string>
#include <variant>

#include "hand.h"

namespace ChoiceStrategy {

template <typename HandT>
class Naive {
public:
  static HandT choice() { return HandT(1); }
};

template <typename HandT>
class Random {
public:
  // TODO: Use C++ style random number generation
  static HandT choice() { return HandT(rand() % static_cast<int>(HandT::SIZE)); }
};

// Could be templated on the input console
// to provide input reading functionality
// template<typename ConsoleT>
template <typename HandT>
class Human {
public:
  static HandT choice() {
    // TODO: Allow a choice of R, P, S to be converted to Hand enum
    // std::cout << "What hand do you want to choose?" << std::endl
    //           << "[R]ock, [P]aper, [S]cissors" << std::endl;
    // char choice;
    // std::cin >> choice;

    std::cout << "What hand do you want to choose?" << std::endl
              << "[1] - Rock, [2] - Paper, [3] - Scissors" << std::endl;
    uint choice;
    std::cin >> choice;
    return HandT(choice);
  }
};
} // namespace ChoiceStrategy

namespace Player {

// This is the strategy design pattern implemented via templates
template <typename HandT, typename ChoiceStrategyT> class BasePlayer {
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

// This is our Public API. Put these in a namespace?
using Human = BasePlayer<Hand, ChoiceStrategy::Human<Hand>>;
using RandomBot = BasePlayer<Hand, ChoiceStrategy::Random<Hand>>;
using NaiveBot = BasePlayer<Hand, ChoiceStrategy::Naive<Hand>>;

using Variant = std::variant<NaiveBot, RandomBot, Human>;

} // namespace Player
