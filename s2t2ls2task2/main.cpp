#include <cassert>
#include <iostream>
#include <string>

#include "rational.h"

using namespace std::literals;

std::string ToString(Rational r) {
    return std::to_string(r.GetNumerator()) + "/"s + 
           std::to_string(r.GetDenominator());
}

void RunUnitTests() {
    {
        Rational r;
        assert(ToString(r) == "0/1"s);
        assert(r.AsDouble() == 0.0);
    }
    {
        Rational r{1, 2};
        assert(ToString(r) == "1/2"s);
        assert(r.AsDouble() == 0.5);
    }
    {
        Rational r{2, 4};
        assert(ToString(r) == "1/2"s);
        assert(r.AsDouble() == 0.5);
    }
    {
        Rational r{-2, 4};
        assert(ToString(r) == "-1/2"s);
        assert(r.AsDouble() == -0.5);
    }
    {
        Rational r{2, -4};
        assert(ToString(r) == "-1/2"s);
    }
    {
        Rational r{8, -12};
        assert(ToString(r) == "-2/3"s);
    }
    {
        Rational r1{1, 2};
        Rational r2{5, 6};
        assert(ToString(r1.Add(r2)) == "4/3"s);
    }
    {
        Rational r1{1, 2};
        Rational r2{5, 6};
        assert(ToString(r1.Sub(r2)) == "-1/3"s);
    }
    {
        Rational r1{1, 2};
        Rational r2{-5, 6};
        assert(ToString(r1.Add(r2)) == "-1/3"s);
    }
    {
        Rational r1{1, 2};
        Rational r2{-5, 6};
        assert(ToString(r1.Sub(r2)) == "4/3"s);
    }
    {
        Rational r1{1, -2};
        Rational r2{-1, 6};
        assert(ToString(r1.Add(r2)) == "-2/3"s);
    }
    {
        Rational r1{1, -2};
        Rational r2{-1, 6};
        assert(ToString(r1.Sub(r2)) == "-1/3"s);
    }
}

int main() {
    RunUnitTests();

    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    Rational r1{a, b};
    Rational r2{c, d};

    std::cout << "Fraction 1: " + ToString(r1) 
              << " (" << r1.AsDouble() << ')' << std::endl;
    std::cout << "Fraction 2: " + ToString(r2) 
              << " (" << r2.AsDouble() << ')' << std::endl;
    auto sum = r1.Add(r2);
    std::cout << "Sum:        " + ToString(sum) 
              << " (" << sum.AsDouble() << ')' << std::endl;
    auto diff = r1.Sub(r2);
    std::cout << "Difference: " + ToString(diff) 
              << " (" << diff.AsDouble() << ')' << std::endl;
}
