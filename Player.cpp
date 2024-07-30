#include "Player.h"

HANDLE hOutPlayer;

Player::Player(const string &playerName) : playerName(playerName) {}

string Player::getPlayerName() const {
    return playerName;
}

int Player::getCountShip4(){
    return ship4;
}
void Player::setCountShip4(int count){
    this->ship4 = count;
}

int Player::getCountShip3(){
    return ship3;
}
void Player::setCountShip3(int count){
    this->ship3 = count;
}

int Player::getCountShip2(){
    return ship2;
}
void Player::setCountShip2(int count){
    this->ship2 = count;
}

int Player::getCountShip1(){
    return ship1;
}
void Player::setCountShip1(int count){
    this->ship1 = count;
}

void Player::printAvailableShips(){

    hOutPlayer = GetStdHandle( STD_OUTPUT_HANDLE );

    cout << "Dostepne statki: " << endl;
    cout << endl;

    cout << "Jedno-masztowce (1): ";
    if(getCountShip1() == 0){
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << getCountShip1() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } else {
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        cout << getCountShip1() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } 

    cout << "Dwu-masztowce (2): ";
    if(getCountShip2() == 0){
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << getCountShip2() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } else {
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        cout << getCountShip2() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    }

    cout << "Troj-masztowce (3): ";
    if(getCountShip3() == 0){
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << getCountShip3() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } else {
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        cout << getCountShip3() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } 

    cout << "Cztero-masztowiec (4): ";
        if(getCountShip4() == 0){
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << getCountShip4() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } else {
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        cout << getCountShip4() << endl;
        SetConsoleTextAttribute( hOutPlayer, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } 

    cout << endl;
}