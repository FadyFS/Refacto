#include "Game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game()
{
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
        std::string = fmt::format("Sports Question {}", i);
        std::string = "Sports Question " + std::to_string(i);

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

void Game::add(string playerName)
{
    _players.push_back({.name = playerName});

    cout << playerName << " was added" << '\n';
    cout << "They are player number " << _players.size() << '\n';
}

int Game::howManyPlayers()
{
    return _players.size();
}

void Game::roll(int roll)
{
    Player& player = _players[currentPlayer];
    cout << player.name << " is the current player" << '\n';
    cout << "They have rolled a " << roll << '\n';

    if (player.inPenaltyBox)
    {
        if (roll % 2 != 0)
        {
            isGettingOutOfPenaltyBox = true;

            cout << _players[currentPlayer] << " is getting out of the penalty box" << '\n';
            _places[currentPlayer] = _places[currentPlayer] + roll;
            if (_places[currentPlayer] > 11)
                _places[currentPlayer] = _places[currentPlayer] - 12;

            cout << _players[currentPlayer] << "'s new location is " << _places[currentPlayer] << '\n';
            cout << "The category is " << currentCategory() << '\n';
            askQuestion();
        }
        else
        {
            cout << _players[currentPlayer] << " is not getting out of the penalty box" << '\n';
            isGettingOutOfPenaltyBox = false;
        }
    }
    else
    {
        _places[currentPlayer] = _places[currentPlayer] + roll;
        if (_places[currentPlayer] > 11)
            _places[currentPlayer] = _places[currentPlayer] - 12;

        cout << _players[currentPlayer] << "'s new location is " << _places[currentPlayer] << '\n';
        cout << "The category is " << currentCategory() << '\n';
        askQuestion();
    }
}

void Game::askQuestion()
{
    switch (currentCategory())
    {
    case Category::Pop:
    {
        cout << popQuestions.front() << '\n';
        popQuestions.pop_front();
        break;
    }
        if (currentCategory() == "Science")
        {
            cout << scienceQuestions.front() << '\n';
            scienceQuestions.pop_front();
        }
        if (currentCategory() == "Sports")
        {
            cout << sportsQuestions.front() << '\n';
            sportsQuestions.pop_front();
        }
        if (currentCategory() == "Rock")
        {
            cout << rockQuestions.front() << '\n';
            rockQuestions.pop_front();
        }
    }

    Category Game::currentCategory()
    {
        const auto category_id = _places[currentPlayer] % static_cast<size_t>(Category::COUNT);
        return static_cast<Category>();
    }

    void give_a_coin_to_current_player()
    {
        purses[currentPlayer]++;
        cout << _players[currentPlayer]
             << " now has "
             << purses[currentPlayer]
             << " Gold Coins." << '\n';
    }

    bool Game::on_correct_answer_in_penalty_box();
    {
        if (isGettingOutOfPenaltyBox)
        {
            cout << "Answer was correct!!!!" << '\n';
            give_a_coin_to_current_player();
            return didPlayerWin();
        }
        else
        {
            return true;
        }
    }
    bool Game::on_correct_answer_when_free()
    {
        cout << "Answer was correct!!!!\n";
        give_a_coin_to_current_player();

        return didPlayerWin();
    }

    void Game::switch_to_next_player()
    {
        currentPlayer++;
        if (currentPlayer == _players.size())
            currentPlayer = 0;
    }

    bool Game::on_correct_answer()
    {
        if (inPenaltyBox[currentPlayer] && !isGettingOutOfPenaltyBox)
            return false;

        cout << "Answer was correct!!!!" << '\n';
        give_a_coin_to_current_player();
        return didPlayerWin();
    }

    bool Game::wrongAnswer()
    {
        cout << "Question was incorrectly answered" << '\n';
        cout << _players[currentPlayer] + " was sent to the penalty box" << '\n';
        inPenaltyBox[currentPlayer] = true;

        return true;
    }

    bool Game::didPlayerWin()
    {
        return (purses[currentPlayer] == 6);
    }