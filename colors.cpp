//
// Created by Administrator on 24-4-25.
//

#include "colors.h"

//std::map<Color, std::string> colorNames = {
//        {BLACK,   "Black"},
//        {WHITE,   "White"},
//        {RED,     "Red"},
//        {GREEN,   "Green"},
//        {BLUE,    "Blue"},
//        {YELLOW,  "Yellow"},
//        {CYAN,    "Cyan"},
//        {MAGENTA, "Magenta"}
//};

//struct ColorComparator {
//    bool operator()(const QColor& a, const QColor& b) const {
//        return a.name() < b.name();
//    }
//};

std::map<QColor,std::string,ColorComparator> colorNames = {
        {Qt::black,   "Black"},
        {Qt::white,   "White"},
        {Qt::red,     "Red"},
        {Qt::green,   "Green"},
        {Qt::blue,    "Blue"},
        {Qt::yellow,  "Yellow"},
        {Qt::cyan,    "Cyan"},
        {Qt::magenta, "Magenta"}
};