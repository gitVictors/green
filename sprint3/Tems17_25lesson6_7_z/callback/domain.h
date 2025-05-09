#pragma once

enum class UniverseSignalType {
    UFO,                // НЛО.
    SUPERNOVA,          // Вспышка сверхновой.
    DYSON_SPHERE,       // Сфера Дайсона.
    GRAVITATIONAL_LENS, // Гравитационная линза.
};

struct Coordinate {
    double ra;
    double dec;
};

struct SignalInformation {
    double signal_strength;  // Число от 0 до 1.
    Coordinate coordinates;  // Сферические координаты точки.
};

template<UniverseSignalType type>
struct SignalPayload{};

template<>
struct SignalPayload<UniverseSignalType::UFO>{
    std::string alien_ship_model;
    inline static const std::string name = "НЛО";
};

template<>
struct SignalPayload<UniverseSignalType::SUPERNOVA>{
    double stellar_magnitude;
    inline static const std::string name = "вспышка сверхновой";
};

template<>
struct SignalPayload<UniverseSignalType::DYSON_SPHERE>{
    double civilization_development_index;
    inline static const std::string name = "сфера Дайсона";
};

template<>
struct SignalPayload<UniverseSignalType::GRAVITATIONAL_LENS>{
    double diopters;
    inline static const std::string name = "гравитационная линза";
    
};

template<UniverseSignalType type>
struct UniverseSignal {
    // Задаём статическое поле на основе шаблонного параметра.
    inline static UniverseSignalType signal_type = type;
    SignalInformation info;
    SignalPayload<type> payload;
};