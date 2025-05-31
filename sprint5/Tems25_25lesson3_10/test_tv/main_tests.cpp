#include "practicum_tests.h"

std::vector<Test>& GetPracAllTests() {
    static std::vector<Test> obj;
    return obj;
}

int main() {
  const auto& prac_all_tests = GetPracAllTests();
    int good = 0;
    int bad = 0;
    for(const auto& test: prac_all_tests) {
        std::cout << "RUNNING TEST " << test.name << std::endl;
        try {
            test.func();
            std::cout << "SUCCESS" << std::endl << std::endl;
            ++good;
            continue;
        } catch(const PracTestException& test_ex) {
            std::cout << "FAILED: " << test_ex.what() << std::endl << std::endl;
        } catch(const std::exception& ex) {
            std::cout << "FAILED: " << ex.what() << std::endl << std::endl;
        }
        ++bad;
    }
    std::cout << "Process finished. Total: " << good << " good, " << bad << " bad" << std::endl;

    return bad ? 1 : 0;
}