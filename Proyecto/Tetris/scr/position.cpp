//
//  position.cpp
//  Tetris
//

#include "position.hpp"

Position::Position()
{
    this -> row = 0;
    this -> column = 0;
}

Position::Position(int row, int column)
{
    this -> row = row;
    this -> column = column;
}

Position Position::operator+(const Position &other) const
{
    return Position(row + other.row, column + other.column);
}
