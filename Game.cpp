#include "Game.h"
#include <iostream>
#include <string>
#include <limits>
#include <windows.h>

HANDLE hOutGame;

bool checkPosition(string position){
    // Sprawdzanie długości
    if(position.length() > 3){
        return false;
    }

    // Sprawdzanie pierwszego członu
    if(position[0] != 'a' && position[0] != 'b' && position[0] != 'c' && position[0] != 'd' && position[0] != 'e' 
    && position[0] != 'f' && position[0] != 'g' && position[0] != 'h' && position[0] != 'i' && position[0] != 'j'){
        return false;
    }

    position.erase(0,1);
    if(position != "1" && position != "2" && position != "3" && position != "4" && position != "5" 
    && position != "6" && position != "7" && position != "8" && position != "9" && position != "10"){
        return false;
    }

    return true;
}

Game::Game() {}

int Game::getNumPart(string fieldID){
    fieldID.erase(0,1);
    int num = stoi(fieldID);
    return num;

}
int Game::getAlfPart(string fieldID){
    char alfPart = fieldID[0];
    int alf = alfPart - 96;
    return alf;
}

void Game::setPlayer(Player player, int playerNumber) {
    if (playerNumber == 1){
        this->player1 = player;
    } else if (playerNumber == 2) {
        this->player2 = player;
    }
}

void Game::setPlayerPosition(Player &player, Board &board, int playerNumber){
    
    hOutGame = GetStdHandle( STD_OUTPUT_HANDLE );

    string position;
    cout << "--------------------------------------------------------------" << endl;
    if(playerNumber == 1){
        SetConsoleTextAttribute( hOutGame, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
        cout << player.getPlayerName();
        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    } else if (playerNumber == 2) {
        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        cout << player.getPlayerName();
        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    }
    cout << " ustawia swoja pozycje." << endl;
    int avayableShipCount = 10;
    int AvayableTable[4] = {0};
        AvayableTable[0] = player.getCountShip1();
        AvayableTable[1] = player.getCountShip2();
        AvayableTable[2] = player.getCountShip3();
        AvayableTable[3] = player.getCountShip4();

    while(avayableShipCount != 0){
        player.printAvailableShips();

        cout << "Ustaw statek: " << endl;
        int shipSize = 0;
        int orientation = 0;
        string shipPosition = "";
        cout << "Rozmiar statku (1 - 4): ";
        cin >> shipSize;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
            cout << "Niepoprawny rozmiar!!!" << endl;
            SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
        } else { 
            if((shipSize > 4) || (shipSize < 1)){
                SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                cout << "Niepoprawny rozmiar!!!" << endl;
                SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
            } else if ( AvayableTable[shipSize - 1] == 0) {
                SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                cout << "Ten rozmiar jest juz niedostepny!!!" << endl;
                SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
            } else {
                cout << "Wybierz orientacje statku( 0 - poziomo, 1 - pionowo): ";
                cin >> orientation;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                    cout << "Bledna orientacja!!!" << endl;
                    SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                } else {
                    if(orientation != 0 && orientation != 1){
                        SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                        cout << "Bledna orientacja" << endl;
                        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                    } else {
                        cout << "Podaj startowa wspolrzedna statku (np a4): ";
                        cin >> shipPosition;
                        if(checkPosition(shipPosition) == false){
                            SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                            cout << "Bledna pozycja!!!" << endl;
                            SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                        } else {
                            if(orientation == 0){
                                if((getAlfPart(shipPosition) + shipSize - 1) > 10 ){
                                    SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                                    cout << "Statek sie nie zmiesci w tej pozycji!!!" << endl;
                                    SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                                } else {
                                    int colisionCheck = board.setShipAt(getNumPart(shipPosition) - 1, getAlfPart(shipPosition) - 1, shipSize, orientation);
                                    if( colisionCheck == 1){
                                        SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                                        cout << "Kolizja z innym stakiem lub statek za blisko drugiego!!!" << endl;
                                        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                                    } else {
                                        avayableShipCount--;
                                        AvayableTable[shipSize - 1]--;
                                        if(shipSize == 1){
                                            player.setCountShip1(AvayableTable[0]);
                                        } else if(shipSize == 2) {
                                            player.setCountShip2(AvayableTable[1]);
                                        } else if(shipSize == 3) {
                                            player.setCountShip3(AvayableTable[2]);
                                        } else if(shipSize == 4) {
                                            player.setCountShip4(AvayableTable[3]);
                                        }
                                    }
                                }
                            } else {
                                if((getNumPart(shipPosition) + shipSize - 1) > 10 ){
                                    SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                                    cout << "Statek się nie zmiesci w tej pozycji!!!" << endl;
                                    SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                                } else {
                                    int colisionCheck = board.setShipAt(getNumPart(shipPosition) - 1, getAlfPart(shipPosition) - 1, shipSize, orientation);
                                    if( colisionCheck == 1){
                                        SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
                                        cout << "Kolizja z innym stakiem lub statek za blisko drugiego!!!" << endl;
                                        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                                    } else {
                                        avayableShipCount--;
                                        AvayableTable[shipSize - 1]--;
                                        if(shipSize == 1){
                                            player.setCountShip1(AvayableTable[0]);
                                        } else if(shipSize == 2) {
                                            player.setCountShip2(AvayableTable[1]);
                                        } else if(shipSize == 3) {
                                            player.setCountShip3(AvayableTable[2]);
                                        } else if(shipSize == 4) {
                                            player.setCountShip4(AvayableTable[3]);
                                        }
                                    }
                                }
                            }
                        }               
                    }
                }                
            }
        }
        
        cout << endl;
        board.PrintBoardInSetings();
        cout << endl;
    }
    system("cls");
}

