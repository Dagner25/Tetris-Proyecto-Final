//
//  block.hpp
//  Tetris
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include "position.hpp"
#include "colors.hpp"

using namespace std;

// clase abstracta
class Block
{
public:
    Block();
    virtual ~Block() = default;
    int id;
    // map<int, vector<Position>> cells;
    map<int, vector<Position>> cells;
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    void Rotate();
    void UndoRotate();
    vector<Position> GetCellPositions(); // metodo
    void SetGravity(double g);
    double GetGravity();
    // Polimorfismo
    virtual void CustomBehaviour(int keyPresed) const = 0; // funcion virtual pura, esta obligada a implementarse en los hijos
    virtual void UndoCustomBehaviour(int keyPresed) const = 0;

private:
    int cellSize; // atributo
    int rotationState;
    double gravity;
    vector<Color> colors;
    // int rowOffset;
    // int columnOffset;
    Position blockPosition;
};

#endif /* block_hpp */
