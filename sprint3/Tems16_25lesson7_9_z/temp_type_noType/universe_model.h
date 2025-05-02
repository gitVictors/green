#pragma once

#include <iomanip>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>


//constexpr double M_PI =  3.14159265358979323846 ;

template <int W, int R>
class UniverseModel {
public:
    // Напишите реализацию этих методов.
    static double CountTotalVolume(){
        double res = 0;

        if  (W > W_CONST )
        {
            res = 4.0 / 3 * M_PI * pow(R, 3);
        }
        else if  (W == W_CONST )
        {
            res = pow(R, 2);
        }
        else if (W < W_CONST)
        {
            res = 2 * pow(M_PI, 2) * pow(R * 0.5, 2) * R;
        }

        return res;
    }

    double CountStars(double stars_per_unit){

        return total_volume * stars_per_unit;
    }

private:
    inline static const double W_CONST = 8; // Критическая плотность.
    inline static const double total_volume = CountTotalVolume();
};

template <typename T>
void CountStarsStats(T UniverseModel) {
    using namespace std::literals;

    std::cout << "Stars per unit  Total number of stars"s << std::endl;
    for (int i = 1; i < 10; i++) {
        std::cout << std::setw(10) << i;
        std::cout << std::setw(20) << UniverseModel.CountStars(i) << std::endl;
    }
}
