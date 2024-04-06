#include <iostream>
#include <string>

// Should each hand be a separate class?
// So we can have a common interface for all hands?
enum class Hand { Rock = 1, Paper, Scissors };

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

// This is the strategy design pattern implemented via templates
template <typename ChoiceStrategyT> class Player {
private:
  ChoiceStrategyT chooser;

public:
  Hand choice() { return chooser.choice(); };
};

// Should this be templated on the Hand enum?
// So we can test it out with a smaller hand of 1/2 options?
class NaiveChoiceStrategy {
public:
  Hand choice() { return Hand::Rock; }
};

class RandomChoiceStrategy {
public:
  Hand choice() {
    // TODO: Use C++ style random number generation
    return Hand(rand() % 3);
  }
};

// Could be templated on the input console
// to provide input reading functionality
// template<typename ConsoleT>
class HumanChoiceStrategy {
public:
  Hand choice() {
    // TODO: Allow a choice of R, P, S to be converted to Hand enum
    // std::cout << "What hand do you want to choose?" << std::endl
    //           << "[R]ock, [P]aper, [S]cissors" << std::endl;
    // char choice;
    // std::cin >> choice;

    std::cout << "What hand do you want to choose?" << std::endl
              << "[1] - Rock, [2] - Paper, [3] - Scissors" << std::endl;
    uint choice;
    std::cin >> choice;

    return Hand(choice);
  }
};

// https://stackoverflow.com/a/28206799
// This prints underlying integers!
template <typename T>
std::ostream &operator<<(
    typename std::enable_if<std::is_enum<T>::value, std::ostream>::type &stream,
    const T &e) {
  return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

// Could be templated on the console as that could be replaced
// with perhaps a GUI or a network interface!
// What if we have more than 2 players?
template <typename Player1T, typename Player2T> class Game {
private:
  Player1T player1;
  Player2T player2;

public:
  void play() {
    Hand h1 = player1.choice();
    Hand h2 = player2.choice();

    std::cout << "Player 1 chose: " << to_string(h1) << std::endl;
    std::cout << "Player 2 chose: " << to_string(h2) << std::endl;

    if (h1 == h2) {
      std::cout << "It's a tie!" << std::endl;
    } else if ((h1 == Hand::Rock && h2 == Hand::Scissors) ||
               (h1 == Hand::Paper && h2 == Hand::Rock) ||
               (h1 == Hand::Scissors && h2 == Hand::Paper)) {
      std::cout << "Player 1 wins!" << std::endl;
    } else {
      std::cout << "Player 2 wins!" << std::endl;
    }
  }
};

int main() {
  using HumanPlayer = Player<HumanChoiceStrategy>;
  using BotRandomPlayer = Player<RandomChoiceStrategy>;
  using BotNaivePlayer = Player<NaiveChoiceStrategy>;

  // Bot vs Bot games
  Game<BotNaivePlayer, BotNaivePlayer>().play();
  Game<BotNaivePlayer, BotRandomPlayer>().play();
  Game<BotRandomPlayer, BotRandomPlayer>().play();

  // Human vs Bot games
  Game<HumanPlayer, BotRandomPlayer>().play();
  Game<HumanPlayer, HumanPlayer>().play();

  return 0;
}
