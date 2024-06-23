//
//  grid.cpp
//  Tetris 
//

#include "grid.hpp"
#include "colors.hpp"
#include "constants.hpp"

Grid::Grid(int numRows, int numCols){
    this -> numRows = numRows;
    this -> numCols = numCols;
    this -> cellSize = 30;
    colors = GetCellColors();
    
    grid = new int *[numRows];
    
    for (int i = 0; i < numRows; ++i){
        grid[i] = new int[numCols];
        
        for (int j = 0; j < numCols; ++j){
            grid[i][j] = 0;
        }
    }
}

Grid::~Grid() {
    for (int i = 0; i < numRows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Grid::Reset() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            grid[row][column] = 0;
        }
    }
}

void Grid::Draw() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int cellValue = grid[row][col];
            DrawRectangle(col * cellSize + 1 + GameConstants::PADDING, row * cellSize + 1 + GameConstants::PADDING, cellSize - 1, cellSize - 1, colors[cellValue]); 
        }
    }
}

bool Grid::IsCellOutside(int row, int column) {
    if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column) {
    if (grid[row][column] == 0) {
        return true;
    }
    return false;
}

bool Grid::IsRowFull(int row) {
    for (int column = 0; column < numCols; column++) {
        if (grid[row][column] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (int column = 0; column < numCols; column++) {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows) {
    for (int column = 0; column < numCols; column++) {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

int Grid::ClearFullRows() {
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

void Grid::Resize(int newNumRows, int newNumCols) 
{
    int **newGrid = new int*[newNumRows];
    for (int i = 0; i < newNumRows; ++i) {
        newGrid[i] = new int[newNumCols];
    }

    int minRows = std::min(numRows, newNumRows);
    int minCols = std::min(numCols, newNumCols);
    for (int i = 0; i < minRows; ++i) {
        for (int j = 0; j < minCols; ++j) {
            newGrid[i][j] = grid[i][j];
        }
    }

    for (int i = 0; i < newNumRows; ++i) {
        for (int j = 0; j < newNumCols; ++j) {
            if (i >= numRows || j >= numCols) {
                newGrid[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < numRows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;

    grid = newGrid;
    numRows = newNumRows;
    numCols = newNumCols;
}

int Grid::GetNumRows(){
    return numRows;
}

int Grid::GetNumCols(){
    return numCols;
}
