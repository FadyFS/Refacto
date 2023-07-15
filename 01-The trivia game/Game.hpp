#include <iostream>
#include <list>
#include <vector>
#include <array>
#ifndef GAME_H_
#define GAME_H_

class Game{

		private:
			std::vector<std::string> players;
			std::array<int, 6> places;
			std::array<int, 6>  purses;
			std::array<bool, 6> inPenaltyBox;
			std::list<std::string> popQuestions;
			std::list<std::string> scienceQuestions;
			std::list<std::string> sportsQuestions;
			std::list<std::string> rockQuestions;
			unsigned int currentPlayer;
			bool isGettingOutOfPenaltyBox; //Take it off and add condition to inPenaltyBox + too long name

		public:
			//Constructor
			Game();
			//Setters
    		void setPlayers(const std::vector<std::string>& players);
			void setPlaces(const std::array<int, 6>& places);
			void setPurses(const std::array<int, 6>& purses);
			void setInPenaltyBox(const std::array<bool, 6>& inPenaltyBox);
			void setPopQuestions(const std::list<std::string>& popQuestions);
			void setScienceQuestions(const std::list<std::string>& scienceQuestions);
			void setSportsQuestions(const std::list<std::string>& sportsQuestions);
			void setRockQuestions(const std::list<std::string>& rockQuestions);
			void setCurrentPlayer(const unsigned int& currentPlayer);
			void setIsGettingOutOfPenaltyBox(const bool& isGettingOutOfPenaltyBox);

			//Getters
			const std::vector<std::string>& getPlayers() const;
			const std::array<int, 6>& getPlaces() const;
			const std::array<int, 6>& getPurses() const;
			const std::array<bool, 6>& getInPenaltyBox() const;
			const std::list<std::string>& getPopQuestions() const;
			const std::list<std::string>& getScienceQuestions() const;
			const std::list<std::string>& getSportsQuestions() const;
			const std::list<std::string>& getRockQuestions() const;
			const unsigned int& getCurrentPlayer() const;
			const bool& getIsGettingOutOfPenaltyBox() const;


			std::string createRockQuestion(int index);
			std::string currentCategory();
			bool isPlayable();
			bool add(std::string playerName);
			bool wasCorrectlyAnswered(); //Repeat itself
			bool wrongAnswer(); //Repeat itself
			bool didPlayerWin(); //Repeat itself
			int howManyPlayers();
			void roll(int roll);
			void askQuestion();

};

#endif /* GAME_H_ */