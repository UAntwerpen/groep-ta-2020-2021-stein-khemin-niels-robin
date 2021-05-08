
#ifndef TA_UTILS_H
#define TA_UTILS_H

#include <string>
#include <cmath>
#include "Lib.h"

inline std::string toBase5(long int num){
    std::string alphabet = "01234";
    std::string converted;
    do {
        converted += alphabet[num % 5];
        num = std::round(num / 5.0);
    } while (num != 0);
    return converted;
}

inline EStates intToEState(int x){
    return static_cast<EStates>(x);
}
#endif //TA_UTILS_H
