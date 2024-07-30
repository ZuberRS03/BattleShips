#include "Field.h"
#include <iostream>

Field::Field() : state(EMPTY) {}

FieldState Field::getState() const {
    return state;
}

void Field::setState(FieldState newState) {
    this->state = newState;
}