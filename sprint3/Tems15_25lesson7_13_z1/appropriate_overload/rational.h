class Rational {
public:
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {}

    Rational(int value) :numerator_(value)
    {}

    // Перегрузка операции сравнения.
    // Вы научитесь этому в следующем уроке.
    bool operator==(const Rational& r) const {
        return (numerator_ == r.numerator_) &&
               (denominator_ == r.denominator_);
    }

    // Добавьте новый конструктор.
    // И реализуйте перегрузку присваивания.
    Rational& operator=(const int value){
        numerator_ = value;
        return *this;
    }
    Rational& operator=(const Rational& other){
        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        return *this;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};
