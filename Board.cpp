#include "Board.h"

HANDLE hOutBoard;

Board::Board() {}

void Board::changeState(int num, int alf, FieldState newState){
    board[num][alf].setState(newState);
}

void Board::PrintBoardInGame(){

    HANDLE hOutBoard;
    hOutBoard = GetStdHandle( STD_OUTPUT_HANDLE );

    cout << endl;
    cout << "     a   b   c   d   e   f   g   h   i   j   " << endl;
    cout << "   ----------------------------------------- " << endl;
    for(int i = 0; i < 10; i++){
        if(i == 9){
            cout << i + 1 <<  " | ";
        } else {
            cout << i + 1 <<  "  | ";
        }
        for(int j = 0; j < 10; j++){
            if(board[i][j].getState() == EMPTY){
                cout << "  | ";
            } else if(board[i][j].getState() == SHIP) {
                cout << "  | ";
            } else if(board[i][j].getState() == HIT) {
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "X ";
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << "| ";
            } else if(board[i][j].getState() == MISS) {
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
                cout << "O ";
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << "| ";
            }
        }
        cout << endl;
        cout << "   ----------------------------------------- " << endl;
    }
    cout << endl;
}

void Board::PrintBoardInSetings(){

    hOutBoard = GetStdHandle( STD_OUTPUT_HANDLE );

    cout << endl;
    cout << "     a   b   c   d   e   f   g   h   i   j   " << endl;
    cout << "   ----------------------------------------- " << endl;
    for(int i = 0; i < 10; i++){
        if(i == 9){
            cout << i + 1 <<  " | ";
        } else {
            cout << i + 1 <<  "  | ";
        }
        for(int j = 0; j < 10; j++){
            if(board[i][j].getState() == EMPTY){
                cout << "  | ";
            } else if(board[i][j].getState() == SHIP) {
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
                cout << "S ";
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << "| ";
            } else if(board[i][j].getState() == HIT) {
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "X ";
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << "| ";
            } else if(board[i][j].getState() == MISS) {
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
                cout << "O ";
                SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << "| ";
            }
        }
        cout << endl;
        cout << "   ----------------------------------------- " << endl;
    }
    cout << endl;
}

int Board::setShipAt(int x, int y, int shipSize, int orientation){
    int copyX = x;
    int copyY = y;
    //Tworzenie tabeli pól gdzie będzie statek
    int ship[2][4];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            ship[i][j] = -1;
        }
    }
    int col = 0;
    int i = 0;
    if(orientation == 0) { // statek poziomo
        while(i < shipSize){
            ship[0][col] = x;
            ship[1][col] = y;
            y++;
            i++;
            col++; 
        }
    } else if ( orientation == 1) { // statek pionowo
        while(i < shipSize){
            ship[0][col] = x;
            ship[1][col] = y;
            x++;
            i++;
            col++;
        }
    }

    // Sprawdzanie kolizji po obrysie
    col = 0;
    int newX;
    int newY;
    int stop = 0;
    while(stop == 0 && col <= 3 ){
        newX = ship[0][col];
        newY = ship[1][col];
        if(newX == -1){
            stop = 1;
        } else {
            for(int k = newX - 1; k <= newX + 1; k++){
                for(int t = newY - 1; t <= newY + 1; t++){
                    if(board[k][t].getState() == SHIP && k >= 0 && k <= 9 && t >= 0 && t <=9){
                        return 1;
                    }
                }
            }
            col++;
        }
    }

    // Ustawianie statku
    i = 0;
    x = copyX;
    y = copyY;

    if(orientation == 0) { // statek poziomo
        while(i < shipSize){
            changeState(x, y, SHIP);
            y++;
            i++;
        }
    } else if ( orientation == 1) { // statek pionowo
        while(i < shipSize){
            changeState(x, y, SHIP);
            x++;
            i++;
        }
    }
    return 0;
}

void Board::removeShipAt(int x, int y, int shipSize, int orientation){
    int i = 0;
    if(orientation == 0) { // statek poziomo
        while(i < shipSize){
            changeState(x, y, EMPTY);
            y++;
            i++; 
        }
    } else if ( orientation == 1) { // statek pionowo
        while(i < shipSize){
            changeState(x, y, EMPTY);
            x++;
            i++; 
        }
    }
}

