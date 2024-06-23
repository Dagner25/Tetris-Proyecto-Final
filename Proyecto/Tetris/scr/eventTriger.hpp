//
//  eventTriger.hpp
//  Tetris
//

#ifndef eventTriger_hpp
#define eventTriger_hpp

#include <stdio.h>

bool EventTriggered(double interval, double additionalTime = 0.0);
bool LevelUpTriggered(double interval);

#endif /* eventTriger_hpp */
