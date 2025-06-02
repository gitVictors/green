#pragma once

#include  "space_object.h"
#include <optional>

enum class PlanetType {
    kTerrestrial, // Земная группа.
    kGasGiant,    // Газовый гигант.
    kIceGiant,    // Ледяной гигант.
    kDwarfPlanet  // Карликовая планета.
};

// Разработайте класс Planet.

class Planet : public SpaceObject {

public:
Planet (const std::string& name, double weight, double magnitude, PlanetType plt, double rzm):
        SpaceObject(name, weight, magnitude), planet_type_(plt), size_(rzm)
    {}


    void PrintInfo(std::ostream& out = std::cout, size_t offset = 0) const {

        SpaceObject::PrintInfo(out , offset ) ;
        if (planet_type_){
            out << std::string(offset, ' ') << "Тип планеты: ";
            switch (*planet_type_) {
            case PlanetType::kTerrestrial : out << "Земная группа";  break;
            case PlanetType::kGasGiant:   out << "Газовый гигант"; break;
            case PlanetType::kIceGiant:  out << "Ледяной гигант"; break;
            case PlanetType::kDwarfPlanet: out << "Карликовая планета"; break;
            default:
                break;
            }
            out << std::string(offset , ' ')  << "Размер: " << *size_ << std::endl;

        }
    }

private:

    std::optional<PlanetType> planet_type_;
     std::optional<double> size_ = 0;
};
