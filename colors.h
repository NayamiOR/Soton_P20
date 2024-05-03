//
// Created by Administrator on 24-4-25.
//

#ifndef P20_CODE_COLORS_H
#define P20_CODE_COLORS_H

#include <string>
#include <unordered_map>
#include <map>
#include <QColor>

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


struct ColorComparator {
    bool operator()(const QColor& a, const QColor& b) const {
        return a.name() < b.name();
    }
};

extern std::map<QColor,std::string,ColorComparator> colorNames;


#endif //P20_CODE_COLORS_H
