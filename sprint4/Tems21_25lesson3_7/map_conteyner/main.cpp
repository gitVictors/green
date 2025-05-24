#include <cassert>
#include "phone_book.h"

using namespace std::literals;

int main() {
    {
        PhoneBook book{{{"Mom"s, 7914111111}, {"Sister"s, 7962333333}}};

        assert(book.GetNumber("Mom"s).has_value());
        assert(book.GetNumber("Sister"s).has_value());
        assert(!book.GetNumber("Dad"s).has_value());

        assert(book.GetNumber("Mom"s).value() == 7914111111);
        assert(book.GetNumber("Sister"s).value() == 7962333333);
    } {
        PhoneBook book{{}};

        assert(book.AddName("Mom"s, 7914111111));
        assert(!book.AddName("Mom"s, 790000000));
        assert(book.GetNumber("Mom"s).has_value());
        assert(book.GetNumber("Mom"s).value() == 7914111111);

        assert(book.AddName("Sister"s, 7962333333));
        assert(!book.AddName("Sister"s, 791000022));
        assert(book.GetNumber("Sister"s).has_value());
        assert(book.GetNumber("Sister"s).value() == 7962333333);
    } {
        PhoneBook book{{{"Mom"s, 7914111111}, {"Sister"s, 7962333333}}};

        assert(!book.ChangeNumber("Dad"s, 111111111));

        assert(book.ChangeNumber("Mom"s, 5555555555));
        assert(book.ChangeNumber("Mom"s, 6666666666));
        assert(book.GetNumber("Mom"s).has_value());
        assert(book.GetNumber("Mom"s).value() == 6666666666);
    }
}
