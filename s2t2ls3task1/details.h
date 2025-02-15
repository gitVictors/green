
#pragma once

#include <string>

using namespace std::literals;

class Address {
public:
    Address(int zip_code, const std::string& city, 
            const std::string& street, int building,
            int apartment) : zip_code_(zip_code),
            city_(city),
            street_(street),
            building_(building),
            apartment_(apartment)
    {
    }

    int GetZipCode() const {
        return zip_code_;
    }

    const std::string& GetCity() const {
        return city_;
    }

    const std::string& GetStreet() const {
        return street_;
    }

    int GetBuilding() const {
        return building_;
    }

    int GetApartment() const {
        return apartment_;
    }

private:
    int zip_code_;        // Почтовый индекс.
    std::string city_;    // Город.
    std::string street_;  // Улица.
    int building_;        // Номер дома.
    int apartment_;       // Номер квартиры.
};

class Person {
public:
    Person(const std::string& name, const std::string& surname, 
           const Address& address)
    // Проинициализируйте поля класса в списке инициализации.
    {
    }

    const std::string& GetName() const {
        return name_;
    }
    const std::string& GetSurname() const {
        return surname_;
    }
    const Address& GetAddress() const {
        return address_;
    }

private:
    std::string name_;
    std::string surname_;
    Address address_;
};