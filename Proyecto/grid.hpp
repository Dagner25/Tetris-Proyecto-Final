//
//  grid.hpp
//  Tetris
//

#ifndef grid_hpp
#define grid_hpp

#pragma once
#include <vector>
#include "raylib.h"

using namespace std;

class Grid
{
public:
    Grid(int numRows = 20, int numCols = 10);
    ~Grid();
    int **grid;
    void Reset();
    void Draw();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int GetNumRows();
    int GetNumCols();

private:
    int numRows;
    int numCols;
    int cellSize;
    vector<Color> colors;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
};

#endif /* grid_hpp */
