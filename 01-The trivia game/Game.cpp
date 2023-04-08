#include "Game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

enum class Category {
    Pop,
    Science,
    Sports,
    Rock,

    COUNT,
};

Game::Game()
    : places{}, purses{}, currentPlayer(0)
{
    questionsPerCategory.resize(Category::COUNT);

    for (int i = 0; i < 50; i++)
    {
        ostringstream oss(ostringstream::out);
        oss << "Pop Question " << i;

        popQuestions.push_back(oss.str());

        char str[255];
        sprintf(str, "Science Question %d", i);
        scienceQuestions.push_back(str);

        char str1[255];
        sprintf(str1, "Sports Question %d", i);
        sportsQuestions.push_back(str1);

        rockQuestions.push_back(createRockQuestion(i));
    }
}

string Game::createRockQuestion(int index)
{
    char indexStr[127];
    sprintf(indexStr, "Rock Question %d", index);
    return indexStr;
}

bool Game::isPlayable()
{
    return (howManyPlayers() >= 2);
}

bool Game::add(string playerName)
{
    places[howManyPlayers()] = Player
    {
        .name = playerName;
    };

    cout << playerName << " was added" << endl;
    cout << "They are player number " << players.size() << endl;
    return true;
}

int Game::howManyPlayers()
{
    return players.size();
}

/// Returns true iff the player escaped.
void Game::try_escape_penalyty_box()
{
    if (roll % 2 != 0)
    {
        isGettingOutOfPenaltyBox = true;
        cout << players[currentPlayer] << " is getting out of the penalty box" << endl;
    }
    else
    {
        cout << players[currentPlayer] << " is not getting out of the penalty box" << endl;
        isGettingOutOfPenaltyBox = false;
    }
}

void Game::move_player()
{
    places[currentPlayer] = places[currentPlayer] + roll;
    if (places[currentPlayer] > 11)
        places[currentPlayer] = places[currentPlayer] - 12;
    cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << endl;
}

void Game::play_turn_when_free()
{
    move_player();

    cout << "The category is " << currentCategory() << endl;
    askQuestion();
}

void Game::roll(int roll)
{
    cout << players[currentPlayer] << " is the current player" << endl;
    cout << "They have rolled a " << roll << endl;

    if (inPenaltyBox[currentPlayer])
    {
        try_escape_penalyty_box();
        if (!isGettingOutOfPenaltyBox)
            return;
    }
    play_turn_when_free();
}

void Game::askQuestion()
{
    auto& questions = questionsPerCategory[static_cast<int>(currentCategory())];

    cout << questions.front() << endl;
    questions.pop_front();
}

string Game::currentCategory()
{
    if (places[currentPlayer] % 4 == 0)
        return "Pop";
    if (places[currentPlayer] % 4 == 1)
        return "Science";
    if (places[currentPlayer] % 4 == 2)
        return "Sports";
    return "Rock";
}

bool Game::wasCorrectlyAnswered()
{
    if (inPenaltyBox[currentPlayer])
    {
        if (isGettingOutOfPenaltyBox)
        {
            cout << "Answer was correct!!!!" << endl;
            purses[currentPlayer]++;
            cout << players[currentPlayer]
                 << " now has "
                 << purses[currentPlayer]
                 << " Gold Coins." << endl;

            bool winner = didPlayerWin();
            currentPlayer++;
            if (currentPlayer == players.size())
                currentPlayer = 0;

            return winner;
        }
        else
        {
            currentPlayer++;
            if (currentPlayer == players.size())
                currentPlayer = 0;
            return true;
        }
    }
    else
    {
        cout << "Answer was corrent!!!!" << endl;
        purses[currentPlayer]++;
        cout << players[currentPlayer]
             << " now has "
             << purses[currentPlayer]
             << " Gold Coins." << endl;

        bool winner = didPlayerWin();
        currentPlayer++;
        if (currentPlayer == players.size())
            currentPlayer = 0;

            return winner;
    }
}

void Game::wrongAnswer()
{
        cout << "Question was incorrectly answered" << endl;
        cout << players[currentPlayer] << " was sent to the penalty box" << endl;
        inPenaltyBox[currentPlayer] = true;

        currentPlayer++;
        if (currentPlayer == players.size())
            currentPlayer = 0;
}

        bool Game::didPlayerWin()
        {
        return purses[currentPlayer] != 6;
        }