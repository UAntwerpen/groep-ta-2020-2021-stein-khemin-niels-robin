
#ifndef TA_UTILS_H
#define TA_UTILS_H

#include <string>
#include <cmath>

inline std::string toBase5(long int num){
    std::string alphabet = "01234";
    std::string converted;
    do {
        converted += alphabet[num % 5];
        num = std::round(num / 5.0);
    } while (num != 0);
    return converted;
}

#endif //TA_UTILS_H
