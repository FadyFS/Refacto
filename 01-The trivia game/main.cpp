#include <stdlib.h>
#include "Game.hpp"

int main()
{
    srand(time(NULL));
    Game aGame;

    aGame.add("Chet");
    aGame.add("Pat");
    aGame.add("Sue");

    bool there_is_a_winner{false};
    do
    {
        aGame.roll(rand() % 5 + 1);

        if (rand() % 9 == 7)
        {
            aGame.wrongAnswer();
        }
        else
        {
            there_is_a_winner = !aGame.wasCorrectlyAnswered();
        }
    } while (!there_is_a_winner);
}