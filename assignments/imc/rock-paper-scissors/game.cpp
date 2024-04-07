#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>

// Should each hand be a separate class?
// So we can have a common interface for all hands?
// https://stackoverflow.com/questions/57346118/enum-class-constructor-c-how-to-pass-specific-value
enum class Hand { Rock = 1, Paper = 2, Scissors = 3, SIZE = 3 };

// Hand should be a class so this representation can stay close to it?
std::string to_string(Hand c) {
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

// This is the strategy design pattern implemented via templates
template <typename ChoiceStrategyT>
class Player {
private:
  std::string name;
public:
  Player (std::string_view name) : name(name) {};

  Hand choice() { return ChoiceStrategyT::choice(); };

  inline friend std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << player.name;
    return os;
  }
};

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

// Could be templated on the console as that could be replaced
// with perhaps a GUI or a network interface!
// What if we have more than 2 players?
template <typename Player1T, typename Player2T, typename JudgeT>
class Game {
private:
  Player1T player1;
  Player2T player2;

public:
  Game(std::string_view name1, std::string_view name2) : player1(name1), player2(name2) {};
  void play() {
    Hand h1 = player1.choice();
    std::cout << player1 << " chose: " << to_string(h1) << std::endl;

    Hand h2 = player2.choice();
    std::cout << player2 << " chose: " << to_string(h2) << std::endl;

    uint result = JudgeT::judge(h1, h2);
    if (result == 0) {
      std::cout << "It's a draw!" << std::endl;
    } else if (result == 1) {
      std::cout << player1 << " wins!" << std::endl;
    } else if (result == 2) {
      std::cout << player2 << " wins!" << std::endl;
    }

    std::cout << std::endl;
  }
};

int main() {
  using Human = Player<ChoiceStrategy::Human<Hand>>;
  using RandomBot = Player<ChoiceStrategy::Random<Hand>>;
  using NaiveBot = Player<ChoiceStrategy::Naive<Hand>>;

  // Follows classic rules of Rock, Paper, Scissors
  using ClassicJudge = Judge<Hand, ClassicRules<Hand>>;
  using RockyJudge = Judge<Hand, RockWinsRules<Hand>>;

  // Bot vs Bot games
  Game<NaiveBot, NaiveBot, ClassicJudge>("NaiveBot1", "NaiveBot2").play();
  Game<NaiveBot, RandomBot, ClassicJudge>("NaiveBot", "RandomBot").play();
  Game<RandomBot, RandomBot, ClassicJudge>("RandomBot1", "RandomBot2").play();

  // Human vs Bot games
  Game<Human, RandomBot, RockyJudge>("Shadab", "Computer").play();
  Game<Human, Human, RockyJudge>("Shadab", "Zafar").play();

  return 0;
}
