#pragma once

#include <algorithm>
#include <random>

#ifdef PRAC_TESTS

class RandomGen {
public:
    template <class T>
    const T& GetRandomElem(const std::vector<T>& elements) const {
        assert(elements.size() > 0);

        int index = std::clamp(in_range, 0, static_cast<int>(elements.size()) - 1);

        return elements[index];
    }

    int GetInRange(const int from, const int to) const {
        last_from = from;
        last_to = to;

        return in_range;
    }

    static void SetInRange(const int value) {
        in_range = value;
    }

    static int GetLastFrom() {
        return last_from;
    }

    static int GetLastTo() {
        return last_to;
    }

private:
    static inline int in_range{2};
    static inline int last_from{0};
    static inline int last_to{0};
};

#else

class RandomGen {
public:
    template <class T>
    const T& GetRandomElem(const std::vector<T>& elements) {
        assert(elements.size() > 0);
        return elements[GetInRange(0, elements.size() - 1)];
    }

    int GetInRange(int from, int to) {
        std::uniform_int_distribution<int> dist(from, to);
        return dist(random_gen);
    }

private:
    std::mt19937 random_gen;
};

#endif