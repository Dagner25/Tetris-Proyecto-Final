//
//  colors.hpp
//  Tetris
//

#ifndef colors_hpp
#define colors_hpp

#include <stdio.h>
#pragma once
#include "raylib.h"
#include <vector>

extern const Color black;
extern const Color brightgreen;
extern const Color red;
extern const Color pink;
extern const Color yellow;
extern const Color purple;
extern const Color turquoise;
extern const Color blue;
extern const Color orange;
extern const Color black;
extern const Color darkgreen;
extern const Color beige;

std::vector<Color> GetCellColors();

#endif /* colors_hpp */
