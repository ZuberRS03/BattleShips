#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Player{
private:
    string playerName; //nick gracza

    // Ile statków ma do dyspozycji przy ustawianiu
    int ship4 = 1;
    int ship3 = 2;
    int ship2 = 3;
    int ship1 = 4;

public:
    // Konstruktor
    Player(const string &playerName);

    Player() {}

    /*
    * Funkcja zwracająca nick gracza
    * @param void
    * @return playerName
    */
    string getPlayerName() const;

    /*
    * Funkcja ustawiająca nick gracza
    * @param playerName
    * @return void
    */
    void setPlayerName(string name);

    /*
    * Zestawy funkcji do zmieniania ilości dostępnych statków
    */
    int getCountShip4();
    void setCountShip4(int count);

    int getCountShip3();
    void setCountShip3(int count);

    int getCountShip2();
    void setCountShip2(int count);

    int getCountShip1();
    void setCountShip1(int count);

    void printAvailableShips();

    // Destruktor
    ~Player() {}
};

#endif // PLAYER_H