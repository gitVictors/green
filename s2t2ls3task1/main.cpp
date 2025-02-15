#include <cassert>
#include "details.h"

std::string ToString(const Address& addr) {
    return std::to_string(addr.GetZipCode()) 
        + ", "s + addr.GetCity()
        + ", "s + addr.GetStreet()
        + ", "s + std::to_string(addr.GetBuilding()) 
        + ", "s + std::to_string(addr.GetApartment());
}

void TestAddress() {
    {
        Address address{
            101000, "Moscow"s, "The 3rd Stroiteley Street"s, 
            25, 100
        };
        assert(ToString(address) 
               == "101000, Moscow, The 3rd Stroiteley Street, 25, 100"s);
    }
    {
        Address address{123456, "Moscow"s, "Zastava Ilyicha"s, 8, 1};
        assert(ToString(address) 
               == "123456, Moscow, Zastava Ilyicha, 8, 1"s);
    }
}

void TestPerson() {
    {
        Person person{
            "Zhenya"s, "Lukashin"s, 
            {101000, "Moscow"s, "The 3rd Stroiteley Street"s, 25, 100}};
        assert(person.GetName() == "Zhenya"s);
        assert(person.GetSurname() == "Lukashin"s);
        assert(ToString(person.GetAddress())
               == "101000, Moscow, The 3rd Stroiteley Street, 25, 100"s);
    }

    {
        Person person{
             "Stepan"s, "Stepanov"s, 
             {123456, "Moscow"s, "Zastava Ilyicha"s, 8, 1}};
        assert(person.GetName() == "Stepan"s);
        assert(person.GetSurname() == "Stepanov"s);
        assert(ToString(person.GetAddress()) 
               == "123456, Moscow, Zastava Ilyicha, 8, 1"s);
    }
}

int main() {
    TestAddress();
    TestPerson();
}