#pragma once

#include <iostream>
#include <list>
#include <vector>

struct Player {
    std::string name;

    int place{0};
    int purse{0};

    bool inPenaltyBox{false};
};

class Game {
private:
    Player players[6];

    std::vector<std::list<std::string>> questionsPerCategory;

    unsigned int currentPlayer;
    bool         isGettingOutOfPenaltyBox;

private:
    void   askQuestion();
    string currentCategory();

    bool didPlayerWin();

public:
    Game();
    string createRockQuestion(int index);
    bool   isPlayable();
    bool   add(string playerName);

    int  howManyPlayers();
    void roll(int roll);

    bool wasCorrectlyAnswered();
    bool wrongAnswer();
};
