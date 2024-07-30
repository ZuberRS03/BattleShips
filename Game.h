#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

using namespace std;

class Game{
private:
    Board player1Board; // plansza gracza 1
    Board player2Board; // plansza gracza 2
    Player player1; // gracz 1
    Player player2; // gracz 2
    int currentMove = 0; // 0 -  player 1, 1 - player 2

    /*
    * Funkcja zwracająca numeryczną część współrzędnych pola
    * @param string sfielID - całe współrzędne pola
    * @return int num - numeryczna część współrzędnych jako indeks
    */
    int getNumPart(std::string fieldID);

    /*
    * Funkcja zwracająca alfabetyczną część współrzędnych pola
    * Dokonuuje konwersji alfabetycznej części na numeryczny indeks
    * @param string sfielID - całe współrzędne pola
    * @return int alf - alfabetyczna część współrzędnych jako indeks
    */
    int getAlfPart(std::string fieldID);

public:
    // Konstruktor
    Game();

    void setPlayer(Player player, int playerNumber);

    /*
    * Funkcja kreatora pozycji przed grą
    * @param Player player - jeden z graczy, Board board - plansza gracza, int playerNumber - numer gracza
    * @return void
    */
    void setPlayerPosition(Player &player, Board &board, int playerNumber);

    /*
    * Funkcja startująca bitwę
    * @param void
    * @return void
    */
    void startBatle();

    /*
    * Funkcja wykonująca jeden ruch
    * Funkcja nie zmienia flagi ruchu
    * @param Player player - jeden z graczy, Board board - plansza gracza
    * @return int: 0 - gdy pudło, 1 - gdy trafienie, 2 - gdy pole już ostrzelane, 3 - gdy podana zła pozycja
    */
    int makeMove(Player &player, Board &board);

    /*
    * Funkcja startująca grę
    * @param void
    * @return void
    */
    void runGame();

    void runTest();
    void setTestPosition(Player &player, Board &board, int number);

    // Destruktor
    ~Game() {}
};

#endif // GAME_H