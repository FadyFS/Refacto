#include <iostream>
#include <list>
#include <vector>

#ifndef GAME_H_
#define GAME_H_

enum class Category {
    Pop,
    Science,
    Sports,
    Rock,

    COUNT,
};

struct Player {
    std::string name{""};
    int         place{0};
    int         purse{0};
    bool        inPenaltyBox{false};
}

class Game {
private:
    std::vector<Player> _players{};

    std::list<std::string> _popQuestions{};
    std::list<std::string> _scienceQuestions{};
    std::list<std::string> _sportsQuestions{};
    std::list<std::string> _rockQuestions{};

    unsigned int _currentPlayer{};
    bool         _isGettingOutOfPenaltyBox{};

public:
    Game();
    std::string createRockQuestion(int index);
    bool        isPlayable() const;
    bool        add(std::string playerName);

    int  howManyPlayers() const;
    void roll(int roll);

    /// Returns false iff the current player has won
    bool on_correct_answer();
    bool wrongAnswer();

private:
    void        askQuestion();
    std::string currentCategory();

    bool didPlayerWin();
};

#endif /* GAME_H_ */