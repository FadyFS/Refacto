#include "Game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

//Setters
void Game::setPlayers(const std::vector<std::string>& players) {
	this->players = players;
}

void Game::setPlaces(const std::array<int, 6>& places) {
		this->places = places;
}

void Game::setPurses(const std::array<int, 6>& purses) {
	this->purses = purses;
}

void Game::setInPenaltyBox(const std::array<bool, 6>& inPenaltyBox) {
	this->inPenaltyBox = inPenaltyBox;
}

void Game::setPopQuestions(const std::list<std::string>& popQuestions) {
	this->popQuestions = popQuestions;
}

void Game::setScienceQuestions(const std::list<std::string>& scienceQuestions) {
	this->scienceQuestions = scienceQuestions;
}

void Game::setSportsQuestions(const std::list<std::string>& sportsQuestions) {
	this->sportsQuestions = sportsQuestions;
}

void Game::setRockQuestions(const std::list<std::string>& rockQuestions) {
	this->rockQuestions = rockQuestions;
}

void Game::setCurrentPlayer(const unsigned int& currentPlayer) {
	this->currentPlayer = currentPlayer;
}

void Game::setIsGettingOutOfPenaltyBox(const bool& isGettingOutOfPenaltyBox) {
	this->isGettingOutOfPenaltyBox = isGettingOutOfPenaltyBox;
}

//Getters 
const std::vector<std::string>& Game::getPlayers() const {
	return players;
}
const std::array<int, 6>& Game::getPlaces() const {
	return places;
}
const std::array<int, 6>& Game::getPurses() const {
	return purses;
}
const std::array<bool, 6>& Game::getInPenaltyBox() const {
	return inPenaltyBox;
}
const std::list<std::string>& Game::getPopQuestions() const {
	return popQuestions;
}
const std::list<std::string>& Game::getScienceQuestions() const {
	return scienceQuestions;
}
const std::list<std::string>& Game::getSportsQuestions() const {
	return sportsQuestions;
}
const std::list<std::string>& Game::getRockQuestions() const {
	return rockQuestions;
}
const unsigned int& Game::getCurrentPlayer() const {
	return currentPlayer;
}
const bool& Game::getIsGettingOutOfPenaltyBox() const {
	return isGettingOutOfPenaltyBox;
}



Game::Game() : places{}, purses{}, currentPlayer(0) {
	for (int i = 0; i < 50; i++) {
		std::ostringstream oss;
		oss << "Pop Question " << i;
		popQuestions.push_back(oss.str());

		std::ostringstream oss1;
		oss1 << "Science Question " << i;
		scienceQuestions.emplace_back(oss1.str());

		std::ostringstream oss2;
		oss2 << "Sports Question " << i;
		sportsQuestions.emplace_back(oss2.str());

		rockQuestions.push_back(createRockQuestion(i));
	}
}

std::string Game::createRockQuestion(int index) {
	std::ostringstream oss;
	oss << "Rock Question " << index;
	return oss.str();
}
int Game::howManyPlayers()
{
	return players.size();
}

bool Game::isPlayable()
{
	return (howManyPlayers() >= 2);
}

bool Game::add(const std::string& playerName){
	players.push_back(playerName);
	int players_num = howManyPlayers();
	places.at(players_num) = 0;
	purses.at(players_num) = 0;
	inPenaltyBox.at(players_num) = false;

	std::cout << playerName << " was added" << std::endl;
	std::cout << "They are player number " << players.size() << std::endl;
	return true;
}

void Game::roll(int roll)
{
    std::cout << players[currentPlayer] << " is the current player" << std::endl;
    std::cout << "They have rolled a " << roll << std::endl;

    if (inPenaltyBox.at(currentPlayer))
    {
        if (roll % 2 != 0)
        {
            isGettingOutOfPenaltyBox = true;
            std::cout << players[currentPlayer] << " is getting out of the penalty box" << std::endl;
        }
        else
        {
            std::cout << players[currentPlayer] << " is not getting out of the penalty box" << std::endl;
            isGettingOutOfPenaltyBox = false;
            return;  // Skip the common code for players in penalty box who don't get out
        }
    }

    places.at(currentPlayer) = places.at(currentPlayer) + roll;
    if (places.at(currentPlayer) > 11)
        places.at(currentPlayer) = places.at(currentPlayer) - 12;

    std::cout << players[currentPlayer] << "'s new location is " << places.at(currentPlayer) << std::endl;
    std::cout << "The category is " << currentCategory() << std::endl;
    askQuestion();
}


void Game::askQuestion()
{
    std::string category = currentCategory();
    std::list<std::string>* questionList = nullptr;

    if (category == "Pop")
    {
        questionList = &popQuestions;
    }
    else if (category == "Science")
    {
        questionList = &scienceQuestions;
    }
    else if (category == "Sports")
    {
        questionList = &sportsQuestions;
    }
    else if (category == "Rock")
    {
        questionList = &rockQuestions;
    }

    if (questionList && !questionList->empty())
    {
        std::cout << questionList->front() << std::endl;
        questionList->erase(questionList->begin());
    }
}



std::string Game::currentCategory()
{
    int currentPlace = places.at(currentPlayer);

    if (currentPlace == 0 || currentPlace == 4 || currentPlace == 8)
        return "Pop";
    else if (currentPlace == 1 || currentPlace == 5 || currentPlace == 9)
        return "Science";
    else if (currentPlace == 2 || currentPlace == 6 || currentPlace == 10)
        return "Sports";

    return "Rock";
}

bool Game::wasCorrectlyAnswered()
{
    if (inPenaltyBox.at(currentPlayer))
    {
        if (isGettingOutOfPenaltyBox)
        {
            incrementPlayerScore();
            bool winner = didPlayerWin();
            updateCurrentPlayer();
            return winner;
        }
        else
        {
            updateCurrentPlayer();
            return true;
        }
    }
    else
    {
        incrementPlayerScore();
        bool winner = didPlayerWin();
        updateCurrentPlayer();
        return winner;
    }
}

bool Game::wrongAnswer()
{
    std::cout << "Question was incorrectly answered" << std::endl;
    std::cout << players[currentPlayer] + " was sent to the penalty box" << std::endl;
    inPenaltyBox.at(currentPlayer) = true;

    updateCurrentPlayer();
    return true;
}

bool Game::didPlayerWin()
{
    return !(purses.at(currentPlayer) == 6);
}

void Game::incrementPlayerScore()
{
    std::cout << "Answer was correct!!!!" << std::endl;
    purses.at(currentPlayer)++;
    std::cout << players[currentPlayer] << " now has " << purses.at(currentPlayer) << " Gold Coins." << std::endl;
}

void Game::updateCurrentPlayer()
{
    currentPlayer++;
    if (currentPlayer == players.size())
        currentPlayer = 0;
}
