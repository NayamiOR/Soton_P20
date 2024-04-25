//
// Created by Administrator on 24-4-25.
//

#ifndef P20_CODE_COLORS_H
#define P20_CODE_COLORS_H

#include <string>
#include <unordered_map>
#include <map>

enum Color {
    BLACK,
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA
};

extern std::map<Color, std::string> colorNames ;

#endif //P20_CODE_COLORS_H