int Board::shotAt(int x, int y){

    hOutBoard = GetStdHandle( STD_OUTPUT_HANDLE );

    if(board[x][y].getState() == HIT || board[x][y].getState() == MISS){
        SetConsoleTextAttribute( hOutBoard, FOREGROUND_RED);
        cout << "Pole juz ostrzelane" << endl;
        SetConsoleTextAttribute( hOutBoard, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
        return -1;
    }

    if(board[x][y].getState() == SHIP){
        changeState(x, y, HIT);
        // sprawdzanie czy zatopiony
        int newX;
        int newY;
        if(x != 0){ //sprawdź w górę jeśli może
            newX = x;
            newY = y;
            while((board[newX][newY].getState() != MISS && board[newX][newY].getState() != EMPTY) && newX >= 0){
                if(board[newX][newY].getState() == SHIP){
                    cout << "Trafiony" << endl;
                    return 1;
                }
                newX--;
            }
        }

        if(x != 9){ //sprawdź w dół jeśli może
            newX = x;
            newY = y;
            while((board[newX][newY].getState() != MISS && board[newX][newY].getState() != EMPTY) && newX <= 9){
                if(board[newX][newY].getState() == SHIP){
                    cout << "Trafiony" << endl;
                    return 1;
                }
                newX++;
            }
        }

        if(y != 0){ //sprawdź w lewo jeśli może
            newX = x;
            newY = y;
            while((board[newX][newY].getState() != MISS && board[newX][newY].getState() != EMPTY) && newY >= 0){
                if(board[newX][newY].getState() == SHIP){
                    cout << "Trafiony" << endl;
                    return 1;
                }
                newY--;
            }
        }

        if(y != 9){ //sprawdź w prawo jeśli może
            newX = x;
            newY = y;
            while((board[newX][newY].getState() != MISS && board[newX][newY].getState() != EMPTY) && newY <= 9){
                if(board[newX][newY].getState() == SHIP){
                    cout << "Trafiony" << endl;
                    return 1;
                }
                newY++;
            }
        }
        cout << "Trafiony zatopiony!" << endl;
        return 2;

    }
    changeState(x, y, MISS);
    cout << "Pudlo :(" << endl;
    return 0;
}

void Board::fillMiss(int x, int y){
    int ship[2][4];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            ship[i][j] = -1;
        }
    }
    int col = 0;
    ship[0][col] = x;
    ship[1][col] = y;
    col++;

    int newX;
    int newY;

    // Lolalizowanie i zapisywanie kordynatów każdego pola statku do tablicy ship
    if(x != 0){ //sprawdź w górę jeśli może
        newX = x - 1;
        newY = y;
        while(board[newX][newY].getState() == HIT && newX >= 0){
            ship[0][col] = newX;
            ship[1][col] = newY;
            col++;

            newX--;
        }
    }

    if(x != 9){ //sprawdź w dół jeśli może
        newX = x + 1;
        newY = y;
        while(board[newX][newY].getState() == HIT  && newX <= 0){
            ship[0][col] = newX;
            ship[1][col] = newY;
            col++;
            
            newX++;
        }        
    }

    if(y != 0){ //sprawdź w lewo jeśli może
        newX = x;
        newY = y - 1;
        while(board[newX][newY].getState() == HIT && newY >= 0){
            ship[0][col] = newX;
            ship[1][col] = newY;
            col++;

            newY--;
        }        
    }

    if(y != 9){ //sprawdź w prawo jeśli może
        newX = x;
        newY = y + 1;
        while(board[newX][newY].getState() == HIT && newY <= 9){
            ship[0][col] = newX;
            ship[1][col] = newY;
            col++;

            newY++;
        }        
    }

    // Zaznaczenie obrysu
    col = 0;
    int stop = 0;
    while(stop == 0 && col <= 3 ){
        newX = ship[0][col];
        newY = ship[1][col];
        if(newX == -1){
            stop = 1;
        } else {
            for(int k = newX - 1; k <= newX + 1; k++){
                for(int t = newY - 1; t <= newY + 1; t++){
                    if(board[k][t].getState() != HIT && k >= 0 && k <= 9 && t >= 0 && t <=9){
                        board[k][t].setState(MISS);
                    }
                }
            }
            col++;
        }
    }
}