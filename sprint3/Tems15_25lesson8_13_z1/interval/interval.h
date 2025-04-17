#pragma once

#include <iostream>
#include <cmath>

class Interval {
public:
    Interval(int start, int end):
        start_(start),
        end_(end)
    {};

    int GetStart() const {
        return start_;
    }
    int GetEnd() const {
        return end_;
    }
private:
    int start_, end_;
};

// Напишите здесь перегрузки.

inline bool operator<(const Interval& itr1, const Interval& itr2 ) {
    int delt1;
    int delt2;
    if (itr1.GetStart() < itr1.GetEnd())
        delt1  = std::abs(itr1.GetEnd()) - itr1.GetStart();
    else
        delt1  = std::abs(itr1.GetStart()) - itr1.GetEnd();

    if (itr2.GetStart() < itr2.GetEnd())
        delt2  = std::abs (itr2.GetEnd()) - itr2.GetStart();
    else
        delt2  = std::abs (itr2.GetStart()) - itr2.GetEnd();

    //std::cout<< delt1 << " " << delt2 << std::endl;
    return delt1 < delt2;
}

inline bool operator>=(const Interval& int1, const Interval& int2){
    return !(int1 < int2);
}

inline bool operator<=(const Interval& int1, const Interval& int2){
    return !(int2 < int1);
}


inline bool operator==(const Interval& int1, const Interval& int2){
    return !(int1 < int2) && !(int2 < int1);
}

inline bool operator!=(const Interval& int1, const Interval& int2){
    return (int1 < int2) || (int2 < int1);
}


inline bool operator>(const Interval& itr1, const Interval& itr2 ) {
    return itr2 < itr1;
}



