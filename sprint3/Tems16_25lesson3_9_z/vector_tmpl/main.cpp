
#include "vector.h"
#include <cassert>
#include <string>

// Шаблон операции. Вы изучите их в следующем уроке.
template<typename T>
bool operator==(Point<T> l, Point<T> r) {
    return l.x == r.x && l.y == r.y;
}

namespace std {
inline std::string operator*(const std::string& l, const std::string& r) {
    return "(" + l + "*" + r + ")";
}
inline std::string operator-(const std::string& l, const std::string& r) {
    return l + "-" + r;
}
}

int main() {
    {
        Vector2D<int> my_vector{{1, 2}, {4, 6}};

        assert((my_vector.GetStart() == Point<int>{1, 2}));
        assert((my_vector.GetEnd() == Point<int>{4, 6}));
        assert((my_vector.GetLengthSq() == 25));

        my_vector.SetStart({4, 6});

        assert((my_vector.GetStart() == Point<int>{4, 6}));
        assert((my_vector.GetEnd() == Point<int>{4, 6}));
        assert((my_vector.GetLengthSq() == 0));

        my_vector.SetEnd({1, 2});

        assert((my_vector.GetStart() == Point<int>{4, 6}));
        assert((my_vector.GetEnd() == Point<int>{1, 2}));
        assert((my_vector.GetLengthSq() == 25));
    }
    {
        Vector2D<double> my_vector{{0.5, 0.1}, {2.0, 2.5}};

        assert((my_vector.GetStart() == Point<double>{0.5, 0.1}));
        assert((my_vector.GetEnd() == Point<double>{2.0, 2.5}));
        assert((my_vector.GetLengthSq() == 8.01));

        my_vector.SetStart({0.0, 0.0});

        assert((my_vector.GetStart() == Point<double>{0.0, 0.0}));
        assert((my_vector.GetEnd() == Point<double>{2.0, 2.5}));
        assert((my_vector.GetLengthSq() == 10.25));

        my_vector.SetEnd({1.0, 0.5});

        assert((my_vector.GetStart() == Point<double>{0.0, 0.0}));
        assert((my_vector.GetEnd() == Point<double>{1.0, 0.5}));
        assert((my_vector.GetLengthSq() == 1.25));

        my_vector.SetEnd({0.0, 0.0});

        assert((my_vector.GetLengthSq() == 0.0));
    }

    {
        Vector2D<int> my_vector{{-1, -2}, {-4, 6}};

        assert((my_vector.GetStart() == Point<int>{-1, -2}));
        assert((my_vector.GetEnd() == Point<int>{-4, 6}));
        assert((my_vector.GetLengthSq() == 73));

        my_vector.SetStart({-1, 2});

        assert((my_vector.GetStart() == Point<int>{-1, 2}));
        assert((my_vector.GetEnd() == Point<int>{-4, 6}));
        assert((my_vector.GetLengthSq() == 25));

        my_vector.SetEnd({-4, -6});

        assert((my_vector.GetStart() == Point<int>{-1, 2}));
        assert((my_vector.GetEnd() == Point<int>{-4, -6}));
        assert((my_vector.GetLengthSq() == 73));
    }
}
