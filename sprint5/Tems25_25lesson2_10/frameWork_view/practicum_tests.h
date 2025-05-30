#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Test{
    std::string name;
    void (*func)();
};
std::vector<Test>& GetPracAllTests();

#define PRAC_STRINGIFY(x) #x
#define PRAC_CONCATENATE(prefix, x) prefix##x
#define PRAC_TEST(X) \
void PRAC_CONCATENATE(PracTest_, X)(); \
struct PRAC_CONCATENATE(PracTestStruct_, X) {\
    PRAC_CONCATENATE(PracTestStruct_, X) () { \
        GetPracAllTests().push_back(\
            {.name=PRAC_STRINGIFY(X), .func=&PRAC_CONCATENATE(PracTest_, X)} \
        );\
    }\
} PRAC_CONCATENATE(instPracTestStruct_, X); \
void PRAC_CONCATENATE(PracTest_, X)()

class PracTestException : public std::runtime_error {
public:
    PracTestException(const std::string& what) : runtime_error(what) {}
};

inline void PracCheck(bool condition, const std::string& text) {
    if (!condition) {
        throw PracTestException(text);
    }
}