//
//  position.hpp
//  Tetris
//

#ifndef position_hpp
#define position_hpp

#include <stdio.h>

class Position
{
    public:
        Position();
        Position(int row, int column);
        int row; // x
        int column; // y
        Position operator+(const Position &other) const;
};

#endif
