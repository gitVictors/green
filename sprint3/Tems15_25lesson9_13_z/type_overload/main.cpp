#include <iostream>
#include "person.h"

int main() {
    // Ошибка: неявно создать объект нельзя.
    // Person p1 = "Gwen"s;

    // Создание объекта с явным преобразованием.
    using namespace std::literals;
    Person p2 = Person("Peter"s);
    std::cout << p2.GetName() << std::endl;
}
