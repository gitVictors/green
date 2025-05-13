#pragma once

#include <numeric>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <compare>

class Rational {
public :
    Rational () =default;
    Rational (int numerator): numerator_(numerator), denominator_(1) {}
    Rational (int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        // Приводим дробь к правильному формату.
        Reduction();
    }
    Rational (const Rational& rtn): numerator_(rtn.numerator_), denominator_(rtn.denominator_) {}



    // Присваивающие арифметические ------------------------------------------------

    Rational& operator*=(const Rational& r)
    {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r)
    {
        if (r.numerator_ == 0)
            std::abort();

        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;

        Reduction();
        return *this;
    }

    Rational& operator+=(const Rational& r)
    {
        numerator_ = (numerator_ * r.denominator_) + (denominator_ * r.numerator_);
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r)
    {
        numerator_ = numerator_ * r.denominator_ - r.numerator_ * denominator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational operator+(const Rational& rt )const{
        Rational result{*this};
        result+=rt;
        return result;
    }

    Rational operator-(const Rational& rt) const{
        Rational result{*this};
        result-=rt;
        return result;
    }

    Rational operator*(const Rational& rt)const{
        Rational result{*this};
        result*=rt;
        return result;
    }

    Rational operator/(const Rational& rt)const {
        Rational result{*this};
        result/=rt;
        return result;
    }

    //------------------------------------------------------------------------

    // Операции присваивания -------------------------------------------------

    // Rational& operator=(Rational&&) = default;

    Rational& operator=(const Rational& other)
    {
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        return *this;
    }


    Rational& operator=(const int value){
        numerator_ = value;
        return *this;
    }

    //------------------------------------------------------------------------


    //------------------------------------------------------------------------
    // Унарные + - операции --------------------------------------------------
    Rational operator-() const {
        return Rational {numerator_ , -denominator_};
    }

    Rational operator+() const {
        return *this;
    }
    //------------------------------------------------------------------------

    // Перегрузка потоков ----------------------------------------------------
    friend std::istream& operator>>(std::istream& inst, Rational& rtn);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rtn);
    //------------------------------------------------------------------------

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {

        return Rational{denominator_, numerator_};
    }

    //-------------------------------------------------------------------------------
private:
    // Метод для приведения дроби к корректной форме.
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;

};


//-- Перегрузка потоков ----------------------------------------------------
inline std::istream& operator>>(std::istream& inst, Rational& rtn) {
    int num, den;
    char div;

    if (!(inst >> num)) {
        return inst;
    }

    if (!(inst >> std::ws >> div)) {
        rtn = Rational(num, 1);
        inst.clear();
        return inst;
    }

    if (div != '/') {
        rtn = Rational(num, 1);
        inst.unget();
        return inst;
    }

    if (!(inst >> den) || (den == 0)) {
        inst.setstate(std::ios::failbit);
        return inst;
    }

    rtn = Rational(num, den);

    return inst;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& rtn) {
    using namespace std::literals;
    if (rtn.denominator_ == 1) {
        os << rtn.numerator_;
    } else {
        os << rtn.numerator_ << " / "s << rtn.denominator_;
    }
    return os;
}

//----------------------------------------------------------------------------

//--Проверки на равенство и трёхстороннего сравнения -------------------------
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
