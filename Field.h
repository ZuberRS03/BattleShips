#ifndef FIELD_H
#define FIELD_H

enum FieldState{
    EMPTY,
    SHIP,
    MISS,
    HIT
};

class Field {
private:
    FieldState state; // stan pojedyńczego pola
public:
    //Konstruktor
    Field();

    /*
    * Funkcja zwracająca stan pola
    * @param void
    * @return FieldState state
    */
    FieldState getState() const;

    /*
    * Funkcja ustawiająca stan pola
    * @param FieldState state
    * @return void
    */
    void setState(FieldState newState);

    //Destruktor
    ~Field() {}
};

#endif //FIELD_H