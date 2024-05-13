#include "move.h"

Move::Move() {
    this->row = 0;
    this->col = 0;
}

Move::Move(int row, int col) {
    this->row = row;
    this->col = col;
}

Move::~Move() {}

int Move::getRow() const {
    return row;
}


int Move::getCol() const {
    return col;
}

void Move::setRow(int row) {
    this->row = row;
}

void Move::setCol(int col) {
    this->col = col;
}
