/*
Defines a class where two players play a game of rock-paper-scissors.

This could also be templated on a console-type so it could be replaced
with perhaps a GUI or a network interface?

What if we have more than 2 players?
*/
#include <iostream>

template <typename Player1T, typename Player2T, typename JudgeT>
class Game {
private:
  Player1T player1;
  Player2T player2;

public:
  Game(Player1T player1, Player2T player2) : player1(player1), player2(player2) {};
  void play() {
    auto h1 = player1.choice();
    std::cout << player1 << " chose: " << to_string(h1) << std::endl;

    auto h2 = player2.choice();
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
