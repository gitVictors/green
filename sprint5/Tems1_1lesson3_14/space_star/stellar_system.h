#pragma once

#include "planet.h"
#include "space_object.h"
#include <vector>
#include <optional>


// Разработайте класс StellarSystem.

class  StellarSystem : public SpaceObject
{
public:
    StellarSystem (const std::string& name, double weight, double magnitude, int stars_count, double tpk) :
        SpaceObject(name, weight, magnitude),
        stars_count_(stars_count),
        temp_k_(tpk)
    {}

    void AddPlanet(const Planet &planet){
        planets_.push_back(planet);
    }

   void PrintInfo(std::ostream& out = std::cout, size_t offset = 0) const {
       SpaceObject::PrintInfo(out, offset);
       out << std::string(offset, ' ') << "Количество звёзд: " << stars_count_ << std::endl;
       out << std::string(offset, ' ') << "Температура (K): " << temp_k_ << std::endl;
       out << std::string(offset, ' ') << "Планеты:" << std::endl;
       for (const auto& planet : planets_) {
           planet.PrintInfo(out, offset + 2);
       }

    }

private:
    int stars_count_ = 0;
    double temp_k_ = 0;
    std::vector<Planet> planets_;

};
