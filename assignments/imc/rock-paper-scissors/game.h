/*
Defines a class where two players play a game of rock-paper-scissors.

This could also be templated on a console-type so it could be replaced
with perhaps a GUI or a network interface?

TODO: What if we have more than 2 players? How will the rules change?
*/

#include <iostream>

template <typename Player1T, typename Player2T, typename JudgeT>
class Game {
private:
  Player1T player1;
  Player2T player2;

  int draws{0};
  int player1Wins{0};
  int player2Wins{0};

public:
  Game(const Player1T& player1, const Player2T& player2)
      : player1(player1), player2(player2){};

  void play(int rounds = 1) {
    for (int i = 0; i < rounds; i++) {
      playImpl();
    }
    printScores();
  }

  void playImpl() {
    std::cout << "--------------------------------\n";

    auto h1 = player1.choice();
    std::cout << player1 << " chose: " << to_string(h1) << "\n";

    auto h2 = player2.choice();
    std::cout << player2 << " chose: " << to_string(h2) << "\n";

    uint result = JudgeT::judge(h1, h2);

    if (result == 0) {
      draws++;
      std::cout << "It's a draw!\n";
    } else if (result == 1) {
      player1Wins++;
      std::cout << player1 << " wins!\n";
    } else if (result == 2) {
      player2Wins++;
      std::cout << player2 << " wins!\n";
    }
  }

  void printScores() {
    std::cout << "\n"
              << "Rounds: " << draws + player1Wins + player2Wins << "\n"
              << "Final scores: " << player1 << " won " << player1Wins << ", "
              << player2 << " won " << player2Wins << ", "
              << draws << " were draws.\n";
  }
};
