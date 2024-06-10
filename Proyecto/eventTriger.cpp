//
//  eventTriger.cpp
//  Tetris
//

#include <stdio.h>
#include "eventTriger.hpp"
#include "raylib.h"

double lastUpdatedTime = 0;
double lastLevelUpTime = 0;

bool EventTriggered(double interval, double additionalTime)
{
    double currentTime = GetTime(); // Suponiendo que GetTime() está definida en algún lugar
    if (currentTime - lastUpdatedTime >= interval + additionalTime)
    {
        lastUpdatedTime = currentTime;
        return true;
    }
    return false;
}

bool LevelUpTriggered(double interval)
{
    double currentTime = GetTime(); // Suponiendo que GetTime() está definida en algún lugar
    if (currentTime - lastLevelUpTime >= interval)
    {
        lastLevelUpTime = currentTime;
        return true;
    }
    return false;
}
