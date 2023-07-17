#include <cstdlib>
#include <ctime>
#include <random>
#include "Game.hpp"

int main() {
    std::srand(std::time(nullptr));
    Game aGame;

    aGame.add("Chet");
    aGame.add("Pat");
    aGame.add("Sue");

    while (true) {
        aGame.roll(std::rand() % 5 + 1);

        if (std::rand() % 9 == 7) {
            if (!aGame.wrongAnswer()) {
                break;
            }
        } else {
            if (!aGame.wasCorrectlyAnswered()) {
                break;
            }
        }
    }
	return 0;
}
