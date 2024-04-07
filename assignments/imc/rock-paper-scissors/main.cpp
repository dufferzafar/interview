#include <vector>

#include "player.h"
#include "game.h"

int main() {
  // Follows classic rules of Rock, Paper, Scissors
  using ClassicJudge = Judge<Hand, ClassicRules<Hand>>;
  using RockyJudge = Judge<Hand, RockWinsRules<Hand>>;

  using namespace Player;
  auto nb1 = NaiveBot("NaiveBot1");
  auto nb2 = NaiveBot("NaiveBot2");
  auto rb1 = RandomBot("RandomBot1");
  auto rb2 = RandomBot("RandomBot2");
  auto h = Human("Shadab");
  auto z = Human("Zafar");

  std::vector<Player::Variant> players = {nb1, nb2, rb1, rb2, h, z};

  // Bot vs Bot games
  Game<NaiveBot, NaiveBot, ClassicJudge>(nb1, nb2).play();
  Game<NaiveBot, RandomBot, ClassicJudge>(nb1, rb2).play();
  Game<RandomBot, RandomBot, ClassicJudge>(rb1, rb2).play();

  // Human vs Bot games
  Game<Human, RandomBot, RockyJudge>(h, rb1).play();
  Game<Human, Human, RockyJudge>(h, z).play();

  return 0;
}
