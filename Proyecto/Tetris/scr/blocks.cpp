//
//  blocks.cpp
//  Tetris
//

#include "block.hpp"
#include "position.hpp"
#include <iostream>

class LBlock : public Block
{
    public:
        LBlock()
        {
            id = 1;
            cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)};
            cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)};
            cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
            Move(0, 3);
            SetGravity(8);
        }
    
        void CustomBehaviour (int keyPresed) const override
        {
            switch (keyPresed)
            {
                case KEY_LEFT:
                    const_cast <LBlock *> (this) -> Move(0, 2);
                    break;
                case KEY_RIGHT:
                    const_cast <LBlock *> (this) -> Move(0, -2);
                    break;
                default:
                    break;
            }
        };
    
        void UndoCustomBehaviour (int keyPresed) const override
        {
            switch (keyPresed)
            {
                case KEY_LEFT:
                    const_cast <LBlock *> (this) -> Move(0, -2);
                    break;
                case KEY_RIGHT:
                    const_cast <LBlock *> (this) -> Move(0, 2);
                    break;
                default:
                    break;
            }
        };
};


class JBlock : public Block
{
    public:
        JBlock()
        {
            id = 2;
            cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
            cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
            cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)};
            Move(0, 3);
            SetGravity(8);
        }
    
        void CustomBehaviour(int keyPresed) const override {};
    
        void UndoCustomBehaviour(int keyPresed) const override {};
};


class IBlock : public Block
{
    public:
        IBlock()
        {
            id = 3;
            cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
            cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
            cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
            cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
            Move(-1, 3);
        }
    
        void CustomBehaviour (int keyPresed) const override
        {
            const_cast <IBlock *> (this) -> SetGravity(10);
            switch (keyPresed)
            {
                case 0:
                    const_cast <IBlock *> (this) -> Move(1, 0);
                    break;
                default:
                    break;
            }
        };
    
        void UndoCustomBehaviour (int keyPresed) const override
        {
            const_cast <IBlock *> (this) -> SetGravity(8);
            switch (keyPresed)
            {
                case 0:
                    const_cast <IBlock *> (this) -> Move(-1, 0);
                    break;
                default:
                    break;
            }
        };
};


class OBlock : public Block
{
    public:
        OBlock()
        {
            id = 4;
            cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
            Move(0, 4);
        }
    
        void CustomBehaviour (int keyPresed) const override {
            const_cast <OBlock *> (this) -> SetGravity(10);
        };
    
        void UndoCustomBehaviour (int keyPresed) const override {
            const_cast <OBlock *> (this) -> SetGravity(8);
        };
};


class SBlock : public Block
{
    public:
        SBlock()
        {
            id = 5;
            cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
            cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
            cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)};
            cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
            Move(0, 3);
        }
    
        void CustomBehaviour (int keyPresed) const override {
            const_cast <SBlock *> (this) -> SetGravity(7);
        };
    
        void UndoCustomBehaviour(int keyPresed) const override {
            const_cast <SBlock *> (this) -> SetGravity(8);
        };
};


class TBlock : public Block
{
    public:
        TBlock()
        {
            id = 6;
            cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
            cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
            cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
            Move(0, 3);
            SetGravity(8);
        }
    
        void CustomBehaviour (int keyPresed) const override
        {
            switch (keyPresed)
            {
                case KEY_LEFT:
                    const_cast <TBlock *> (this) -> Move(0, -1);
                    break;
                default:
                    break;
            }
        };
    
        void UndoCustomBehaviour(int keyPresed) const override
        {
            switch (keyPresed)
            {
                case KEY_LEFT:
                    const_cast <TBlock *> (this) -> Move(0, 1);
                    break;
                default:
                    break;
            }
        };
};


class ZBlock : public Block
{
    public:
        ZBlock()
        {
            id = 8;
            cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
            cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
            cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
            Move(0, 3);
            SetGravity(8);
        }
    
        void CustomBehaviour (int keyPresed) const override
        {
            switch (keyPresed)
            {
                case KEY_RIGHT:
                    const_cast <ZBlock *> (this) -> Move(0, 1);
                    break;
                default:
                    break;
            }
        };
    
        void UndoCustomBehaviour (int keyPresed) const override
        {
            switch (keyPresed)
            {
                case KEY_RIGHT:
                    const_cast <ZBlock *> (this) -> Move(0, -1);
                    break;
                default:
                    break;
            }
        };
};
