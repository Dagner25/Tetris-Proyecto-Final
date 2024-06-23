//
//  colors.cpp
//  Tetris
//

#include "colors.hpp"

const Color darkgrey = {46, 43, 43, 255};
const Color brightgreen = {164, 159, 88, 255};
const Color red = {141, 39, 51, 255};
const Color pink = {125, 26, 76, 255};
const Color yellow = {221, 170, 85, 255};
const Color purple = {92, 41, 118, 255};
const Color turquoise = {52, 118, 118, 255};
const Color blue = {69, 88, 155, 255};
const Color orange = {198, 106, 82, 255};
const Color black = {0, 0, 0, 255};
const Color darkgreen = {47, 132, 91, 255};
const Color beige = {241, 234, 223, 255};

std::vector<Color> GetCellColors()
{
    return {darkgrey, brightgreen, red, pink, yellow, purple, blue, black, darkgreen};
}
