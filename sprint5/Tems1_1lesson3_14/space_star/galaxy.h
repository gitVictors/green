#pragma once

#include "stellar_system.h"
#include "space_object.h"
#include <vector>
#include <optional>

// Разработайте класс Galaxy.

class Galaxy : SpaceObject {

public:

    Galaxy(const std::string& name, double weight, double magnitude) :
    SpaceObject(name, weight, magnitude)
    {}

    StellarSystem& AddStellarSystem(const StellarSystem& system){
        systems_.push_back(system);
        return systems_.back();
    }

    void PrintInfo(std::ostream& out = std::cout, size_t offset = 0) const {
        SpaceObject::PrintInfo(out, offset);
        out << std::string(offset, ' ') << "Звёздные системы:" << std::endl;
        for (const auto& system : systems_) {
            system.PrintInfo(out, offset + 2);
        }
    }

private:
    std::vector<StellarSystem> systems_;

};
