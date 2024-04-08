#include "game.h"
#include "player.h"

int main() {
  std::cout << "Welcome to Rock, Paper, Scissors! "
            << "You will be playing against a Computer.\n"
            << "How many rounds do you want to play?\n";
  int rounds;
  std::cin >> rounds;

  // Two players: Human vs Computer
  using namespace Player;
  auto c = RandomBot("Computer");
  auto h = Human("Shadab");

  // A Judge that follows classic rules of Rock, Paper, Scissors
  using ClassicJudge = Judge<Hand, ClassicRules<Hand>>;

  Game<Human, RandomBot, ClassicJudge>(h, c).play(rounds);

  // To play against another human:
  // auto z = Human("Zafar");
  // Game<Human, Human, ClassicJudge>(h, z).play();

  return 0;
}
