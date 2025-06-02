#include "galaxy.h"

int main() {
    Galaxy milky_way{"Млечный путь", 1e12, -20.9};
    StellarSystem& sun_system = milky_way.AddStellarSystem(StellarSystem{"Солнечная система", 1, -26.74, 1, 5772});

    sun_system.AddPlanet(Planet{"Меркурий", 1.660e-7, +0.3, PlanetType::kTerrestrial, 2439});
    sun_system.AddPlanet(Planet{"Венера", 2.447e-6, -4.4, PlanetType::kTerrestrial, 6051});
    sun_system.AddPlanet(Planet{"Земля", 3e-6, -3.99, PlanetType::kTerrestrial, 6378});
    sun_system.AddPlanet(Planet{"Марс", 3.227e-7, +1.5, PlanetType::kTerrestrial, 3389});
    sun_system.AddPlanet(Planet{"Юпитер", 1.898e-4, -9.8, PlanetType::kGasGiant, 69911});
    sun_system.AddPlanet(Planet{"Сатурн", 5.683e-5, -9.6, PlanetType::kGasGiant, 58232});
    sun_system.AddPlanet(Planet{"Уран", 8.681e-6, -7.19, PlanetType::kIceGiant, 25362});
    sun_system.AddPlanet(Planet{"Нептун", 1.024e-6, -7.0, PlanetType::kIceGiant, 24622});

    StellarSystem& alpha_centauri = milky_way.AddStellarSystem(StellarSystem{"Альфа Центавра", 0.123, -0.01, 3, 5772});
    alpha_centauri.AddPlanet(Planet{"Alpha Centauri Bb", 1.2e-6, +11.6, PlanetType::kTerrestrial, 6000}); // Примерные данные
    alpha_centauri.AddPlanet(Planet{"Alpha Centauri B b", 1.1e-6, +10.6, PlanetType::kTerrestrial, 5500}); // Примерные данные
    alpha_centauri.AddPlanet(Planet{"Проксима Центавра b", 1.17e-6, +15.5, PlanetType::kTerrestrial, 4900}); // Примерные данные
    alpha_centauri.AddPlanet(Planet{"Проксима Центавра c", 2.0e-6, +9.5, PlanetType::kTerrestrial, 7500}); // Примерные данные

    milky_way.PrintInfo();
}