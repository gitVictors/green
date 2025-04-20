#pragma once
#include <cstdint>
#include <compare>

class Rational {
public:
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {}

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};

// Напишите здесь перегрузки операций.

inline bool operator==(const Rational& rt1, const Rational& rt2 )
{
    std::int64_t c1 = static_cast<std::int64_t>  (rt1.GetNumerator()) *  static_cast<std::int64_t> (rt2.GetDenominator());
    std::int64_t c2 = static_cast<std::int64_t>  (rt1.GetDenominator()) * static_cast<std::int64_t> (rt2.GetNumerator());
    return (c1 == c2);
}

inline auto operator<=>(const Rational& rt1, const Rational& rt2 ){

    std::int64_t ln1 = static_cast<std::int64_t>  (rt1.GetNumerator()) *  static_cast<std::int64_t> (rt2.GetDenominator());
    std::int64_t ln2 = static_cast<std::int64_t>  (rt1.GetDenominator()) * static_cast<std::int64_t> (rt2.GetNumerator());
    return (ln1 <=> ln2);
}
