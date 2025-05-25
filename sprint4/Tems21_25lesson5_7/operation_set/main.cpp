#include <cassert>
#include "operations_on_sets.h"

int main() {
    {
        std::set<int> set1 = {1, 2, 3};
        std::set<int> set2 = {3, 4, 5};

        assert((Intersection(set1, set2) == std::set<int>{3}));
        assert((Union(set1, set2) == std::set<int>{1, 2, 3, 4, 5}));
        assert((Difference(set1, set2) == std::set<int>{1, 2}));
        assert((Difference(set2, set1) == std::set<int>{4, 5}));
    } {
        std::set<char> set1 = {'h', 'e', 'l', 'l', 'o'};
        std::set<char> set2 = {'w', 'o', 'r', 'l', 'd'};

        assert((Intersection(set1, set2) == std::set<char>{'o', 'l'}));
        assert((Union(set1, set2) == std::set<char>{'h', 'e', 'l', 'w', 'o', 'r', 'd'}));
        assert((Difference(set1, set2) == std::set<char>{'h', 'e'}));
        assert((Difference(set2, set1) == std::set<char>{'w', 'r', 'd'}));
    } {
        std::set<int> set1 = {};
        std::set<int> set2 = {};

        assert(Intersection(set1, set2) == std::set<int>{});
        assert(Union(set1, set2) == std::set<int>{});
        assert(Difference(set1, set2) == std::set<int>{});
    } {
        std::set<int> set1 = {1};
        std::set<int> set2 = {1};

        assert((Intersection(set1, set2) == std::set<int>{1}));
        assert((Union(set1, set2) == std::set<int>{1}));
        assert((Difference(set1, set2) == std::set<int>{}));
        assert((Difference(set2, set1) == std::set<int>{}));
    } {
        std::set<int> set1 = {0, 2};
        std::set<int> set2 = {1, 3};

        assert((Intersection(set1, set2) == std::set<int>{}));
        assert((Union(set1, set2) == std::set<int>{0, 1, 2, 3}));
        assert((Difference(set1, set2) == std::set<int>{0, 2}));
        assert((Difference(set2, set1) == std::set<int>{1, 3}));
    }
}
