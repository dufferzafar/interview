# Assignment 1 - RPS

## Problem Description & Requirements

Paper-Rock-Scissors (sic) is a game for two players.

Each player simultaneously opens his/her hand to display a symbol:
* Fist equals rock
* Open hand equals paper
* Showing the index and middle finger equals scissors.

The winner is determined by the following schema:
* paper beats (wraps) rock
* rock beats (blunts) scissors
* scissors beats (cuts) paper.

Write a Program that plays Paper-Scissors-Rock (sic) between the computer and a real player.

You should be able to play the game n times before the program exits.

## Design

```cpp
enum class Hand { Rock = 1, Paper, Scissors };

template <typename ChoiceStrategyT>
class Player {
    private: ChoiceStrategyT chooser;
    public: Hand choice() { return chooser.choice(); };
};

class NaiveChoiceStrategy { public: Hand choice() { return Hand::Rock; } };
class RandomChoiceStrategy { public: Hand choice() { return Hand(rand() % 3); } };
class HumanChoiceStrategy { public: Hand choice() { return Hand(console_choice); } };

template <typename Player1T, typename Player2T>
class Game {
    private: Player1T player1; Player2T player2;
    public: void play();
};

using HumanPlayer = Player<HumanChoiceStrategy>;
using BotRandomPlayer = Player<RandomChoiceStrategy>;
using BotNaivePlayer = Player<NaiveChoiceStrategy>;

Game<HumanPlayer, BotRandomPlayer> game;
game.play();

// While testing
Game<BotNaivePlayer, BotRandomPlayer> game;
game.play();
```

## Implementation
