//
// Created by Administrator on 24-4-25.
//

#include "colors.h"


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