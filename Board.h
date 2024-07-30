#ifndef BOARD_H
#define BOARD_H

#include "Field.h"
#include <iostream> 
#include <string>
#include <windows.h>

using namespace std;

class Board {
private:
    Field board[10][10]; // tablica obrazująca plansze

public:
    //Konstruktor
     Board();

    /*
    * Zmienia stan wskazanego pola
    * @param int num - numeryczna część indeksu
    * @param int alt - alfabetyczna część indeksu część indeksu, przerobiona wcześniej na numer
    * @param FieldState newState - nowy stan pola
    * @return void
    */
    void changeState(int num, int alf, FieldState newState);

    /*
    * Wyświetla w terminalu plansze w trakcie gry
    * Nie wyświetla pozycji statków
    * @param void
    * @return void
    */
    void PrintBoardInGame();

    /*
    * Wyświetla w terminalu plansze podczas ustawiania planszy
    * Wyświetla pozycje statków
    * @param void
    * @return void
    */
    void PrintBoardInSetings();

    /*
    * Funkcja ustawia określony statek zaczynająć od wybranych współrzędnych w określonej oreintacji
    * @param int x - pionowa współrzędna pola, int y - pozioma współrzędna pola, int shipSize - rozmiar statku, int orientation - (1 - jeśli pionowo, 0 - jeśli poziomo)
    * @return int: 1 - gdy wystąpiła kolizja, 0 - gdy wszystk osię udało
    */
    int setShipAt(int x, int y, int shipSize, int orientation);

    /*
    * Funkcja ususuwa określony statek zaczynająć od wybranych współrzędnych w określonej oreintacji
    * @param int x - pionowa współrzędna pola, int y - pozioma współrzędna pola, int shipSize - rozmiar statku, int orientation - (1 - jeśli pionowo, 0 - jeśli poziomo)
    * @return void
    */
    void removeShipAt(int x, int y, int shipSize, int orientation);

    /*
    * Funkcja symuluje strzał na konkretne pole 
    * @param int x - pionowa współrzędna pola, int y - pozioma współrzędna pola
    * @return int: -1 - gdy już ostrzelane, 0 - gdy pudło, 1 - gdy trafienie, 2 - gdy zatopienie
    */
    int shotAt(int x, int y);

    /*
    * Funkcja zaznacza wszystkie pola wokół zatopionego statku jako MISS 
    * @param int x - pionowa współrzędna pola, int y - pozioma współrzędna pola
    * @return void
    */
    void fillMiss(int x, int y);

    //Destruktor
    ~Board() {}
};

#endif //GAME_H