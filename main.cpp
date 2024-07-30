#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"

using namespace std;

int main() {
    Player player1("Gracz 1");
    Player player2("Gracz 2");

    Game game;
    game.setPlayer(player1, 1);
    game.setPlayer(player2, 2);

    //game.runTest();
    game.runGame();

    return 0;
}