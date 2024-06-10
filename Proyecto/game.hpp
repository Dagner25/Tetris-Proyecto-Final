//
//  game.hpp
//  Tetris
//
//  Created by Exponentia Dev on 25/05/24.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include "grid.hpp"
#include "blocks.cpp"

class Game
{
public:
    Game();
    void Draw();
    void HandleInput();
    void HandleLevel();
    void MoveBlockDown(int keyPresed);
    double GetMoveInterval();
    double GetAdditionalMoveInterval();
    bool gameOver;
    int score;
    int level;
    Music music;
    ~Game();

private:
    Grid *grid;
    vector<Block *> blocks;
    bool isBlockOutside();
    void MoveBlockLeft(int keyPresed);
    void MoveBlockRight(int keyPresed);
    void RotateBlock(int keyPresed);
    void LockBlock();
    bool BlockFits();
    void ClearAllBlocks(vector<Block*>& allBlocks);
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    //void SetMoveInterval(double newInterval);
    
    //tiempo
    double moveInterval;
    double additionalMoveInterval;
    double levelUpInterval;
    //nivel
    int resizeLevelInterval;
    
    Block *currentBlock;
    Block *nextBlock;
    Block *GetRandomBlock();
    vector<Block *> GetAllBlocks();
    Sound rotateSound;
    Sound clearSound;
};

#endif /* game_hpp */
