//
//  block.cpp
//  Tetris
//

#include "block.hpp"

using namespace std;

Block::Block()
{
    blockPosition = Position();
    cellSize = 30;
    rotationState = 0;
    gravity = 9.8;
    colors = GetCellColors();
}

void Block::Draw(int offsetX, int offsetY)
{
    vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + 1 + offsetX, item.row * cellSize + 1 + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
};

// void Block::Move(int rows, int columns){
//     rowOffset += rows;
//     columnOffset += columns;
// }
void Block::Move(int rows, int columns)
{
    blockPosition = blockPosition + Position(rows, columns);
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotate()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = (int)cells.size() - 1;
    };
}

vector<Position> Block::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + blockPosition.row, item.column + blockPosition.column);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::SetGravity(double g)
{
    // Gravedad estándar
    const double standardGravity = 9.8;
    // Gravedad normalizada
    const double normalizedGravity = 0.02;

    // Si la gravedad es igual a la gravedad estándar, establece la gravedad del bloque a 0.0
    if (g == standardGravity)
    {
        gravity = 0.0;
    }
    else if (g > standardGravity)
    {
        // Calcula la gravedad aumentada
        double increasedGravity = (g - standardGravity) * normalizedGravity;
        gravity = normalizedGravity + increasedGravity;
    }
    else // g < standardGravity
    {
        // Calcula la gravedad reducida
        double reducedGravity = (standardGravity - g) * normalizedGravity;
        gravity = -normalizedGravity - reducedGravity;
    }
}

double Block::GetGravity()
{
    return gravity;
}
