#include "guests_list.h"

#include <cassert>
#include <string>

int main() {
    using namespace std::literals;

    GuestsList guests_list_0{std::set<std::string>{}};
    assert(!guests_list_0.CheckGuest("Mary"s));
    assert(!guests_list_0.CheckGuest("Ivan"s));

    GuestsList guests_list_1{std::set<std::string>{"Eve"s, "Eve"s, "Eve"s}};
    assert( guests_list_1.CheckGuest("Eve"s));
    assert(!guests_list_1.CheckGuest("Lilith"s));

    GuestsList guests_list_2{std::set<std::string>{"Alice"s, "Bob"s, "Charlie"s}};
    assert( guests_list_2.CheckGuest("Alice"s));
    assert( guests_list_2.CheckGuest("Bob"s));
    assert( guests_list_2.CheckGuest("Charlie"s));
    assert(!guests_list_2.CheckGuest("Mary"s));
    assert(!guests_list_2.CheckGuest("Ivan"s));
}