void Game::startBatle() {

    hOutGame = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hOutGame, FOREGROUND_RED | FOREGROUND_INTENSITY );
    cout << "BITWA!!!" << endl;
    SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );

    int currentMoveOld = 1;
    int result;
    int player1hit = 0;
    int player2hit = 0;
    while(player1hit < 20 && player2hit < 20){
        
        while(currentMoveOld != currentMove && player1hit < 20 && player2hit < 20){
            if (currentMove == 0 ){ // ruch player 1
                cout << "Strzela ";
                SetConsoleTextAttribute( hOutGame, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
                cout<< player1.getPlayerName() << endl;
                SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << endl;
                player2Board.PrintBoardInGame(); 
                result = makeMove(player1, player2Board);
                if(result == 1){
                    player1hit++;
                }
            } else if(currentMove == 1) { // ruch player 2
                cout << "Strzela ";
                SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
                cout << player2.getPlayerName() << endl;
                SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << endl;
                player1Board.PrintBoardInGame();
                result = makeMove(player2, player1Board);
                if(result == 1){
                    player2hit++;
                }
            }

            if(result == 0){
                currentMoveOld = currentMove;
            }
        }

        if (currentMove == 0 ){ 
            currentMove = 1;
        } else if(currentMove == 1) {
            currentMove = 0;
        }
    }
    cout << "---------------------------------------------------------------------------" << endl; 
    if(player1hit > player2hit){
        cout << "Wygral ";
        SetConsoleTextAttribute( hOutGame, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
        cout << player1.getPlayerName();
        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
        cout << "!!!" << endl;

        player1Board.PrintBoardInSetings();

    } else if (player1hit < player2hit) {
        cout << "Wygral ";
        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        cout << player2.getPlayerName();
        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
        cout << "!!!" << endl;
        
        player2Board.PrintBoardInSetings();
    }

}

int Game::makeMove(Player &player, Board &board) {
    hOutGame = GetStdHandle( STD_OUTPUT_HANDLE );
    
    string position;
    cout << "Podaj pole do ostrzelania: " << endl;
    cin >> position;

    if(checkPosition(position) == false){
        SetConsoleTextAttribute( hOutGame, FOREGROUND_RED);
        cout << "Bledna pozycja!!!" << endl;
        SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
        return 3;
    }
    
    int result = 0;
    int tmpresult = board.shotAt(getNumPart(position) - 1, getAlfPart(position) - 1);
    if(tmpresult == 1 || tmpresult == 2){
        result = 1;
    }

    if(tmpresult == 2){
        board.fillMiss(getNumPart(position) - 1, getAlfPart(position) - 1);
    }

    if(tmpresult == -1){
        result = 2;
    }
    return result;
}

void Game::runGame() {
    
    setPlayerPosition(player1, player1Board, 1);
    setPlayerPosition(player2, player2Board, 2);

    startBatle();
}

void Game::runTest(){

    hOutGame = GetStdHandle( STD_OUTPUT_HANDLE );

    cout << "Plansza ";
    SetConsoleTextAttribute( hOutGame, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    cout << "Gracza 1: " << endl;
    SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    setTestPosition(player1, player1Board, 1);
    cout << endl;

    cout << "Plansza ";
    SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    cout << "Gracza 2: " << endl;
    SetConsoleTextAttribute( hOutGame, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    setTestPosition(player2, player2Board, 2);
    cout << endl;

    startBatle();
}

void Game::setTestPosition(Player &player, Board &board, int number){
    switch(number){
        case 1: {
            board.setShipAt(2, 0, 1, 0); // 1
            board.setShipAt(0, 8, 1, 0); // 1
            board.setShipAt(2, 5, 1, 0); // 1
            board.setShipAt(5, 5, 1, 0); // 1
            board.setShipAt(4, 2, 2, 0); // 2
            board.setShipAt(6, 2, 2, 1); // 2
            board.setShipAt(5, 8, 2, 1); // 2 
            board.setShipAt(0, 0, 3, 0); // 3
            board.setShipAt(3, 7, 3, 0); // 3
            board.setShipAt(8, 6, 4, 0); // 4

            board.PrintBoardInSetings();

            break;
        }
        case 2: {
            board.setShipAt(1, 0, 1, 0); // 1
            board.setShipAt(1, 2, 1, 0); // 1
            board.setShipAt(2, 9, 1, 0); // 1
            board.setShipAt(8, 4, 1, 0); // 1
            board.setShipAt(6, 1, 2, 1); // 2
            board.setShipAt(2, 7, 2, 1); // 2
            board.setShipAt(7, 9, 2, 1); // 2 
            board.setShipAt(0, 6, 3, 0); // 3
            board.setShipAt(3, 2, 3, 0); // 3
            board.setShipAt(5, 5, 4, 0); // 4

            board.PrintBoardInSetings();

            break;
        }
        default: {

            break;
        }

    }
    
}
