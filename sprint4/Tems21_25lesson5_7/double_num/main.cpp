#include "duplicated_values.h"

#include <cassert>
#include <string>

int main() {
    assert((FindDuplicates<int>({1, 2, 3, 3}) == std::vector{3}));
    assert((FindDuplicates<int>({1, 2, 1, 2}) == std::vector{1, 2}));
    assert((FindDuplicates<char>({'a', 'a', 'b', 'b', 'c'}) == std::vector{'a', 'b'}));

    assert((FindDuplicates<std::string>({}) == std::vector<std::string>{}));
    assert((FindDuplicates<int>({27}) == std::vector<int>{}));
    assert((FindDuplicates<int>({1, 2, 3, 4}) == std::vector<int>{}));
    assert((FindDuplicates<char>({'a', 'a', 'a'}) == std::vector{'a'}));
}
