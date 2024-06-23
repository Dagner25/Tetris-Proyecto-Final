//
//  game.cpp
//  Tetris
//

#include "game.hpp"
#include "eventTriger.hpp"
#include <iostream>
#include "constants.hpp"

using namespace std;

Game::Game()
{
    grid = new Grid(27, 14);
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    additionalMoveInterval = currentBlock->GetGravity();
    nextBlock = GetRandomBlock();
    moveInterval = 0.2;
    levelUpInterval = 10.0;
    resizeLevelInterval = 5;
    gameOver = false;
    score = 0;
    level = 1;
    InitAudioDevice();
    music = LoadMusicStream("/Users/fiorellaflores/Desktop/Coding File/C++ Projects/CCOMP I | Proyecto Final/Tetris/Tetris/scr/Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("/Users/fiorellaflores/Desktop/Coding File/C++ Projects/CCOMP I | Proyecto Final/Tetris/Tetris/scr/Sounds/rotate.mp3");
    clearSound = LoadSound("/Users/fiorellaflores/Desktop/Coding File/C++ Projects/CCOMP I | Proyecto Final/Tetris/Tetris/scr/Sounds/clear.mp3");
}

Game::~Game()
{
    delete currentBlock;
    delete nextBlock;
    ClearAllBlocks(blocks);
    delete grid;
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

//void Game::SetMoveInterval(double newInterval)
//{
//    moveInterval = newInterval;
//}

double Game::GetMoveInterval()
{
    return moveInterval;
}

double Game::GetAdditionalMoveInterval()
{
    return additionalMoveInterval;
}

void Game::Draw()
{
    grid->Draw();
    currentBlock->Draw(GameConstants::PADDING, GameConstants::PADDING);
    switch (nextBlock->id)
    {
        case 3:
            nextBlock->Draw(375, 340);
            break;
        case 4:
            nextBlock->Draw(375, 320);
            break;
        default:
            nextBlock->Draw(390, 320);
            break;
    }
}

void Game::HandleInput()
{
    int keyPresed = GetKeyPressed();
    int keyIsDown = IsKeyDown(KEY_DOWN);
    
    if (gameOver && keyPresed != 0)
    {
        gameOver = false;
        Reset();
    }
    
    if (keyIsDown)
    {
        if (EventTriggered(0.05))
        {
            MoveBlockDown(-1);
            UpdateScore(0, 1);
        }
    }
    
    switch (keyPresed)
    {
        case KEY_LEFT:
            MoveBlockLeft(keyPresed);
            break;
        case KEY_RIGHT:
            MoveBlockRight(keyPresed);
            break;
        case KEY_DOWN:
            MoveBlockDown(keyPresed);
            break;
        case KEY_UP:
            RotateBlock(keyPresed);
        default:
            break;
    }
}

void Game::HandleLevel()
{
    if (LevelUpTriggered(levelUpInterval))
    {
        //SetMoveInterval(moveInterval - 0.02);
        moveInterval = moveInterval - 0.02;
        if (!gameOver)
        {
            level++;
            if( level % resizeLevelInterval == 0 ){
                grid->Resize(grid->GetNumRows() -1 , grid->GetNumCols() -1);
            }
        }
    }
}

void Game::MoveBlockLeft(int keyPresed)
{
    if (!gameOver)
    {
        currentBlock->Move(0, -1);
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock->Move(0, 1);
        } else {
            currentBlock->CustomBehaviour(keyPresed);
            if (isBlockOutside() || !BlockFits())
            {
                currentBlock->UndoCustomBehaviour(keyPresed);
            }
        }
    }
}

void Game::MoveBlockRight(int keyPresed)
{
    if (!gameOver)
    {
        currentBlock->Move(0, 1);
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock->Move(0, -1);
        }else{
            currentBlock->CustomBehaviour(keyPresed);
            if (isBlockOutside() || !BlockFits())
            {
                currentBlock->UndoCustomBehaviour(keyPresed);
            }
        }
    }
}

void Game::MoveBlockDown(int keyPresed)
{
    if (!gameOver)
    {
        currentBlock->Move(1, 0);
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock->Move(-1, 0);
            LockBlock();
        }
        if (keyPresed == 0)
        {
            currentBlock->CustomBehaviour(keyPresed);
            if (isBlockOutside() || !BlockFits())
            {
                currentBlock->UndoCustomBehaviour(keyPresed);
                LockBlock();
            }
        }
    }
}

void Game::RotateBlock(int keyPresed)
{
    if (!gameOver)
    {
        currentBlock->Rotate();
        if (isBlockOutside() || !BlockFits())
        {
            currentBlock->UndoRotate();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock->GetCellPositions();
    for (const Position& item : tiles)
    {
        // Verificar si las posiciones están dentro de los límites de la grid
        if (item.row >= 0 && item.row < grid->GetNumRows() && item.column >= 0 && item.column < grid->GetNumCols()) {
            grid->grid[item.row][item.column] = currentBlock->id;
        } else {
            // Manejar el caso de posiciones fuera de los límites
            // TODO: tal vez agregar un sonido de explocion
            std::cerr << "Error: Position (" << item.row << ", " << item.column << ") is out of bounds!" << std::endl;
            gameOver = true;
            return;
        }
    }
    currentBlock = nextBlock;
    currentBlock->CustomBehaviour(-1);
    additionalMoveInterval = currentBlock->GetGravity();
    // si el bloque actual colisiona con otro
    if (!BlockFits())
    {
        gameOver = true;
    }
    // se asigna el siguiente bloque, porque el actual ya esta bloqueado
    nextBlock = GetRandomBlock();
    // como ya se ha bloqueado , verificamos si hay alguna fila completa
    int rowsCleared = grid->ClearFullRows();
    // si hay mas de 1 fila completa actualizamos el score
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared,0);
    }
}

bool Game::BlockFits()
{
    // comprobamos que la posicion de las celdas del bloque actual no choquen con alguna ocupada en esa posicion de  grid
    vector<Position> tiles = currentBlock->GetCellPositions();
    for (Position item : tiles)
    {
        if (!grid->IsCellEmpty(item.row, item.column))
        {
            return false;
        }
    }
    return true;
}

void Game::ClearAllBlocks(vector<Block*>& allBlocks)
{
    for (Block* block : allBlocks) {
        delete block;
    }
    allBlocks.clear(); // Limpia el contenedor después de liberar la memoria
}

void Game::Reset()
{
    grid->Reset(); // setear los valores en 0
    grid->Resize(27,14);
    ClearAllBlocks(blocks);
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    additionalMoveInterval = 0.0;
    score = 0;
    moveInterval = 0.2;
    //SetMoveInterval(0.2);
    level = 1;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 700;
            break;
        default:
            break;
    }
    
    score += moveDownPoints;
}

vector<Block *> Game::GetAllBlocks()
{
    return {new LBlock(), new OBlock(), new SBlock(), new IBlock(), new ZBlock(), new JBlock(), new TBlock() };
}


Block *Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block *block = blocks[randomIndex]; // Obtener un puntero crudo al bloque
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

bool Game::isBlockOutside()
{
    vector<Position> tiles = currentBlock->GetCellPositions();
    for (Position item : tiles)
    {
        if (grid->IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}
