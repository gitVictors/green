#pragma once

#include <iostream>
#include <string>
#include <algorithm>


class Rational {
public:
    Rational() = default;
    Rational(int numerator, int denominator)
        : numerator_{numerator}, denominator_{denominator} {}

    friend inline std::istream& operator>>(std::istream& is, Rational& rt);
    friend inline  std::ostream& operator<<(std::ostream& os, const Rational& rt);

private:
    int numerator_ = 0;
    int denominator_ = 1;
};

// Напишите здесь реализацию ввода-вывода.

inline std::istream& operator>>(std::istream& is, Rational& rt) {
    //int num;
    std::string div; // { '/' };
    //int denom;
    std::string line;

    std::getline(is, line);

    line.erase( std::remove (line.begin(), line.end(), ' '), line.end());

    size_t slash_pos = line.find('/');
    if (slash_pos == std::string::npos){
        rt.numerator_ = std::stoi(line);
        rt.denominator_ = 1;
    }else {
        rt.numerator_= std::stoi (line.substr(0, slash_pos) );

        if (line.size() > slash_pos+1)
            rt.denominator_ = std::stoi (line.substr( slash_pos + 1 ));
        else{
            is.unget();
            is.setstate(std::ios_base::failbit );
        }

        if (rt.denominator_ == 0){
            rt.denominator_ = 1;
            is.setstate(std::ios_base::failbit );
        }
    }

    return is;

}

inline std::ostream& operator<<(std::ostream& ot, const Rational& rt) {

    if  ( rt.denominator_ == 0  || rt.denominator_ == 1 )
    {
        ot << rt.numerator_; //<< " " << "/";
    }
    else
    {
        ot << rt.numerator_ << " " << "/" << " " << rt.denominator_;
    }

    return ot;
}

