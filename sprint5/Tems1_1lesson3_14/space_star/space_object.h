#pragma once

#include <iostream>
#include <string>

class SpaceObject {
public:
    SpaceObject(const std::string& name, double weight, double magnitude)
        : name_{name}, weight_(weight), magnitude_(magnitude) {
    }


    void PrintInfo(std::ostream& out = std::cout, size_t offset = 0) const {
        out << std::string(offset, ' ') << "Имя: " << name_ << std::endl;
        out << std::string(offset, ' ') << "Масса (солнечных масс): " << weight_ << std::endl;
        out << std::string(offset, ' ') << "Звёздная величина: " << magnitude_ << std::endl;
    }

private:
    std::string name_;
    double weight_;
    double magnitude_;
};
