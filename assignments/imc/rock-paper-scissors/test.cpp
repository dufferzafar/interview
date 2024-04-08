/*
Showcases how each individual component of the game can be tested in isolation.
*/

#include <vector>

#include "game.h"
#include "player.h"

// Just for example, a ruleset where Player1 can only win if they play Rock
// and then it doesn't matter what Player2 picks!
template <typename HandT>
class RockWinsRules {
public:
  inline static const std::unordered_multimap<HandT, HandT> rules = {
      {HandT::Rock, /* beats */ HandT::Paper},
      {HandT::Rock, /* beats */ HandT::Scissors}};
};

using ClassicJudge = Judge<Hand, ClassicRules<Hand>>;
using RockyJudge = Judge<Hand, RockWinsRules<Hand>>;

// Add a CTAD deduction guide for Game defaulting to ClassicJudge
template <typename Player1, typename Player2>
Game(Player1, Player2) -> Game<Player1, Player2, ClassicJudge>;

int main() {
  using namespace Player;
  auto nb1 = NaiveBot("NaiveBot1");
  auto nb2 = NaiveBot("NaiveBot2");
  auto rb1 = RandomBot("RandomBot1");
  auto rb2 = RandomBot("RandomBot2");

  std::vector<Player::Variant> players = {nb1, nb2, rb1, rb2};

  // Bot vs Bot games with a fair judge
  Game(nb1, nb2).play(2);
  Game(nb1, rb2).play(2);
  Game(rb1, rb2).play(2);

  // Bot vs Bot games with a judge that favours Rock
  Game<NaiveBot, NaiveBot, RockyJudge>(nb1, nb2).play();
  Game<NaiveBot, RandomBot, RockyJudge>(nb1, rb2).play();
  Game<RandomBot, RandomBot, RockyJudge>(rb1, rb2).play();

  // Demonstrating the judge's behaviour
  assert(ClassicJudge::judge(Hand::Rock, Hand::Paper) == 2);
  assert(RockyJudge::judge(Hand::Rock, Hand::Paper) == 1);

  // We can even try out the components with a shorter hand set!
  // enum HandRP { Rock = 1, Paper = 2, SIZE = 3 };

  return 0;
}
