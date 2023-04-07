#include <stdlib.h>
#include <stdexcept>
#include "Game.hpp"

static bool notAWinner;

int main()
{

	srand(time(NULL));
	Game aGame;

	aGame.add("Chet");
	aGame.add("Pat");
	aGame.add("Sue");

    if (!aGame.isPlayable())
        throw std::runtime_error{"Not enough players to play."};

    do
    {
        aGame.roll(rand() % 5 + 1);

        if (rand() % 9 == 7)
        {
            notAWinner = !aGame.wrongAnswer();
        }
        else
        {
            notAWinner = !aGame.on_correct_answer();
        }
        switch_to_next_player();
    } while (notAWinner);
}