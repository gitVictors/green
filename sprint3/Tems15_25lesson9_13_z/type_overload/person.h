#pragma once

#include <string>

class Person {

public:
    // Допишите здесь недостающие методы.
    explicit  Person (const std::string& name) : name_(name) {}

    const std::string& GetName () const
    {
        return name_;
    }

private:
    std::string name_;
};

