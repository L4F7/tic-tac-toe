#ifndef MOVE_H
#define MOVE_H

class Move {
public:
    Move();
    Move(int row, int col);
    ~Move();
    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);

private:
    int row;
    int col;
};

#endif // MOVE_H
