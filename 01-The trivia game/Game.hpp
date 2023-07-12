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
			bool isGettingOutOfPenaltyBox;

		public:
			Game();
			std::string createRockQuestion(int index);
			bool isPlayable();
			bool add(std::string playerName);

			int howManyPlayers();
			void roll(int roll);

			private:
				void askQuestion();
				std::string currentCategory();

						public:
							bool wasCorrectlyAnswered();
							bool wrongAnswer();

		private:
			bool didPlayerWin();
};

#endif /* GAME_H_ */