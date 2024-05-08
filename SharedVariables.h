//
// Created by Administrator on 2024/5/8.
//

#ifndef P20_CODE_SHAREDVARIABLES_H
#define P20_CODE_SHAREDVARIABLES_H

#include "SharedBoolVar.h"

class SharedVariables {
public:
    SharedBoolVar data;
    SharedBoolVar sending;
    SharedBoolVar hasRead;
    SharedBoolVar transfering;

private:
};


#endif //P20_CODE_SHAREDVARIABLES_H
