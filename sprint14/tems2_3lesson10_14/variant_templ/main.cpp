#include <cassert>
#include <string>
#include <string_view>

using namespace std::string_literals;
using namespace std::literals;

/* Напишите вашу реализацию EqualsToOneOf здесь*/

template <typename T0, typename... Ts>
bool EqualsToOneOf(const T0& v0, const Ts&... others) {
    //return (... || (v0 == vs));
       return ((v0 == others) || ...);
}


bool IsExpectedAnswer(std::string_view answer) {
    using namespace std::literals;
    return EqualsToOneOf(answer, "yes"sv, "no"sv, "don't know"sv);
}



int main() {
    assert(EqualsToOneOf("hello"sv, "hi"s, "hello"s));
    assert(!EqualsToOneOf(1, 10, 2, 3, 6));
    assert(!EqualsToOneOf(8));
}
