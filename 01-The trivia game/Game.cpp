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



Game::Game() : places{}, purses{}, currentPlayer(0){
	for (int i = 0; i < 50; i++)
	{
		std::ostringstream oss (std::ostringstream::out);
		oss << "Pop Question " << i;

		popQuestions.push_back(oss.str());

		char str[255];
		sprintf(str, "Science Question %d", i);
		scienceQuestions.emplace_back(str);

		char str1[255];
		sprintf(str1, "Sports Question %d", i);
		sportsQuestions.emplace_back(str1);

		rockQuestions.push_back(createRockQuestion(i));
	}
}

std::string Game::createRockQuestion(int index)
{
	char indexStr[127];
	sprintf(indexStr, "Rock Question %d", index);
	return indexStr;
}

bool Game::isPlayable()
{
	return (howManyPlayers() >= 2);
}

bool Game::add(std::string playerName){
	players.push_back(playerName);
	int players_num = howManyPlayers();
	places[players_num] = 0;
	purses[players_num] = 0;
	inPenaltyBox[players_num] = false;

	std::cout << playerName << " was added" << std::endl;
	std::cout << "They are player number " << players.size() << std::endl;
	return true;
}

void Game::roll(int roll)
{
    std::cout << players[currentPlayer] << " is the current player" << std::endl;
    std::cout << "They have rolled a " << roll << std::endl;

    if (inPenaltyBox[currentPlayer])
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

    places[currentPlayer] = places[currentPlayer] + roll;
    if (places[currentPlayer] > 11)
        places[currentPlayer] = places[currentPlayer] - 12;

    std::cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << std::endl;
    std::cout << "The category is " << currentCategory() << std::endl;
    askQuestion();
}


void Game::askQuestion()
{
	if (currentCategory() == "Pop")
	{
		std::cout << popQuestions.front() << std::endl;
		popQuestions.pop_front();
	}
	if (currentCategory() == "Science")
	{
		std::cout << scienceQuestions.front() << std::endl;
		scienceQuestions.pop_front();
	}
	if (currentCategory() == "Sports")
	{
		std::cout << sportsQuestions.front() << std::endl;
		sportsQuestions.pop_front();
	}
	if (currentCategory() == "Rock")
	{
		std::cout << rockQuestions.front() << std::endl;
		rockQuestions.pop_front();
	}
}


std::string Game::currentCategory()
{
    int currentPlace = places[currentPlayer];

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
	if (inPenaltyBox[currentPlayer])
	{
		if (isGettingOutOfPenaltyBox)
		{
			std::cout << "Answer was correct!!!!" << std::endl;
			purses[currentPlayer]++;
			std::cout << players[currentPlayer]
			     << " now has "
			     << purses[currentPlayer]
				<<  " Gold Coins." << std::endl;

			bool winner = didPlayerWin();
			currentPlayer++;
			if (currentPlayer == players.size()) currentPlayer = 0;

			return winner;
		}
		else
		{
			currentPlayer++;
			if (currentPlayer == players.size()) currentPlayer = 0;
			return true;
		}



	}
	else
	{

		std::cout << "Answer was corrent!!!!" << std::endl;
		purses[currentPlayer]++;
		std::cout << players[currentPlayer]
				<< " now has "
				<< purses[currentPlayer]
			<< " Gold Coins." << std::endl;

		bool winner = didPlayerWin();
		currentPlayer++;
		if (currentPlayer == players.size()) currentPlayer = 0;

		return winner;
	}
}

bool Game::wrongAnswer()
{
	std::cout << "Question was incorrectly answered" << std::endl;
	std::cout << players[currentPlayer] + " was sent to the penalty box" << std::endl;
	inPenaltyBox[currentPlayer] = true;

	currentPlayer++;
	if (currentPlayer == players.size()) currentPlayer = 0;
	return true;
}


bool Game::didPlayerWin()
{
	return !(purses[currentPlayer] == 6);
}